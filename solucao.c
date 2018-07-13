#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 100
#define M 2

void solucao()
{
	FILE *gp, *fp, *rp;
	double y1[N+1], y2[N+1];
	double a, b;
	double alpha=-.3, beta=-.1, y, t, h;
	int i=0;
	
	
	gp=fopen("RK1.dat", "r");
	fp=fopen("RK2.dat", "r");
	rp=fopen("Sol.dat", "w");
	
	while(i<=N)
	{
		fscanf(gp, "%lf\t%lf\n", &a, &b);
		y1[i]=b;
		
		fscanf(fp, "%lf\t%lf\n", &a, &b);
		y2[i]=b;
		
		i++;
	}
	
	h= M_PI/2./N;
	t=0;
	
	for(i=0; i<=N; i++)
	{
		y=y1[i] +((beta-y1[N])/y2[N])*y2[i];
		fprintf(rp, "%lf\t%lf\t%lf\t%lf\n", t, y, y1[i], y2[i]);
		t+=h;
	}
}

void main()
{
	solucao();
}
