#include <stdio.h>
struct heap
{
    int h[10000];
    int n;
};
int find_min(struct heap *H)
{
    if(H->n!=0)
    {
        return H->h[0];
    }
}
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
int decrease_key(struct heap *H,int x,int k)
{
    if(k>=x)
    {
        return -1;
    }
    int i=0;
    while(H->h[i]!=x && i<(H->n))
    {
        i++;
    }
    if(i==H->n)
    {
        return -1;
    }
    int index=i;
    H->h[i]=k;
    int p=(i-1)/2;
    while( p>=0 && H->h[p]>k)
    {
        swap(&H->h[p],&H->h[i]);
        i=p;
        p=(i-1)/2;
    }
    return index;
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
int delete(struct heap *H,int x)
{
    if(decrease_key(H,x,-10000000)==-1)
    {
        return -1;
    }
    extract_min(H);
    return x;
}
void print_heap(struct heap *H)
{
    for(int i=0;i<H->n;i++)
    {
        printf("%d ",H->h[i]);
    }
}
int main()
{
    struct heap *H,heap;
    H=&heap;
    H->n=0;
    for(int i=0;i<10000;i++)
    {
        H->h[i]=0;
    }
    char ch;
    int x,k;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='i')
        {
            scanf("%d",&x);
            insert(H,x);
        }
        else if(ch=='d')
        {
            scanf("%d",&x);
            printf("%d\n",delete(H,x));
        }
        else if(ch=='r')
        {
            scanf("%d",&x);
            scanf("%d",&k);
            if(decrease_key(H,x,k)==-1)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n",k);
            }
        }
        else if(ch=='p')
        {
            print_heap(H);
            printf("\n");
        }
        else if(ch=='x')
        {
            extract_min(H);
            print_heap(H);
            printf("\n");
            
        }
        else if(ch=='g')
        {
            printf("%d\n",find_min(H));
        }
        else if(ch=='e')
        {
            break;
        }
    }
    return 0;
}