#include <stdio.h>
#include <stdlib.h>
struct queue
{
    int elems[100];
    int head;
    int tail;
};
struct node
{
    int vertex;
    char colour;
    int d;
    struct node *anc;

};
struct graph
{
    int vertices;
    struct node **adj_list;
};
struct node *create_node(int k)
{
    struct node *link=(struct node*)malloc(sizeof(struct node));
    link->vertex=k;
    link->colour='w';
    link->d=10000;
    link->anc=NULL;
    return link;
}
struct graph* create_graph(int n)
{
    struct graph* g=(struct graph*)malloc(sizeof(struct graph));
    g->vertices=n;
    g->adj_list=(struct node**)malloc(n*sizeof(struct node));
    for(int i=0;i<n;i++)
    {
        g->adj_list[i]=NULL;
    }
    return g;
}
struct queue* create_queue()
{
    struct queue *q=(struct queue*)malloc(sizeof(struct queue));
    q->head=q->tail=0;
    return q;
}
void enqueue(struct queue *q,int k)
{
    if((q->head==q->tail+1)|| (q->tail==99 && q->head==0))
    {
        return;
    }
    q->elems[q->tail]=k;
    if(q->tail==99)
    {
        q->tail=0;
        return;
    }
    q->tail++;
    return;
}
int dequeue(struct queue *q)
{
    if(q->head==q->tail)
    {
        return -1;
    }
    int t=q->elems[q->head];
    if(q->head==99)
    {
        q->head=0;
        return t;
    }
    q->head++;
    return t;
}
int isempty(struct queue *q)
{
    if((q->head==q->tail))
    {
        return 1;
    }
    return 0;
}
void bfs(struct graph *g,struct node *arr[])
{
    struct queue *q=create_queue();
    arr[0]->colour='g';
    arr[0]->d=0;
    enqueue(q,arr[0]->vertex);
    while(!isempty(q))
    {
        int u=dequeue(q);
        printf("%d ",u);
        struct node *v=g->adj_list[u];
        while(v)
        {
            struct node *temp=arr[v->vertex];
            if(temp->colour=='w')
            {
                temp->colour='g';
                temp->d=arr[u]->d+1;
                temp->anc=arr[u];
                enqueue(q,v->vertex);
            }
            v=v->anc;
        }
        arr[u]->colour='b';
    }
}
void add_vertices(struct graph *g,int a,int b)
{
    struct node *t=create_node(b);
    struct node *tail=g->adj_list[a];
    if(!tail)
    {
        g->adj_list[a]=t;
        return;
    }
    while(tail->anc)
    {
        tail=tail->anc;
    }
    tail->anc=t;
    return;
}
int main()
{
    char ch;
    int n,k;
    scanf("%d",&n);
    struct node *arr[n];
    struct graph* g=create_graph(n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%c",&k,&ch);
        arr[i]=create_node(i);
        while(1)
        {
            //printf("entered\n");
            scanf("%d%c",&k,&ch);
            add_vertices(g,i,k);
            if(ch=='\n')
            {
                break;
            }
    
        }
    }
    bfs(g,arr);
    printf("\n");
    return 0;
}