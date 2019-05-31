#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
	int t = *a;
	*a=*b;
	*b=t;
}

int sorting(int* arr,int arr_len){
    int swaps = 0;
	double fakt = 1.2473309; 
	double step = arr_len - 1;
	while (step >= 1){
		for (int i = 0; i + step < arr_len; ++i){
			if (arr[i] < arr[i + (int)step]){
				swap(&arr[i], &arr[i + (int)step]);
				swaps++;
			}
		}
		step /= fakt;
	}
	for (int i = 0; i < arr_len - 1; i++){
		int swapped = 0;
		for (int j = 0; j < arr_len - i - 1; j++){
			if (arr[j] < arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				swapped = 1;
				++swaps;
			}
		}
		if (!swapped)
			break;
	}
	return swaps;
}

int main(){
	int n,t;
	scanf("%d",&n);
	int *arr = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	// printf("%d\n",sorting(arr,n));
	sorting(arr,n);
	for(int i=0;i<n-1;i++)
		printf("%d ",arr[i]);
	printf("%d\n", arr[n-1]);
	return 0;
}