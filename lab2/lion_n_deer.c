// The lion and deer problem 

#include<stdio.h>
#include<stdlib.h>

#define TOTAL_TIME 100000
#define  deltat 0.0001

#define INITIAL_X 5
#define INITIAL_Y 5

// We want to solve the following equation:
/*
    dx
   ---- = A*x - B*x*y
    dt
and 
    dy
   ---- = D*x + G*x*y
    dt
where, x is deer population and y is the lion population
*/

#define alpha 4.0
#define beta  2.0
#define gamma 3.0
#define delta 3.0

void main() {
  double x, y;
  double dxbdt;
  double dybdt;
  int t;
  
  FILE *fp;
  
// Explicit  
  fp = fopen("Explicit.dat", "w") ;
  
  x = INITIAL_X;
  y = INITIAL_Y;
  
  for (t=0; t<TOTAL_TIME; t++){
     dxbdt = alpha*x - beta*x*y;
     dybdt = -gamma*y + delta*x*y;
     
     x += dxbdt*deltat; // x(t+del_t) = x(t) + dxbdt*deltat ;
     y += dybdt*deltat;
     
     fprintf(fp, "%le %le %le\n", t*deltat, x, y);
  }
  fclose(fp);

// PREDICTOR CORRECTOR
  fp = fopen("Predictor.dat", "w") ;
  x = INITIAL_X;
  y = INITIAL_Y;
  
  double x_tilde; //, x_tilde_1, x_tilde_2, x_tilde_3, x_tilde_4;
  double y_tilde; //, y_tilde_1, y_tilde_2, y_tilde_3, y_tilde_4;
  
  for (t=0; t<TOTAL_TIME; t++){
     dxbdt = alpha*x - beta*x*y;
     dybdt = -gamma*y + delta*x*y;
     
     x_tilde = x + dxbdt*deltat;    // User defined for greater accuracy
     y_tilde = y + dybdt*deltat;    // " " 
     
     dxbdt += alpha*x_tilde - beta*x_tilde*y_tilde;
     dybdt += -gamma*y_tilde + delta*x_tilde*y_tilde;
     
     x += 0.5*dxbdt*deltat;
     y += 0.5*dybdt*deltat;
     
     fprintf(fp, "%le %le %le\n", t*deltat, x, y);
  }
  fclose(fp);

// RUNGE - KUTTA METHOD FOR FOURTH ORDER
//
  fp = fopen("rungekutta.dat", "w") ;
  x = INITIAL_X;
  y = INITIAL_Y;

  double  x_tilde_1, x_tilde_2, x_tilde_3, x_tilde_4;
  double  y_tilde_1, y_tilde_2, y_tilde_3, y_tilde_4;
  double  dxbdt_1, dxbdt_2, dxbdt_3, dxbdt_4;
  double  dybdt_1, dybdt_2, dybdt_3, dybdt_4;


  for (t=0; t<TOTAL_TIME; t++){
     dxbdt = alpha*x - beta*x*y;
     dybdt = -gamma*y + delta*x*y;

// First estimate
     x_tilde_1 = x + 0.5*dxbdt*deltat;
     y_tilde_1 = y + 0.5*dybdt*deltat;

     dxbdt_1 = alpha*x_tilde_1 - beta*x_tilde_1*y_tilde_1;
     dybdt_1 = -gamma*y_tilde_1 + delta*x_tilde_1*y_tilde_1;

// Second estimate
     x_tilde_2 = x + 0.5*dxbdt_1*deltat;
     y_tilde_2 = y + 0.5*dybdt_1*deltat;

     dxbdt_2 = alpha*x_tilde_2 - beta*x_tilde_2*y_tilde_2;
     dybdt_2 = -gamma*y_tilde_2 + delta*x_tilde_2*y_tilde_2;

// Third estimate
     x_tilde_3 = x + 0.5*dxbdt_2*deltat;
     y_tilde_3 = y + 0.5*dybdt_2*deltat;
     
     dxbdt_3 = alpha*x_tilde_3 - beta*x_tilde_3*y_tilde_3;
     dybdt_3 = -gamma*y_tilde_3 + delta*x_tilde_3*y_tilde_3;

// Fourth order

     dxbdt_4 = (1.0/6.0)*(dxbdt + 2.0*(dxbdt_1+dxbdt_2) + dxbdt_3);
     dybdt_4 = (1.0/6.0)*(dybdt + 2.0*(dybdt_1+dybdt_2) + dybdt_3);

     x += dxbdt_4*deltat;
     y += dybdt_4*deltat;

     fprintf(fp, "%le %le %le\n", t*deltat, x, y);
  }
  fclose(fp);  
  
// How can one can go so that the predictor corrector does bad as compared to the Runge-Kutta scheme? value of deltat?

}
