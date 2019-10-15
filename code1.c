#include<stdio.h>
#include<stdlib.h>
struct node{
	int vertex;
	struct node*next;
};
struct Graph{
	int numVertices;
	struct node**adjLists;
};
typedef struct{
	int from,to,weight;
} Edge;
void IfMerge(Edge * arr,Edge * EdgeCase,int i,int k,int n1){
	 (arr+k)->from=(EdgeCase+n1+i)->from;
     (arr+k)->to=(EdgeCase+n1+i)->to;
     (arr+k)->weight=(EdgeCase+n1+i)->weight;
}
void Merge(Edge *arr,int n1,int mid,int n2){
	Edge * Edge1,* Edge2;
	int k=0,i,j;
	Edge1=(Edge *)malloc(sizeof(Edge)*(mid-n1+1));
	Edge2=(Edge *)malloc(sizeof(Edge)*(n2-mid));
	for(i=0;i<(mid-n1+1);i++){
		(Edge1+i)->from=(arr+n1+i)->from;
		(Edge1+i)->to=(arr+n1+i)->to;
		(Edge1+i)->weight=(arr+n1+i)->weight;
	}
	for(j=0;j<(n2-mid);j++){
		(Edge2+j)->from=(arr+mid+1+j)->from;
		(Edge2+j)->to=(arr+mid+1+j)->to;
		(Edge2+j)->weight=(arr+mid+1+j)->weight;
	}
	i=0,j=0;
	while( i<mid-n1+1 && j<n2-mid  ){
		if((Edge1+i)->from<(Edge2+j)->from){
			IfMerge(arr,Edge1,i,k,n1);
			i++,k++;
		}
		else if((Edge1+i)->from>(Edge2+j)->from){
			IfMerge(arr,Edge2,j,k,n1);
			j++,k++;
		}
		else{
			if((Edge1+i)->weight<(Edge2+j)->weight){
				IfMerge(arr,Edge1,i,k,n1);
				i++,k++;
			}
			else if((Edge1+i)->weight>(Edge2+j)->weight){
				IfMerge(arr,Edge2,j,k,n1);
				j++,k++;
			}
			else{
				if((Edge1+i)->to<=(Edge2+j)->to){
					IfMerge(arr,Edge1,i,k,n1);
					i++,k++;
				}
				else{
					IfMerge(arr,Edge2,j,k,n1);
					j++,k++;
				}
			}
		}
	}
          /* (arr+k)->from=(Edge1+i)->from;
           (arr+k)->to=(Edge1+i)->to;
           (arr+k)->weight=(Edge1+i)->weight;
           i++,k++;
           continue;
		}
		else if((Edge1+i)->from==(Edge2+j)->from){
			if((Edge1+i)->weight<(Edge2+j)->weight){
				(arr+k)->from=(Edge1+i)->from;
           		(arr+k)->to=(Edge1+i)->to;
           		(arr+k)->weight=(Edge1+i)->weight;
          		i++,k++;
           		continue;
			}
			else if((Edge1+i)->weight>(Edge2+j)->weight){
				(arr+k)->from=(Edge2+j)->from;
           		(arr+k)->to=(Edge2+j)->to;
           		(arr+k)->weight=(Edge2+j)->weight;
           		j++,k++;
           		continue;
			}
			else{
				if((Edge1+i)->to<(Edge2+j)->to){
					(arr+k)->from=(Edge1+i)->from;
           			(arr+k)->to=(Edge1+i)->to;
           			(arr+k)->weight=(Edge1+i)->weight;
          			i++,k++;
           			continue;
				}
				else{
					(arr+k)->from=(Edge2+j)->from;
           			(arr+k)->to=(Edge2+j)->to;
           			(arr+k)->weight=(Edge2+j)->weight;
           			j++,k++;
           			continue;
				}
			}
		}
		else{
			(arr+k)->from=(Edge2+j)->from;
           (arr+k)->to=(Edge2+j)->to;
           (arr+k)->weight=(Edge2+j)->weight;
           j++,k++;
           continue;
		}
	}*/
	if(i==mid-n1+1){
		while(j<n2-mid){
			(arr+k+n1)->from=(Edge2+j)->from;
           	(arr+n1+k)->to=(Edge2+j)->to;
           	(arr+k+n1)->weight=(Edge2+j)->weight;
           	j++,k++;
		}
	}
	else{
		while(i<mid-n1+1){
		(arr+k+n1)->from=(Edge1+i)->from;
        (arr+k+n1)->to=(Edge1+i)->to;
        (arr+k+n1)->weight=(Edge1+i)->weight;
        i++,k++;
        }
	}
	free(Edge1);
	free(Edge2);
	return;
}
void MergeSort(Edge *arr,int n1,int n2){
	int mid=(n1+n2)/2;
	if(n1==n2) return ;
	MergeSort(arr,n1,mid);
	MergeSort(arr,mid+1,n2);
	Merge(arr,n1,mid,n2);
	return ;
}
struct node * createNode(int vertex){
	struct node * tem=(struct node *)malloc(sizeof(struct node));
	tem->vertex=vertex;
	tem->next=NULL;
	return tem;
}
struct Graph * createGraph(int numVertices){
	int i=0;
	struct Graph * tem = (struct  Graph *)malloc(sizeof(struct Graph));
	tem->numVertices=numVertices;
	tem->adjLists=(struct node **) malloc(sizeof(struct node *) * numVertices);
	while(i < numVertices) 
	{
		tem->adjLists[i]=NULL;
		i++;
	}
	return tem;
}
int main(){
	int numVertices,numEdges,n1,n2,i,*arr;
	struct Graph * G;
	struct node * n,* temn;	
	FILE * fp1=fopen("input.txt","r");
	fscanf(fp1,"%d %d",&numVertices, &numEdges);
	Edge E1[numEdges];
	G = createGraph(numVertices);
	for(i=0;i<numEdges;i++){
		fscanf(fp1,"%d%d",&n1,&n2);
		n=createNode(n2-1);
		temn=G->adjLists[n1-1];
		G->adjLists[n1-1]=n;
		n->next=temn;
	}
	fclose(fp1);
	for(i=0,n1=0;i<numVertices;i++){
		temn=*((G->adjLists)+i);
		while(temn!=NULL){
			(E1+n1)->from=i+1;
			(E1+n1)->to=temn->vertex+1;
			temn=temn->next;
			n1++;
		}
	}
	arr=(int *)calloc(sizeof(int),numVertices);
	for(i=0;i<numEdges;i++)		(*(arr+((E1+i)->to)-1))++;
	for(i=0;i<numEdges;i++) (E1+i)->weight=(*(arr+((E1+i)->from-1)))+(*(arr+((E1+i)->to-1)));
	MergeSort(E1,0,numEdges-1);
	fp1=fopen("output.txt","w");
	for(i=0;i<numEdges;i++){
		fprintf(fp1,"%5d %5d %5d\n",(E1+i)->from,(E1+i)->weight,(E1+i)->to);
	}
	fclose(fp1);
	return 3;
}