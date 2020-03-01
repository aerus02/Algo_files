#include<stdio.h>

int main(void){
	long i,j,t,n,k,fl;
	scanf("%ld\n",&t);
	while(t--){
		fl = 0;
		scanf("%ld %ld\n",&n,&k);
		long arr[n];
		i = 0;
		if(k == 2){
			scanf("%ld",arr);
			i++;
			while(i++ < n){
				scanf("%ld",arr+i-1);
				if(arr[i-2] != -1 && arr[i-2] == arr[i-1]) fl = 1;
			}
			if(fl){
				printf("NO\n");
				continue;
			}
			for(i = 0;i<n;i++){
				if(arr[i] == -1) {
					for(j = i+1;j<n && arr[j] == -1;j++);
					//if(j == n) arr[j-1] = 1;
					if(i != 0 && j!=n){
						if(((j -i)%2 == 0 && arr[i-1] == arr[j]) || ((j-i)%2 ==1 && arr[i-1] != arr[j])) {
							fl = 1;
							break;
						}					
						while(j-- >i) arr[j] = (arr[j+1])%k+1; 
						if(j > 0 && arr[j-1] == arr[j]) arr[j] = (arr[j-1])%k+1;
					}
					else if(i == 0){
						while(j-- >0) arr[j] = arr[j+1]%2+1;
					}
					
					else{
					 j = i-1;
					 while(j++ <n) arr[j] = arr[j-1]%2+1;
					}
				}
			}
			if(fl) printf("NO\n");
			else{
		 	printf("YES\n");
		 	j = 0;
		 	while(j++ < n) printf("%ld ",arr[j-1]);
		 	printf("\n");
			}
			continue;

		}
			while(i++ < n) {
				scanf("%ld",arr+i-1);
				if(arr[i-2] != -1 && arr[i-2] == arr[i-1]) fl = 1;
			}
			if(fl) {
				printf("NO\n");
				continue;
			}
		
			for(i = 0;i<n;i++){
				if(arr[i] == -1) {
					for(j = i+1;j<n && arr[j] == -1;j++);
					if(j == n) arr[j-1] = 1;
						while(j-- >i) arr[j] = (arr[j+1])%k+1; 
						if(j > 0 && arr[j-1] == arr[j]) arr[j] = (arr[j-1])%k+1;
				}
			}
			i = 0;
			printf("YES\n");
			while(i++ < n) printf("%ld ",arr[i-1]);
			printf("\n");

		}
	return 0;
}
