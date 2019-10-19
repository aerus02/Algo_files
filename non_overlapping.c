/*
Find if it is possible for x,y of any to be non-ovelapping if x is start position and y is end position on an axis and each moves with a velocity v in any of the two directions after infinite time.
*/



#include<stdio.h>
#include<stdlib.h>
 
typedef struct Point{
    long x,y,vel;
}point;

void merge(point *arr,long low,long mid,long high,long n){
	long i,j,k;
    point *arr1,*arr2;
	i = j = k = 0;
	arr1 = (point *)malloc(sizeof(point)*(mid-low+1));
	arr2 = (point *)malloc(sizeof(point)*(high-mid));
	while(i++ < mid-low+1) arr1[i-1].x = arr[low+i-1].x,arr1[i-1].y = arr[low+i-1].y,arr1[i-1].vel = arr[low+i-1].vel; 
	while(j++ < high - mid) arr2[j-1].x = arr[mid+j].x,arr2[j-1].y = arr[mid+j].y,arr2[j-1].vel = arr[mid+j].vel; 
	i = j = 0;
    if(n == 2){
	while(i < mid-low+1 && j < high - mid)
		if(arr1[i].vel < arr2[j].vel) arr[low + k].vel = arr1[i].vel,arr[low + k].x = arr1[i].x,arr[low + k].y = arr1[i].y,i++,k++;
		else arr[low + k].vel = arr2[j].vel,arr[low + k].x = arr2[j].x,arr[low + k].y = arr2[j].y,j++,k++;
	if(i == mid-low+1) 
		while(j != high - mid) arr[low + k].vel = arr2[j].vel,arr[low + k].x = arr2[j].x,arr[low + k].y = arr2[j].y ,j++ ,k++;
	else 
		while(i != mid-low+1) arr[low + k].vel = arr1[i].vel,arr[low + k].x = arr1[i].x,arr[low + k].y = arr1[i].y ,i++ ,k++;
    }
    else if(n == 0){
        while(i < mid-low+1 && j < high - mid)
		if(arr1[i].x < arr2[j].x) arr[low + k].vel = arr1[i].vel,arr[low + k].x = arr1[i].x,arr[low + k].y = arr1[i].y,i++,k++;
		else arr[low + k].vel = arr2[j].vel,arr[low + k].x = arr2[j].x,arr[low + k].y = arr2[j].y,j++,k++;
	if(i == mid-low+1) 
		while(j != high - mid) arr[low + k].vel = arr2[j].vel,arr[low + k].x = arr2[j].x,arr[low + k].y = arr2[j].y ,j++ ,k++;
	else 
		while(i != mid-low+1) arr[low + k].vel = arr1[i].vel,arr[low + k].x = arr1[i].x,arr[low + k].y = arr1[i].y ,i++ ,k++;
	
    }
    free(arr1);
	free(arr2);
}

void mergeSort(point *arr,long low,long high,long n){
	if(low == high) return;
	long mid = (low + high )/2;
	mergeSort(arr,low,mid,n);
	mergeSort(arr,mid+1,high,n);
	merge(arr,low,mid,high,n);
}

int main(void){
    long i,j,k,t,n,flag;
    point * arr;
    scanf("%ld\n",&t);
    while(t--){
        scanf("%ld\n",&n);
        arr = (point *)malloc(sizeof(point)*n);
        for(i = 0; i < n; i++) scanf("%ld %ld %ld",&((arr+i)->x),&((arr+i)->y),&((arr+i)->vel));
        mergeSort(arr,0,n-1,2);
        for(i = 0; i < n; i++)  printf("%ld %ld %ld  ",(arr+i)->vel,(arr+i)->x,(arr+i)->y);
       flag = 1;
        for(int i =0; i < n-1; i++){
           if((arr+i)-> vel < (arr+i+1)->vel)  continue;
           else {
               for( j = i+1; j < n; j++){
                   if((arr+i)->vel == (arr+j) -> vel ) continue;
                   else break;
               }
               if(j-i > 1){
               mergeSort(arr,i,j-1,0);
               for(k = 0; k < n; k++)  printf("%ld %ld %ld  ",(arr+k)->vel,(arr+k)->x,(arr+k)->y);
               for(k = i; k < j && k < n-2; k++){
                   if((arr+k+1)-> x <= (arr+k)->y && (arr+k +2) -> x <= (arr+k)->y ){
                       flag = 0;
                       break;
                   }
               }
               i = j-1;
               }
               if(flag == 0) break;
           }
        }
        if(flag == 1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}