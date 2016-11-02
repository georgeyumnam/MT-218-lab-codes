#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MESHX 500
#define ntimesteps 5000000
#define deltat 0.001
#define deltax 1.0
#define M 1.0
#define kappa 46.6
#define saveT 100000

#define NEUMANN

double inv_deltax2 = (1.0/deltax)*(1.0/deltax);
//double kappa;

void initialize(double *comp);
void compute_lapacian(double *u, double *lapu);
void compute_chem_pot(double *comp, double *lapc, double *chempot);
void update(double *comp,  double *lapmu);
void apply_boundary_conditions(double *comp);
void write2file(double *comp , long t);
double compute_surface_energy(double *comp);

void main(){
  long x;
  long t;
  double comp[MESHX];
  double chempot[MESHX];
  double lapmu[MESHX];
  double lapc[MESHX];
  double surface_energy;
  
  //kappa = 900.0/(log(81.0)*log(81.0));

  initialize(comp);
  for (t=0; t<ntimesteps; t++){
    compute_lapacian(comp, lapc);
    compute_chem_pot(comp, lapc, chempot);
    compute_lapacian(chempot, lapmu);
    update(comp, lapmu);
    apply_boundary_conditions(comp);
    if (t%saveT == 0){
      write2file(comp, t);
      surface_energy = compute_surface_energy(comp);
      printf("Functional = %le\n", surface_energy);
    }
  }
}

void initialize(double *comp){
  long x;
  for (x=0;x<=MESHX*0.5;x++){
    comp[x] = 0.0;
  }
  for (x=0.5*MESHX+1;x<=MESHX;x++){
    comp[x] = 1.0;
  }
}

void compute_lapacian(double *u, double *lapu){
  long x;
  for (x=1; x < MESHX - 1; x++){
    lapu[x] = (u[x+1] - 2.0*u[x] + u[x-1])*inv_deltax2;
  }
  lapu[0] = 0.0;
  lapu[MESHX-1] = 0.0;
}

void compute_chem_pot(double *comp, double *lapc, double *chempot){
  long x;
  double c;
  for (x=0; x < MESHX; x++){
    c = comp[x];
    chempot[x] = 18.0*c*(1.0-c)*(1.0-2.0*c) - 2.0*kappa*lapc[x];
  }
}

void update(double *comp, double *lapmu){
  long x;
  double c;
  for (x=0; x < MESHX; x++){
    comp[x] += deltat*M*lapmu[x];
  }
}

void apply_boundary_conditions(double *comp){
#ifdef NEUMANN
	comp[0] = comp[3];
	comp[1] = comp[2];
	comp[MESHX-1] = comp[MESHX-4];
	comp[MESHX-2] = comp[MESHX-3];
	
#endif
}
void write2file(double *comp , long t){
		long x ;
		FILE *fp;
		char filename[10000];
		sprintf(filename, "Composition_%ld.dat", t);
		fp = fopen(filename, "w");
		for (x=0; x< MESHX; x++){
			fprintf(fp, "%le %le\n", x*deltax , comp[x]);
		}
		fclose(fp);
}

double compute_surface_energy(double *comp){
  long x;
  FILE *fp;
  double surface_energy = 0.0;
  double gradient, c;
  for (x=1; x< MESHX-1; x++){
    c  = comp[x];
    gradient = (comp[x+1]-comp[x])/deltax;
    surface_energy += (kappa*gradient*gradient + 9.0*c*c*(1.0-c)*(1.0-c))*deltax;
  }
  return surface_energy;
}



