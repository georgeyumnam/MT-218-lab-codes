// Arrays 

void main(){

double arr[1000];
int k, sum;
	sum = 0;
	for (k=0; k< 1000; k++){ // defining the array
	arr[k]=k;
	}
	for (k=0; k< 500; k++){ // computing the sum
        sum += arr[k] + arr[1000-k];
        }
	printf("%d\n", sum);
}
