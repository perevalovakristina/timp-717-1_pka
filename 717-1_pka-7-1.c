#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int t = *a;
    *a=*b;
    *b=t;
}

void sorting(int* arr, int arr_len) {
    int i = 0, j = arr_len, temp, p = arr[arr_len/2];
    do {
        for ( ;arr[i] < p; i++);
        for ( ;arr[j] > p; j--); 
        if (i <= j) 
            swap(&arr[i++],&arr[j--]);
    } while ( i<=j );
    if ( j > 0 ) 
        sorting(arr, j);
    if ( arr_len > i ) 
        sorting(arr+i, arr_len-i);
}

int main(){
    int n,t;
    scanf("%d",&n);
    int *arr = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    // printf("%d\n",sorting(arr,n));
    sorting(arr,n-1);
    for(int i=0;i<n-1;i++)
        printf("%d ",arr[i]);
    printf("%d\n", arr[n-1]);
    return 0;
}