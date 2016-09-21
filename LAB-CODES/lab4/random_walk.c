/* # Random walk */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

#define NJUMPS      100
#define NSEQUENCES  1000

void main() {
    long x[NSEQUENCES][NJUMPS];
    long y[NSEQUENCES][NJUMPS];
    
    long i, j;
    
    double rand;
    long seed;
    double rv;
    
    printf("Enter a seed\n");
    scanf("%ld", &seed);
    
    for (i=0; i<seed ; i++){
       rv = drand48();
    }
    
    for (i=1; i<NSEQUENCES ; i++){
      
      x[i][0] = 0;
      y[i][0] = 0;
      
      for (j=1; j<NJUMPS ; j++){
	rv = drand48();
	if ((rv >0) && (rv <=0.45)) {  // Creating four choices based on the random number - change the biasing to 0 - 0.35, 0.35 - 0.7
	  x[i][j] = x[i][j-1] + 1 ;    // Original was to go from 0.0 to 0.25, 0.25 to 0.5, 0.5 to 0.75, 0.75 to 1.0
	  y[i][j] = y[i][j-1] ;         // When making the forward and return jumps unequal, the linearity will break down.
	}
	if ((rv >0.45) && (rv <=0.7)) {
	  x[i][j] = x[i][j-1] - 1 ;
	  y[i][j] = y[i][j-1] ;
	}
	if ((rv >0.7) && (rv <=0.85)) {
	  x[i][j] = x[i][j-1];
	  y[i][j] = y[i][j-1]  + 1  ;
	}
	if ((rv >0.85) && (rv <=1.0)) {
	  x[i][j] = x[i][j-1];
	  y[i][j] = y[i][j-1]  - 1  ;
	}
      }
    }
    
    double avg_r2mean;
    FILE *fp;
    
    fp = fopen("r2mean2.dat", "w"); // Original was r2mean.dat
    
    for (j=1; j<NJUMPS ; j++){
      avg_r2mean = 0;
      for (i=0; i<NSEQUENCES ; i++){
	avg_r2mean += x[i][j]*x[i][j] + x[i][j]*y[i][j];
      }
      avg_r2mean /= NSEQUENCES;
      fprintf(fp, "%ld %le\n", j , avg_r2mean);
    }
    
    fclose(fp);
}
