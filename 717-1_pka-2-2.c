#include <stdio.h>
#include <math.h>
int main(){
	int sum=0,n,tmp;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&tmp);
		sum+=pow(-1,i)*pow(tmp,3);
	}
	printf("%d\n",sum);
	return 0;
}
