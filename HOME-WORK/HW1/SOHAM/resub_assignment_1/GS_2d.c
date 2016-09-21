#include <stdio.h>
#include <stdlib.h>

#define deltat 0.1
#define deltax 1.0
#define deltay 1.0
#define meshx 100
#define meshy 100
#define ntime 1000
#define saveT 100
#define radius 20

void update ();
void initialize ();
void writetofile (FILE *fp);

double c_old[meshx+2][meshy+2];
double c_k[meshx+2][meshy+2];
double c_prev[meshx+2][meshy+2];

void main()
{
	
	long x,y,iter,t;
	double inv_deltax2 = 1/(deltax*deltax);
	double alpha = deltat*inv_deltax2;//we have taken deltax = deltay, so alpha remains the same for both directions
	FILE *fp;
	char filename[1000];
	initialize ();//create initial values
	for (t=0;t<ntime;t++)
	{
		if (t == 0)
		{
		sprintf(filename,"composition_init.dat");
		fp=fopen (filename,"w");
		writetofile (fp);
		fclose (fp);
		}
		for (y=0;y<=meshy+1;y++)
		{
			for (x=0;x<=meshx+1;x++)
			{
				c_prev[x][y] = c_old[x][y]; //store values of previous time step before moving on to new time-step
			}
			
		}
		for (iter=0;iter<=20; iter++)
		{
			for (y=1;y<meshy+1;y++)
			{
				for (x=1;x<meshx+1;x++)
				{
					c_old[x][y] = (alpha*(c_old[x-1][y]+c_old[x+1][y]+c_old[x][y+1]+c_old[x][y-1])+c_prev[x][y])/(1+4*alpha);
				}
				
			}
			
		}
		if (t%saveT == 0){
		sprintf(filename,"composition%ld.dat", t);
		fp=fopen (filename,"w");
		writetofile (fp);
		fclose (fp);
	    }
	    
	}		
}

void initialize()
{
 long x,y;
 for (x=0;x<=(meshx+1);x++)
 {
	 for(y=0;y<=(meshy+1);y++)
	 {
		 if (((x-(meshx+1)/2)*(x-(meshx+1)/2) + (y-(meshy+1)/2)*(y-(meshy+1)/2)) < radius*radius)
			c_old[x][y] = 1.8;
		 else
			c_old[x][y] = 1.0;
	 }
 }
}


void writetofile (FILE *fp) 
{
 long x,y;
 for (x=0;x<=(meshx+1);x++)
 {
	 for (y=0;y<=(meshy+1);y++)
	 {
		 fprintf(fp, "%le %le %le\n", x*deltax, y*deltay, c_old[x][y]);
	 }
	 fprintf(fp,"\n");
 }	
}
