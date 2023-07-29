#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    int rank;
    struct node *p;
};
struct node* makeset(int k)
{
    struct node *t=(struct node*)malloc(sizeof(struct node));
    t->key=k;
    t->rank=0;
    t->p=t;
    return t;
}
struct node* find_set(struct node *x,int *c)
{
    if(x)
    {
        (*c)++;
        if(x->p==x)
        {
            return x;
        }
        return find_set(x->p,c);
    }
}
struct node* find_set_path(struct node *x,int *c)
{
    if(x)
    {
        (*c)++;
        if(x->p==x)
        {
            return x;
        }
        x->p=find_set_path(x->p,c);
        return(x->p);
    }
}
struct node *link(struct node *a,struct node *b)
{
    if(b!=a)
    {
        b->p=a;
        return a;
    }
}
struct node *rank_link(struct node *a,struct node *b)
{
    if(b!=a)
    {
        if(b->rank>a->rank)
        {
            a->p=b;
            return b;
        }
        b->p=a;
        if(a->rank==b->rank)
        {
            a->rank++;
        }
        return a;
    }
}
struct node *union1(struct node *a,struct node *b,int *c)
{
    return link(find_set(a,c),find_set(b,c));
}
struct node *union_rank(struct node *a,struct node *b,int *c)
{
    return rank_link(find_set(a,c),find_set(b,c));
}
struct node *union_path(struct node *a,struct node *b,int *c)
{
    return link(find_set_path(a,c),find_set_path(b,c));
}
struct node *union_rank_path(struct node *a,struct node *b,int *c)
{
    return rank_link(find_set_path(a,c),find_set_path(b,c));
}
int main()
{
    struct node *a1[1001],*a2[1001],*a3[1001],*a4[1001];
    for(int i=0;i<1001;i++)
    {
        a1[i]=a2[i]=a3[i]=a4[i]=NULL;
    }
    char ch;
    int c1=0,c2=0,c3=0,c4=0;
    while(1)
    {
        scanf("%c",&ch);
        int k,m;
        if(ch=='m')
        {
            scanf("%d",&k);
            if(a1[k]!=NULL)
            {
                printf("-1\n");
            }
            else
            {
                a1[k]=makeset(k);
                a2[k]=makeset(k);
                a3[k]=makeset(k);
                a4[k]=makeset(k);
                printf("%d\n",k);
            }
        }
        else if(ch=='f')
        {
            scanf("%d",&k);
            if(a1[k]==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d ",find_set(a1[k],&c1)->key);
                printf("%d ",find_set(a2[k],&c2)->key);
                printf("%d ",find_set_path(a3[k],&c3)->key);
                printf("%d\n",find_set_path(a4[k],&c4)->key);
            }
        }
        else if(ch=='u')
        {
            scanf("%d %d",&k,&m);
            if(a1[k]==NULL)
            {
                printf("-1\n");
            }
            else if(a1[k]==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d ",union1(a1[k],a1[m],&c1)->key);
                printf("%d ",union_rank(a2[k],a2[m],&c2)->key);
                printf("%d ",union_path(a3[k],a3[m],&c3)->key);
                printf("%d\n",union_rank_path(a4[k],a4[m],&c4)->key);
            }    
        }
        else if(ch=='s')
        {
            printf("%d %d %d %d\n",c1,c2,c3,c4);
            break;
        }
    }
    return 0;
}