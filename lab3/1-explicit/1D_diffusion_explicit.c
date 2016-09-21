#include<stdio.h>
#include<stdlib.h>

#define MESHX 1000             // This defines the grid of concentration
#define ntimesteps 2000        // Total amount of iteration
#define deltat 0.1             // Change in time
#define deltax 1.0             // Change in concentration

#define NEUMANN                // Define the Neumann boundary condition 
			       // i.e. gradient / slope = 0

#define DIRICHLET
#ifdef DIRICHLET               // Define the Dirichlet boundary condition
 #define const_back 0.5        // i.e. the boundary values are known
 #define const_front 0.1       // i.e. C(0) = A_0, C(N) = A_N
#endif                         // Where A_0, A_N are known constants

#define saveT 100              //

void apply_boundary_conditions(double *c);
void update(double *c_new, double *c_old);
void writetofile(FILE *fp, double *c);
void initialize(double *c);

void main (){
	long x, t; // need to iterate over time and domain
	double c_old[MESHX];
	double c_new[MESHX];
	char filename[1000];
	FILE *fp;
	
	initialize(c_old);
	
	double inv_deltax2 = 1.0/(deltax*deltax);
	
	for (t=0; t < ntimesteps; t++){
	  for (x=0; x<MESHX-1; x++){
	    c_new[x] = c_old[x] + deltat*(c_old[x+1] - 2.0 *c_old[x] + c_old[x-1]);
	  }
	apply_boundary_conditions(c_new);
	update(c_new, c_old);
	  if (t%saveT == 0){
	    sprintf(filename, "composition%ld.dat", t);
	    fp = fopen(filename, "w");
	    writetofile(fp, c_new);	  
	    fclose(fp);
	  } 
	}
}

void initialize(double *c){
  long x;
  for (x=0; x <MESHX/2; x++){
    c[x] = 0.1;
  }
  for (x=MESHX/2 + 1; x <MESHX; x++){
    c[x] = 0.5;
  }
}

void apply_boundary_conditions(double *c){
#ifdef NEUMANN  
  c[0] = c[1];
  c[MESHX-1] = c[MESHX-2];
#endif
  
#ifdef DIRICHLET
  c[0] = const_front;
  c[MESHX-1] = const_back;
#endif
}

void update(double *c_new, double *c_old){
  long x;
  for (x=0; x<MESHX; x++){
    c_old[x] = c_new[x];
  }
}

void writetofile(FILE *fp, double *c){
  long x;
  for (x=0; x<MESHX; x++){
    fprintf(fp, "%le %le\n", x*deltax, c[x]);
  }
  
}
