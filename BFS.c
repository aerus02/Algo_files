#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}node;
typedef struct Graph{
    node **head;
    int vertices;
}graph;
node ** adjList(int n){
    node **tem = (node **)malloc(sizeof(node *)*n);
    while(n--) tem[n] = NULL;
    return tem;
}
typedef struct Queue{
    int n,*arr,head,tail;
}queue;
void enqueue(queue * Q,int n){
    Q->arr[Q->head] = n;
    Q->head=(Q->head+1)%Q->n;
}
int dequeue(queue * Q){
    int n = Q->tail;
    Q->tail = (Q->tail+1)%Q->n;
    return Q->arr[n];
}
int isEmpty(queue * Q){
    if(Q->head == Q->tail) return 1;
    else return 0;
}

void BFS(graph * G,int n,int *vis,int *dist,int*par){
    queue Q;
    Q.n = 10;
    Q.head = 0,Q.tail = 0;
    int a[10],m;
    Q.arr = a;
    vis[n] = 1;
    dist[n] = 0;
    enqueue(&Q,n);
    node * p;
    while(!isEmpty(&Q)){
        m = dequeue(&Q);
        p = G->head[m];
        while(p!= NULL){
            if(vis[p->data] == 0){
                vis[p->data] = 1,dist[p->data] = dist[m]+1,par[p->data] = m;
                enqueue(&Q,p->data);
            }
            p = p->next;
        }        
    }
}

void uinsert(node ** head,int n1,int n2){
    node *tem = (node *)malloc(sizeof(node));
    tem->data = n1;
    tem->next=head[n2];
    head[n2]=tem;
    tem = (node *)malloc(sizeof(node));
    tem->data = n2;
    tem->next=head[n1];
    head[n1]=tem;
}
int main(){
    graph G;
    G.vertices = 7;
    int vis[7],dist[7],par[7];
    G.vertices = 7;
    G.head = adjList(7);
    uinsert(G.head,0,1);
    uinsert(G.head,0,2);
    uinsert(G.head,1,3);
    uinsert(G.head,5,3);
    uinsert(G.head,5,2);
    uinsert(G.head,5,6);
    uinsert(G.head,6,4);
    uinsert(G.head,2,4);
    for(int i=0;i<7;i++)      vis[i] = 0,dist[i] = -1,par[i] = i;
    BFS(&G,0,vis,dist,par);
    for(int i=0;i<7;i++) printf("%d %d %d\n",vis[i],dist[i],par[i]);
    return 0;
}
