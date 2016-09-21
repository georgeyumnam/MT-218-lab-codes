#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MESHX 100
#define MESHY 100

#define MCS 5000  // monte carlo steps

#define B   0.0      // define B

#define T   (3.0)
#define J   (1.0)

#define NUMPOINTS  (MESHX*MESHY)
#define saveT 100


int FLAG[MESHX][MESHY];
int spin[MESHX][MESHY];
double avg[MESHX][MESHY];
double compute_DELTAE(int neighbor_sum, int spin_i);
void initialize();
double calculate_avg_magnetization();


void main(){
  long x, y;
  long i;  // MCS counter
  
  long count;
  double rv;
  int neighbor_sum;
  double ensemble_average;
  double DELTAE;
  
  i=0;
  
  FILE *fp;
  char filename[1000];
  
  initialize();
  
  while (i < MCS){
    // initialize all flags to 0
    for (x=0; x< MESHX; x++){
      for (y=0; y< MESHX; y++){
	FLAG[x][y] = 0;
      }      
    }
    
    for (x=0; x< MESHX; x++){
      for (y=0; y< MESHX; y++){
	avg[x][y] = 0;
      }      
    }
    
    count = 0;
    ensembles=0;
    while (count < NUMPOINTS){
      rv = drand48();
      x = ((long)(floor(NUMPOINTS*rv)))/MESHY;
      y = ((long)(floor(NUMPOINTS*rv)))%MESHY;
      
      neighbor_sum = spin[(x+1)%MESHX][y] + spin[(MESHX + x-1)%MESHX][y] + spin[x][(y+1)%MESHY] + spin[x][(MESHY + y - 1)%MESHY];
      
      DELTAE = compute_DELTAE(neighbor_sum, spin[x][y]);
      
      if (DELTAE < 0.0){
	spin[x][y] = -1.0 + fabs(spin[x][y] - 1.0);
      }
      else {
	rv = drand48();
	if (rv < exp(-DELTAE/T)){
	  spin[x][y] = -1.0 + fabs(spin[x][y] - 1.0);
	}
      }
      
      if (FLAG[x][y] == 0.0){
	FLAG[x][y] = 1.0;
	count++;
      }
    }// closes while for count < NUMPOINTS
    avg = calculate_avg_magnetization();
    ensembles++;
    ensemble_average += avg;
   }
   ensemble_average /= ensembles;
   i++;
   printf("MCS=%ld\n", i);
    
    
    if (i%saveT == 0){
     sprintf(filename, "Monte_carlo_%ld.dat", i);
     fp = fopen(filename, "w");
     for (x=0; x<MESHX; x++){
       for (y=0; y<MESHY; y++){
	 fprintf(fp, "%ld %ld %d\n", x, y, spin[x][y]);
       }    
       fprintf(fp, "\n");
     }
    }
    fclose(fp);
    fp = fopen("Magnetization.dat", "w");
    fprintf(fp, "%ld %le\n", i, ensemble_average);
    fclose(fp);
  }// closes while loop in i < MCS
  
}// closes main


double calculate_avg_magnetization(){
    long avg ;
    avg = 0.0;
    for (x=0; x<MESHX; x++){
       for (y=0; y<MESHY; y++){
	avg += spin[x][y] ;
      }
    }
    avg /= NUMPOINTS;
}


double compute_DELTAE(int neighbor_sum, int spin_i){
  return (2*spin_i*(neighbor_sum - B));
  
}

void initialize(){
  long x, y;
  for (x=0; x<MESHX; x++){
     for (y=0; y<MESHY; y++){
	spin[x][y] = -1;
     }
  }
}




