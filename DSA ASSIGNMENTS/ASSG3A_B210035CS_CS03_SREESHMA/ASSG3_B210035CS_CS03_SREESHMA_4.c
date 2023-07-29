#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *next;
};
struct ll
{
    struct node *head;
};
struct node* create_node(int k)
{
    struct node *link=(struct node*)malloc(sizeof(struct node));
    link->key=k;
    link->next=NULL;
    return link;
}
void insert(struct ll *pt,int k)
{
    struct node *t=create_node(k);
    struct node *ptr=pt->head,*ptr1=NULL;
    while(ptr!=NULL && ptr->key<k)
    {
        ptr1=ptr;
        ptr=ptr->next;
    }
    if(ptr1==NULL)
    {
        pt->head=t;
    }
    else
    {
        ptr1->next=t;
    }
    t->next=ptr;
    return;
}
struct node* extract(struct ll *pt)
{
    struct node *t=pt->head;
    if(t)
    {
        pt->head=t->next;
    }
    return t;
}
int find_cost(struct ll *pt)
{
    int cost=0;
    int c=0;
    while(1)
    {
        struct node *t1=extract(pt),*t2;
        if(t1)
        {
            t2=extract(pt);
            if(t2)
            {
                c=t1->key+t2->key;
                cost+=c;
                insert(pt,c);
            }
            else
            {
                return cost;
            }
        }
    }
}
int main()
{
    struct ll *pt,ptr;
    pt=&ptr;
    pt->head=NULL;
    int n,key;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&key);
        insert(pt,key);
    }
    printf("%d\n",find_cost(pt));
    return 0;
}