#include<stdio.h>
#include<stdlib.h>

#define xrange (2.0)
#define yrange (2.0)

#define NRAM 90000000

void main(){
  double x, y;
  
  long iter;
  long accept=0;
  
  for(iter=0; iter<NRAM ; iter++){
    x = -1.0 + xrange*(drand48());
    y = -1.0 + yrange*(drand48());
    
    if (y*y + x*x <= 1.0){
      accept++;
    }
  }
  printf("Pi = %le\n", ((double)(accept)/(double)(NRAM))*4.0);
}