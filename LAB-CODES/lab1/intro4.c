// How to write a file
// Pointers - is the address at which a variable is stored

#include<stdio.h>
#include<stdlib.h>
// File creation
int add();
int sum;
void main() {
FILE *fp;
int i;
double j, k , l; 
fp = fopen("data.dat", "w"); // options can be w, r
for (i=0; i<1000; i++){
j = i/3 ;
k = (i - 4 )/7 ;
l = (j + k - 3)/11 ;
fprintf(fp, "%le %le %le\n", j, k, l );
//fprintf(fp, "Hello\n");
}
fclose(fp);

sum = add();
printf("sum=%d\n", sum);
}

int add(){
int k ; 
int sum = 0 ;
double arr[1000];
for (k = 1; k<11; k++)
{
arr[k]=k;
}

for (k = 1; k<6; k++)
{
sum += arr[k] + arr[11-k];
}

}

