#include<stdio.h>
#include<stdlib.h>
struct node 
{
    int vertex;
    struct node *p;
    int rank;
};
struct vertex
{
    int v;
    int check;
    int weight;
};
struct edge
{
    int u;
    int v;
    int weight;
};
struct node *create_node(int k)
{
    struct node *link=(struct node*)malloc(sizeof(struct node));
    link->vertex=k;
    link->p=link;
    link->rank=1;
    return link;
}
struct edge *create_edge(int a,int b,int w)
{
    struct edge *link=(struct edge*)malloc(sizeof(struct edge));
    link->u=a;
    link->v=b;
    link->weight=w;
    return link;
}
struct vertex *create_vertex(int k)
{
    struct vertex *link=(struct vertex*)malloc(sizeof(struct vertex));
    link->v=k;
    link->weight=100000001;
    link->check=0;
    return link;
}
struct node *find_set(struct node *x)
{
    if(x->p==x)
    {
        return x;
    }
    x->p=find_set(x->p);
    return (x->p);
}
struct node *union_rank(struct node *t1,struct node *t2)
{
    if(t1->rank<t2->rank)
    {
        t1->p=t2;
        return t2;
    }
    t2->p=t1;
    if(t1->rank==t2->rank)
    {
        t1->rank++;
    }
    return t1;
}
void sort_weight(struct edge* arr[],int n)
{
    for(int i=1;i<n;i++)
    {
        struct edge *temp=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]->weight>temp->weight)
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
}
void print(struct edge *arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d %d %d\n",arr[i]->u,arr[i]->v,arr[i]->weight);
    }
}
void min_heapify(struct vertex *a[],int i,int n)
{
    int l=2*i+1;
    int r=2*i+2;
    int small=i;
    if(l<n && a[small]->weight>a[l]->weight)
    {
        small=l;
    }
    if(r<n && a[small]->weight>a[r]->weight)
    {
        small=r;
    }
    if(small!=i)
    {
        struct vertex *temp=a[small];
        a[small]=a[i];
        a[i]=temp;
        min_heapify(a,small,n);
    }
}
struct vertex* extract_min(struct vertex *a[],int *n)
{
    struct vertex *min=a[0];
    (*n)--;
    a[0]=a[(*n)];
    min_heapify(a,0,(*n));
    return min;
}
void decrease_key(struct vertex *a[],struct vertex *t,int w,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(a[i]==t)
        {
            break;
        }
    }
    a[i]->weight=w;
    int p=(i-1)/2;
    while(p>=0 && a[p]->weight>a[i]->weight)
    {
        struct vertex *temp=a[p];
        a[p]=a[i];
        a[i]=temp;
        i=p;
        p=(i-1)/2;
    }
}
int kruskal(struct edge* edges[],int n,int v)
{
    struct node* loc[v];
    //print(edges,n);
    //printf("\n");
    sort_weight(edges,n);
    //print(edges,n);
    for(int i=0;i<v;i++)
    {
        loc[i]=create_node(i);
    }
    int sum=0;
    for(int i=0;i<n;i++)
    {
        struct node *t1=loc[edges[i]->u];
        struct node *t2=loc[edges[i]->v];
        struct node *rep1=find_set(t1);
        struct node *rep2=find_set(t2);
        if(rep1!=rep2)
        {
            //printf("%d %d %d\n",edges[i]->u,edges[i]->v,edges[i]->weight);
            sum+=edges[i]->weight;
            union_rank(rep1,rep2);
        }
    }
    return sum;
}
int prim(int matrix[][100],int v)
{
    struct vertex* loc[v];
    struct vertex* visited[v];
    for(int i=0;i<v;i++)
    {
        loc[i]=create_vertex(i);
        visited[i]=loc[i];
    }
    int sum=0;
    visited[0]->weight=0;
    int n=v;
    while(n)
    {
        struct vertex *u=extract_min(loc,&n);
        visited[u->v]->check=1;
        sum+=u->weight;
        for(int i=0;i<v;i++)
        {
            int w=matrix[u->v][i];
            if(w!=0)
            {
                if(visited[i]->check==0 && w<visited[i]->weight)
                {
                    decrease_key(loc,visited[i],w,n);
                }
            }
        }
    }
    return sum;
}
int main()
{
    int n,k,len=0;
    char ch,junk;
    struct edge* edges[1000];
    scanf("%c\n%d",&ch,&n);
    int matrix[n][100];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            matrix[i][j]=0;
        }
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d%c",&k,&junk);
        while(1)
        {
            scanf("%d%c",&k,&junk);
            matrix[i][k]=1;
            if(junk=='\n')
            {
                break;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d%c",&k,&junk);
        int j=0;
        while(1)
        {
            scanf("%d%c",&k,&junk);
            while(matrix[i][j]==0)
            {
                j++;
            }
            if(j>i && ch=='a')    
            {
                edges[len++]=create_edge(i,j,k);
            }
            matrix[i][j]=matrix[j][i]=k;
            j++;
            if(junk=='\n')
            {
                break;
            }
        }
    }
    if(ch=='a')
    {
        printf("%d\n",kruskal(edges,len,n));
    }
    else if(ch=='b')
    {
        printf("%d\n",prim(matrix,n));
    }
    return 0;
}