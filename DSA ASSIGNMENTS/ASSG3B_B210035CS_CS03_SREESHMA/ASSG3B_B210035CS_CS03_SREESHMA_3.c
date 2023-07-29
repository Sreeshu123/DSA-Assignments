#include <stdio.h>
#include <stdlib.h>
struct node
{
    int eid;
    int rank;
    struct node *p;
    int elems;
};
struct node* makeset(int k)
{
    struct node *t=(struct node*)malloc(sizeof(struct node));
    t->eid=k;
    t->rank=0;
    t->p=t;
    t->elems=1;
    return t;
}
struct node *rank_link(struct node *a,struct node *b)
{
    if(b!=a)
    {
        if(b->rank>a->rank)
        {
            a->p=b;
            b->elems+=a->elems;
            return b;
        }
        b->p=a;
        a->elems+=b->elems;
        if(a->rank==b->rank)
        {
            a->rank++;
        }
        return a;
    }
}
struct node* find_set_path(struct node *x)
{
    if(x)
    {
        if(x->p==x)
        {
            return x;
        }
        x->p=find_set_path(x->p);
        return(x->p);
    }
    return NULL;
}
struct node *union_rank_path(struct node *a,struct node *b)
{
    return rank_link(a,b);
}
int main()
{
    struct node *arr[10000];
    for(int i=0;i<10000;i++)
    {
        arr[i]=NULL;
    }
    int k,m;
    char ch;
    int group=0;
    int max=-1;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='t')
        {
            struct node *a=NULL,*b=NULL;
            scanf("%d %d",&k,&m);
            if(!arr[k])
            {
                arr[k]=makeset(k);
                if(max<k)
                {
                    max=k;
                }
                a=arr[k];
                group++;
            }
            else
            {
                a=find_set_path(arr[k]);
            }
            if(!arr[m])
            {
                arr[m]=makeset(m);
                if(max<m)
                {
                    max=m;
                }
                b=arr[m];
                group++;
            }
            else
            {
                b=find_set_path(arr[m]);
            }
            if(a!=b)
            {
                //printf("a=%d b=%d\n",a->eid,b->eid);
                if(union_rank_path(a,b)==a)
                {
                    arr[b->eid]=a;
                }
                else
                {
                    arr[a->eid]=b;
                }
                group--;
            }
        }
        else if(ch=='T')
        {
            printf("%d\n",group);
        }
        else if(ch=='v')
        {
            scanf("%d %d",&k,&m);
            if(!(find_set_path(arr[m]))||!(find_set_path(arr[k])))
            {
                printf("-1\n");
            }
            else if(m>k && find_set_path(arr[m])!=find_set_path(arr[k]) && group>1)
            {
               printf("1\n");
            }
            else
            {
                printf("-1\n");
            }
        }
        else if(ch=='d')
        {
            int i=0,g=0;
            int groups[group];
            //printf("max=%d\n",max);
            while(i<=max && g<group)
            {
                if(arr[i] && arr[i]->eid==i)
                {
                    groups[g++]=find_set_path(arr[i])->elems;
                    //printf("eid=%d elems=%d\n",arr[i]->eid,arr[i]->elems);
                }
                i++;
            }
            int sum=0;
            g--;
            while(g>=0)
            {
                //printf("g=%d %d\n",g,groups[g]);
                for(int j=g-1;j>=0;j--)
                {
                    //printf("%d %d\n",groups[j],groups[g]);
                    sum+=groups[j]*groups[g];
                }
                //printf("\n");
                g--;
            }
            if(sum==0)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n",sum);
            }
        }
        else if(ch=='e')
        {
            break;
        }
    }
    return 0;
}