#include <stdio.h>
#include <stdlib.h>
struct ht
{
    int key;
    int freq;
    struct ht *next;
};
struct ht* create_node(int k)
{
    struct ht* link=(struct ht*)malloc(sizeof(struct ht));
    link->key=k;
    link->freq=1;
    link->next=NULL;
    return link;
}
void insert(struct ht *a[],int k,int val)
{
    struct ht *x=a[val];
    int check=0;
    while(x !=NULL)
    {
        if(x->key==k)
        {
            (x->freq)++;
            check=1;
            break;
        }
        x=x->next;
    }
    if(check==0)
    {
        struct ht *link=create_node(k);
        link->next=a[val];
        a[val]=link;
    }
}
int check_equal(struct ht *a[],int b[],int n)
{
    int i,k;
    struct ht *p;
    for(i=0;i<n;i++)
    {
        int check=0;
        k=b[i];
        p=a[k%10];
        while(p!=NULL)
        {
            if(p->key==k)
            {
                if(p->freq==0)
                {
                    return 0;
                }
                check=1;
                (p->freq)--;
                break;
            }
            p=p->next;
        }
        if(check==0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    scanf("%d",&n);
    struct ht *a[10];
    for(int i=0;i<10;i++)
    {
        a[i]=NULL;
    }
    int i,j=0,k,p,b[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&k);
        int val=k%10;
        insert(a,k,val);
    }
    for(i=0;i<n;i++)
    {
        scanf("%d",&b[i]);
    }
    printf("%d\n",check_equal(a,b,n));
}