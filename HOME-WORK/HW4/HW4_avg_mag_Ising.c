#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MESHX 100
#define MESHY 100

#define MCS 5000

#define T (3.0)

#define J (1.0)

#define NUMPOINTS (MESHX*MESHY)

#define saveT 1000

int FLAG[MESHX][MESHY];   // in order to check if the MCS cycle needs to be restart
int spin[MESHX][MESHY];   // the spin of the lattice site  (i, j)

double compute_DELTAE(int neighbor_sum, int spin_i, float B);  // to compute the second spin flipping criteria
void initialize();          // initialize the spin of the lattice

long total;                     // to count the total magnetization -- this divided by total NUMPOINTS gives avg magnetization

void main() {
  long x, y; 
  long i;           //MCS counter
  
  long count;      // to keep the count between the NUMPOINTS
  double rv;            // some random MC variable
  int neighbor_sum;         // sum of spins in neighbour points 
  double DELTAE;            // The difference in energy of spin flipped and initial case
  float B;                  // to specify the external magnetization  
  FILE *fp;             // for the creation of the file
  
  char filename[10000];     // filename definition
  double avg, ensemble_average;         // define average and the ensemble average
  long ensembles;                       // define the ensembles
  
    
 for (B=-1.0; B<=1.0; B = B + 0.1)    // Perform the avg mag calculation for different external field values
 {
	  initialize();        // OK, for this B value, initialize the lattice sites
	  printf("Now starting for: B = %f ----**** ----\n", B);
	  i=0;                 //  initialize the counter to 0 <-- this marks the start
	  while(i < MCS) {     // Limiting the MCS cycle steps to defined MCS value
				
				for(x=0; x< MESHX; x++) {    // for each x values in the lattice
				  for(y=0; y< MESHY; y++){   // for each y " " " " " 
					FLAG[x][y] = 0;        // initialize flags to 0 <- indicate when to flip spin of which lattice site
				  }
				}
				count = 0;  // count the points covered in the lattice --> initialize to 0
				ensembles=0;    // initialize the ensemble
				while(count < NUMPOINTS) {      // while the count is less than the total sites
				  
				  rv = drand48();  // some random variable
				  
				  x = ((long)(floor(NUMPOINTS*rv)))/MESHY;  // converting a string of 1D array to 2D 
				  y = ((long)(floor(NUMPOINTS*rv)))%MESHY;  // this is just a clever scheme to save space
				  
				  neighbor_sum = spin[(x+1)%MESHX][y]               +  // neighbour 1
                                                 spin[(MESHX + x - 1)%MESHX][y]     +  // neighbour 2
                                                 spin[x][(y+1)%MESHY]               +  // neighbour 3
                                                 spin[x][(MESHY + y-1)%MESHY];         // neighbour 4 
				  
				  DELTAE = compute_DELTAE(neighbor_sum, spin[x][y], B); // compute 2*spin_i*(neighbor_sum - B)
				  
				  if (DELTAE < 0.0) {       // if the DELTAE is -ve, then flip the spin --
					spin[x][y] = -1.0 + fabs(spin[x][y]-1.0); //--  flipping the spin
				
					if (spin [x][y] == 1 ) // if current spin = +1, => -1 changed to +1, i.e. 1 - (-1) = +2
						total += 2;    // increase total spin by 2
					else if (spin [x][y] == -1) // opposite of previous
						total -= 2;   
			 
				  } 
				  else {   // if DELTAE is +ve , then----
					rv = drand48(); 
					if(rv < exp(-DELTAE/T)) { // flip spin only if this random selection is satisfied
					  spin[x][y] = -1.0 + fabs(spin[x][y]-1.0); // flipping
					  if (spin [x][y] == 1 ) // same as above
						  total += 2;
					  else if (spin [x][y] == -1)
						  total -= 2;
					}
				  }
				  
				  if (FLAG[x][y]==0){ // Now, for this lattice site -- raise the flag
					FLAG[x][y]=1;
					count++;  // increase the total count of raised flag
				  }
				  avg = ((double)total)/((double)NUMPOINTS); // avg = (total magnetization / NUMPOINTS)
				  ensembles++;              // increase the ensemble
				  ensemble_average += avg;  // in order to calculate the ensemble average
				}
				ensemble_average /= ensembles; // ensemble average --> average of the avg mag for a given ext mag field
				
                                                        printf("MCS=%ld\n",i);
							if (i%saveT==0) {
							  sprintf(filename,"Monte_Carlo_%f_%ld.dat", B, i);
							  fp=fopen(filename,"w");
							  for (x=0; x < MESHX; x++) {
								for (y=0; y < MESHY; y++) {
								  fprintf(fp,"%ld %ld %d\n",x, y, spin[x][y]);
								}
								fprintf(fp,"\n");
							  }
							  fclose(fp);
							}
							//sprintf(filename,"Magnetization_%f.dat", B);
							//fp=fopen("Magnetization_%f.dat", B, "a");
							//fprintf(fp, "%ld %le\n",i, ensemble_average);
							//fclose(fp);
                                i++;   // increase the MCS cycle step
				
			  } // end of MCS cycle
				sprintf(filename,"Ens_avg_B.dat");
				fp=fopen("Ens_avg_B.dat","a");
				fprintf(fp, "%f %le\n", B, ensemble_average);
				printf("%f %le\n", B, ensemble_average);
				fclose(fp);
} // closing the step for each B
}// close main()


double compute_DELTAE(int neighbor_sum, int spin_i, float B) { // compute DELTAE
  return (2*spin_i*(neighbor_sum - B)); // refer notes for derivation of this formulae
}
void initialize() { // set all lattice site to -1 spin -- and the total spin = sum of all spin
  long x, y;
  total = 0;
   for (x=0; x < MESHX; x++) {
    for (y=0; y < MESHY; y++) {
      spin[x][y]=-1;
	total += spin[x][y];
    }
  }
}
