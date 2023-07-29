#include <stdio.h>
struct heap
{
    int h[10000];
    int n;
};
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void min_heapify(struct heap *H,int i)
{
    int l=2*i+1;
    int r=2*i+2;
    int small=i;
    if(l<(H->n) && H->h[small]>H->h[l])
    {
        small=l;
    }
    if(l<(H->n) && H->h[small]>H->h[r])
    {
        small=r;
    }
    if(small!=i)
    {
        swap(&H->h[small],&H->h[i]);
        min_heapify(H,small);
    }
}
int extract_min(struct heap *H)
{
    if(H->n!=0)
    {
        int min=H->h[0];
        H->h[0]=H->h[H->n-1];
        H->n--;
        min_heapify(H,0);
        return min; 
    }
}
void insert(struct heap *H,int x)
{
    H->h[(H->n)++]=x;
    int i=(H->n)-1;
    int p=(i-1)/2;
    while(p>=0 && H->h[p]>x)
    {
        swap(&H->h[p],&H->h[i]);
        i=p;
        p=(i-1)/2;
    }
    return;
}
int main()
{
    struct heap *H,heap;
    H=&heap;
    int n,k,key,m;
    scanf("%d",&n);
    int i=0;
    while(i<n)
    {
        i++;
        scanf("%d",&m);
        H->n=m;
        for(int j=0;j<m;j++)
        {
            scanf("%d",&key);
            key=-key;
            insert(H,key);
        }
        scanf("%d",&k);
        for(int j=0;j<k;j++)
        {
            int t=extract_min(H);
            t=-t;
            printf("%d ",t);
        }
        for(int j=0;j<m;j++)
        {
            H->h[j]=0;
        }
        printf("\n");
    }
    return 0;
}