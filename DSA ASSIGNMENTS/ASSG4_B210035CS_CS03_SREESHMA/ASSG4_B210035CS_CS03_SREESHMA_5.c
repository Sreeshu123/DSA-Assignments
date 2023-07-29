#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct vertex
{
    int v;
    int check;
    int weight;
};
struct vertex *create_vertex(int k)
{
    struct vertex *link=(struct vertex*)malloc(sizeof(struct vertex));
    link->v=k;
    link->weight=100000001;
    link->check=0;
    return link;
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
struct vertex** apsp(int matrix[][100],int v,int s)
{
    struct vertex* loc[v];
    struct vertex* visited[v];
    for(int i=0;i<v;i++)
    {
        loc[i]=create_vertex(i);
        visited[i]=loc[i];
    }
    decrease_key(loc,visited[s],0,v);
    int n=v;
    while(n)
    {
        struct vertex *u=extract_min(loc,&n);
        visited[u->v]->check=1;
        for(int i=0;i<v;i++)
        {
            int w=matrix[u->v][i];
            if(w!=-1)
            {
                if(visited[i]->check==0 && (w+u->weight)<visited[i]->weight)
                {
                    //printf("key=%d i=%d weight=%d\n",visited[i]->v,u->v,visited[i]->weight);
                    decrease_key(loc,visited[i],w+u->weight,n);
                }
            }
        }
    }
    for(int i=0;i<v;i++)
    {
        if(visited[i]->weight==100000001)
        {
            printf("INF ");
        }
        else
        {
            printf("%d ",visited[i]->weight);
        }
    }
    printf("\n");
}
void print_matrix(int matrix[][100],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}
int sssp(int matrix[][100],int v,int s,int target)
{
    struct vertex* loc[v];
    struct vertex* visited[v];
    for(int i=0;i<v;i++)
    {
        loc[i]=create_vertex(i);
        visited[i]=loc[i];
    }
    decrease_key(loc,visited[s],0,v);
    int n=v;
    while(n)
    {
        struct vertex *u=extract_min(loc,&n);
        if(u->v==target)
        {
            return u->weight;
        }
        visited[u->v]->check=1;
        for(int i=0;i<v;i++)
        {
            int w=matrix[u->v][i];
            if(w!=-1)
            {
                if(visited[i]->check==0 && (w+u->weight)<visited[i]->weight)
                {
                    //printf("key=%d i=%d weight=%d\n",visited[i]->v,u->v,visited[i]->weight);
                    decrease_key(loc,visited[i],w+u->weight,n);
                }
            }
        }
    }
    for(int i=0;i<v;i++)
    {
        if(visited[i]->weight==100000001)
        {
            printf("INF ");
        }
        else
        {
            printf("%d ",visited[i]->weight);
        }
    }
    printf("\n");
}
int main()
{
    int n,k;
    char junk;
    struct edge* edges[1000];
    scanf("%d",&n);
    int matrix[n][100];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            matrix[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d%c",&k,&junk);
        if(junk=='\n')
        {
            continue;
        }
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
   //print_matrix(matrix,n);

    for(int i=0;i<n;i++)
    {
        scanf("%d%c",&k,&junk);
        int j=0;
        if(junk=='\n')
        {
            continue;
        }
        while(1)
        {
            scanf("%d%c",&k,&junk);
            while(matrix[i][j]==-1)
            {
                j++;
            }
            matrix[i][j]=k;
            j++;
            if(junk=='\n')
            {
                break;
            }
        }
    }
    //print_matrix(matrix,n);
    

    char str[5];
    int m;
    while(1)
    {
        scanf("%s",str);
        if(strcmp(str,"stop")==0)
        {
            break;
        }
        else if(strcmp(str,"apsp")==0)
        {
            scanf("%d",&k);
            apsp(matrix,n,k);
        }
        else if(strcmp(str,"sssp")==0)
        {
            scanf("%d %d",&k,&m);
            int res=sssp(matrix,n,k,m);
            if(res==100000001)
            {
                printf("UNREACHABLE\n");
            }
            else
            {
                printf("%d\n",res);
            }
        }

    }
    return 0;
}