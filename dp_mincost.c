
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int findTotal(int start,int end,int b1,int **cost){
	if(start > end) return INT_MAX;  
    if(b1 == 1) return cost[start][end];
	int i,min,tem;	
    min = INT_MAX;
	for(i = start; i <= end; i++){
		if(cost[start][i] > min ) continue;
		tem = findTotal(i+1,end,b1-1,cost);
		if(tem != INT_MAX) tem += cost[start][i];		
		else continue;
		if(tem < min) min = tem;
	}
	return min;
}

int** findMaximum(int *arr,int n){
	int **matrix,i,j;
    matrix =(int **)malloc(sizeof(int *)*n);
	for(i = 0; i < n; i++) matrix[i] = (int *)malloc(sizeof(int)*n);
	for(i = 0; i < n; i++){
		matrix[i][i] = arr[i];
		for(j = i+1; j < n; j++){
			if(arr[j] > matrix[i][j-1]) matrix[i][j] = arr[j];
			else matrix[i][j] = matrix[i][j-1];
		}
	}
	return matrix;
}

int ** findCost(int * arr, int ** matrix,int n){
	int i,j,**cost;
	cost = (int **)malloc(sizeof(int *)*n);
	for(i = 0 ; i < n ;i++) cost[i] = (int *)malloc(sizeof(int)*n); 
	for(i = 0 ; i < n; i++){
		cost[i][i] = 0;
		for(j = i+1; j < n;j++){
			if(matrix[i][j] == matrix[i][j-1]) cost[i][j] = cost[i][j-1] + matrix[i][j-1]-arr[j];
			else cost[i][j] = (matrix[i][j]-matrix[i][j-1])*(j-i)+cost[i][j-1]; 
		}
	}
	return cost;
}

int main(){
	int n,*arr,b,i;
	FILE *fp1 = fopen("input.txt","r");
	fscanf(fp1,"%d\n",&n);
	arr = (int *)malloc(sizeof(int)*n);
	for(i = 0; i < n; i++) fscanf(fp1,"%d",arr+i);
	fscanf(fp1,"%d",&b);
	int **matrix = findMaximum(arr,n);
	int ** cost = findCost(arr,matrix,n); 
	i = findTotal(0,n-1,b+1,cost);
	fclose(fp1);
	fp1 = fopen("output.txt","w");
	fprintf(fp1,"%d\n",i);
	fclose(fp1);
	return 0;
}