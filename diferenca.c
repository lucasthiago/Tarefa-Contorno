#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 9

double alpha = -.3;
double beta = -.1;

double r(double x) {return (cos(x));}

void imprime(double **M, int var){
	
	int i, j;
	
	for(i=0;i<var;i++) {
		for(j=0;j<var+1;j++) { 
			printf("%5.2lf\t",M[i][j]);
		}	  
		puts("");
	}
}

void sistema(double **M, double x[N], double h)
{
	int i, j;
	
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			M[i][j]=0;
			
			if(i==j)
				M[i][j]=2+2*pow(h, 2);
				
			if(i==j+1)
				M[i][j]=-1-(h/2.);
				
			if(i+1==j)
				M[i][j]=-1+(h/2.);
		}
	}
	
	for(i=0; i<N; i++)
	{	
		M[i][N]=(-1)*pow(h, 2.)*r(x[i]);
	
		if(i==0)
			M[i][N]=(-1)*pow(h, 2.)*r(x[0])+(1.+(h/2.))*alpha;
	
		if(i==N-1)
			M[i][N]=(-1)*pow(h, 2.)*r(x[N-1])+(1.-(h/2.))*beta;
			
	}
	
	imprime(M, N);
	
}



void triangsup(double **M, int dim) 
{
	int i, j, k;
	double lamb;
	i=j=0;
	
	for(j=0; j<dim; j++)
	{
		for(i=j; i<dim-1; i++) 
		{
			lamb=M[i+1][j]/M[j][j];
			for(k=j; k<dim+1; k++)
			{
				M[i+1][k] = M[i+1][k] - (lamb)*M[j][k];
			}
		}
	}
}

void subsreversa (double **M, double *raizes, int dim)
{
	int i, j;
	double soma=0;
	
	
	for(i=dim-1; i>=0; i--)
	{
		raizes[i] = M[i][dim];
		
		for(j=dim; j>=i+1; j--)
			raizes[i]-=M[i][j]*raizes[j];
			
		raizes[i]/=M[i][i];
	}
}

main()
{
	FILE *fp;
	double a=0., b=M_PI/2., h;
	double **M, x[N], *raizes;
	int i;
	
	fp=fopen("dif.dat", "w");
	
	h=(b-a)/(N+1);
	
	x[0]=a+h;
	printf("h=%lf\n\n", h);
	for(i=1; i<N; i++)
		x[i]=x[i-1]+h;
	
	M = malloc( N*sizeof(double *));
	for( i = 0 ; i < N ; i++ )
		M[i] = (double *) malloc((N+1)*sizeof(double));
	
	sistema(M, x, h);	
		
	//imprime(M, N);
	raizes = malloc(N*sizeof(double ));
	triangsup(M, N);
	subsreversa(M, raizes, N);
	
	fprintf(fp, "%lf\t%lf\n", a, alpha);
	
	for(i=0; i<N; i++)
		fprintf(fp, "%lf\t%lf\n", x[i], raizes[i]);

	fprintf(fp, "%lf\t%lf\n", b, beta);
}
