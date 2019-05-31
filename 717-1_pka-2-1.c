#include <stdio.h>

int main(){
	int min,n,tmp;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&tmp);
		if(i==0 || tmp<min){
			min=tmp;
		}
	}
	printf("%d\n",min);
	return 0;
}
