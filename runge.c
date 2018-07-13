#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 100
#define M 2

double dz(double t, double y[M])
{
    return(y[1]+2*y[0]+cos(t)); // retorna valor de dy/dt
}

double dy(double t, double y[M])
{
	return (y[1]);
}

double a=0.;
double y[M] = {0, 1};
void RungeKutta(double t, double y[M])
{
    FILE *gp;
    gp = fopen("RK2.dat", "w");
    
    double k1[M], k2[M], k3[M], k4[M], h, b=M_PI/2., aux[M], (*equacao[M])() = {dy, dz};
    int i;
    
        
    h=(b-a)/N;
    
    while(t<=b)
    {
        fprintf(gp, "%lf\t%lf\n", t, y[0]);
        
        for(i=0; i<M; i++)
        	aux[i]=y[i];
       
        //funções  K1, K2, K3 e K4
        for(i=0; i<M; i++)
		k1[i] = equacao[i](t, y);
	
	for(i=0; i<M; i++)
		aux[i]=y[i]+k1[i]*h/2;
	
       	
        for(i=0; i<M; i++)
        	k2[i] = equacao[i](t+h/2, aux);
        
        for(i=0; i<M; i++)
        	aux[i]=y[i]+k2[i]*h/2;
        
        for(i=0; i<M; i++)	
        	k3[i] = equacao[i](t+h/2, aux);
        
        for(i=0; i<M; i++)
        	aux[i]=y[i]+k3[i]*h;
        		
        for(i=0; i<M; i++)
        	k4[i] = equacao[i](t+h, aux);
        
        for(i=0; i<M; i++)
        	y[i]+=(k1[i]+2*k2[i]+2*k3[i]+k4[i])*h/6; // cálculo de yi+1							     	
      
        t+=h;
    }
}



void main()
{	
	RungeKutta(a, y);
}
