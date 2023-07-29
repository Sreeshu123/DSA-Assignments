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
void dfs(struct graph *g,struct node *arr[],struct queue *q,int i)
{
    if(isempty(q))
    {
        return;
    }
    int u=dequeue(q);
    printf("%d ",u);
    if(g->adj_list[i])
    {
        struct node *temp=g->adj_list[i];
        while(temp)
        {
            if(arr[temp->vertex]->colour=='w')
            {
                enqueue(q,temp->vertex);
                arr[temp->vertex]->colour='b';
                dfs(g,arr,q,temp->vertex);
            }
            g->adj_list[i]=temp->anc;
            temp=temp->anc;
        }
    }
    return;

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
    struct queue *q=create_queue();
    enqueue(q,0);
    arr[0]->colour='b';
    dfs(g,arr,q,0);
    printf("\n");
    return 0;
}