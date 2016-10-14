// This is a code for solving the simple harmonic motion

#include<stdio.h>
#include<stdlib.h>

#define m 1.0
#define k 1.0

#define deltat 0.1
#define ntimesteps 10000

#define TRIVIAL
#define VERLET
#define MOD_VERLET
#define LEAPFROG

void main(){
  double x[ntimesteps], v[ntimesteps] ;
  
#ifdef TRIVIAL
  x[0] = 0;
  v[0] = 1;
  
  for (t=0; t<ntimesteps-1; t++){
    x[t+1] = x[t] + v[t]*deltat + 0.5*(-k*x[t]/m)*(deltat*deltat);
    v[t+1] = v[t] + a[t]*deltat;
  }
#endif
  
#ifdef VERLET
  x[0] = 0;
  v[0] = 1;
  
  for (t=1; t<ntimesteps-1; t++){
    x[t+1] = x[];
  }
#endif
  
}