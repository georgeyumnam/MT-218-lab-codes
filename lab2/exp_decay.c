#include<stdio.h>
#include<stdlib.h>

// #define - defines the variable global
// format is #define (variable) (assignment)
#define TOTAL_ITERATIONS 10     // total time for the computation
#define deltat_exp 0.1	 // change in time for the implicit case	
#define deltat_imp 0.1   // change in time for the explicit case	
#define deltat_PC 0.1   // Predictor correction

void main() { // Now we are writing a code to solve the first oder differential equation:
	      //  dx
	      // ---- = 2*x + 3
	      //  dt
  double x_exp[TOTAL_ITERATIONS], x_imp[TOTAL_ITERATIONS] , x_PC[TOTAL_ITERATIONS];
  int t;
  
  FILE *fp1, *fp2, *fp3;
  
  fp1 = fopen("Exponential_exp.dat", "w");
  fp2 = fopen("Exponential_imp.dat", "w");
  fp3 = fopen("Exponential_pc.dat", "w");
  
  x_exp[0] = 0.0;
  x_imp[0] = 0.0;
  x_PC[0]  = 0.0;
  
// 1) Explicit
  for (t=0; t < TOTAL_ITERATIONS-1 ; t++){
    x_exp[t+1] = x_exp[t] + (2.0*x_exp[t] + 3)*deltat_exp;
    x_imp[t+1] = (x_imp[t] + 3.0*deltat_imp)/(1.0 - 2.0*deltat_imp);
    x_PC[t+1]  = 2.0*deltat_PC*(x_PC[t] + x_PC[t]*deltat_PC + 1.5*deltat_PC) + 3.0*deltat_PC + x_PC[t];
    
    fprintf(fp1, "%le %le\n", (t+1)*deltat_exp, x_exp[t+1]);
    fprintf(fp2, "%le %le\n", (t+1)*deltat_imp, x_imp[t+1]);
    fprintf(fp3, "%le %le\n", (t+1)*deltat_PC, x_PC[t+1]);
  }
  
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  
  // Now we plot the generated files using gnuplot
  // f(x) = 1.5*(exp(2*x) - 1) -- this is the exact solution

}