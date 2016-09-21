#include<stdio.h>
#include<stdlib.h>

#define MESHX 1000

#define ntimesteps 2000
#define deltat 0.1
#define deltax 1.0

// #define DIRICHLET
#define NEUMANN

#ifdef DIRICHLET
 #define const_back 0.5
 #define const_front 0.5
#endif

#define saveT 100

// void apply_boundary_conditions(double *c);
// void update(double *c_new, double *c_old);
void writetofile(FILE *fp, double *c);
void initialize(double *c);

void main() {
  long x, t;
  double c_old[MESHX+2];
  double c_new[MESHX+2];
  
  double A[MESHX];
  double B[MESHX];
  double C[MESHX];
  double D[MESHX];
  
  char filename[1000];
  FILE *fp;
  
  double inv_deltax2 = 1.0/(deltax*deltax);
  
  double alpha = deltat*inv_deltax2;
  
  initialize(c_old);
  
  for (t=0; t < ntimesteps; t++) {
    
    // Create the matrix
//     D[0]     = c_old[0];
    B[1] = 1.0 + 2.0*alpha;
    C[1] = -alpha;
    A[1] = 0.0;
    D[1] = c_old[1]     + alpha*c_old[0];
    
    for (x=2; x < MESHX+1; x++) {
      A[x] = -alpha;
      B[x] = 1.0 + 2.0*alpha;
      C[x] = -alpha;
      D[x] = c_old[x];
    }
   
    C[MESHX] = 0.0;
    D[MESHX] = c_old[MESHX] + alpha*c_old[MESHX+1];
    
    //Transform matrix (Forward)
    for (x=2; x <= MESHX; x++) {
      B[x] = -C[x-1]*(A[x]/B[x-1]) + B[x];
      D[x] = -D[x-1]*(A[x]/B[x-1]) + D[x]; 
    }
    
    //Backward substitution
    
    c_old[MESHX] = D[MESHX]/B[MESHX];
    
    for (x=MESHX-1; x >= 1; x--) {
      c_old[x] = (D[x] - C[x]*c_old[x+1])/B[x]; 
    }
    
    if (t%saveT == 0) {
      sprintf(filename, "composition_%ld.dat",t);
      fp = fopen(filename, "w");
      writetofile(fp, c_old);
      fclose(fp);
    }
  }
}
void initialize(double *c) {
  long x;
  for (x=0; x < (MESHX+1)/2; x++) {
    c[x] = 0.1;
  }
  for (x=(MESHX+1)/2+1; x <= MESHX+1; x++) {
    c[x] = 0.5;
  }
}
void writetofile(FILE *fp, double *c) {
  long x;
  for (x=0; x <= MESHX+1; x++) {
    fprintf(fp, "%le %le\n", x*deltax, c[x]);
  }
}
