#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000001
#define MIN -1000000001
struct node
{
int key;
struct node *p;
struct node *child;
struct node *sibling;
int degree;
};
struct heap
{
    struct node *head;
};
struct node *print(struct node *x,int c)
{
   if(x)
   {
        if(c==0)
        {
            printf("%d ",x->key);
            print(x->sibling,c);
        }
        else if(c>0)
        {
            print(x->child,c-1);
        }
    }
}
struct node *create_node(int k)
{
    struct node *l=(struct node*)malloc(sizeof(struct node));
    l->key=k;
    l->p=l->child=l->sibling=NULL;
    l->degree=0;
    return l;
}
struct heap* make_heap()
{
    struct heap* h=(struct heap*)malloc(sizeof(struct heap));
    h->head=NULL;
    return h;
}
struct node *search(struct node *x,int k)
{
    if(!x)
    {
        return NULL;
    }
    if(x->key>k)
    {
        return search(x->sibling,k);
    }
    else if(x->key==k)
    {
        return x;
    }
    else
    {
        struct node *temp=search(x->child,k);
        if(!temp)
        {
            return search(x->sibling,k);
        }
        return temp;
    }
}
struct node *binomial_min(struct heap *h)
{
    struct node *y,*x;
    y=NULL;
    x=h->head;
    int min=MAX;
    while(x)
    {
        if(x->key<min)
        {
            min=x->key;
            y=x;
        }
        x=x->sibling;
    }
    return y;
}
struct node *binomial_link(struct node *y,struct node *z)
{
    y->p=z;
    y->sibling=z->child;
    z->child=y;
    z->degree++;
    return z;
}
struct node *binomial_heap_merge(struct heap *h1, struct heap *h2)
{
    struct node *link=NULL;
    struct node *l1=h1->head,*l2=h2->head,*temp=NULL;
    while(l1 && l2)
    {
        if(l1->degree<=l2->degree)
        {
            if(!link)
            {
                link=l1;
            }
            else
            {
                temp->sibling=l1;
            }
            temp=l1;
            l1=l1->sibling;
        }
        else
        {
            if(!link)
            {
                link=l2;
            }
            else
            {
                temp->sibling=l2;
            }
            temp=l2;
            l2=l2->sibling;
        }
    }
    if(l1)
    {
        if(!link)
        {
            link=l1;
        }
        else
        {
            temp->sibling=l1;
        }
    }
    if(l2)
    {
        if(!link)
        {
            link=l2;
        }
        else
        {
            temp->sibling=l2;
        }
    }
    return link;
}
struct heap *binomial_heap_union(struct heap *h1,struct heap *h2)
{
    struct heap *h=make_heap();
    h->head=binomial_heap_merge(h1,h2);
    // print(h->head,0);
    // printf("\n");
    free(h1);
    free(h2);
    if(!h->head)
    {
        return h;
    }
    struct node *x=h->head;
    struct node *next=x->sibling,*prev=NULL;
    while(next)
    {
        if((x->degree!=next->degree)||(next->sibling && next->sibling->degree==x->degree))
        {
            prev=x;
            x=next;
        }
        else if(x->key<=next->key)
        {
            x->sibling=next->sibling;
            binomial_link(next,x);

        }
        else 
        {
            if(!prev)
            {
                h->head=next;
            }
            else
            {
                prev->sibling=next;
            }
            binomial_link(x,next);
            x=next;
        }
        next=x->sibling;
    }
    return h;
}
struct heap* binomial_heap_insert(struct heap *h,struct node *x)
{
    struct heap *temp=make_heap();
    temp->head=x;
    h=binomial_heap_union(h,temp);
    return h;
}
struct heap *binomial_heap_extract(struct heap *h)
{
    struct node *temp=h->head,*min=NULL,*temp2=NULL;
    min=binomial_min(h);
    if(min)
    {
        temp=h->head;
        if(h->head==min)
        {
            h->head=temp->sibling;
        }
        else
        {
            while(temp->sibling)
            {
                if(temp->sibling==min)
                {
                    temp->sibling=min->sibling;
                    break;
                }
                temp=temp->sibling;
            }
        }
        min->sibling=NULL;
        temp=min->child;
        struct heap *link=make_heap();
        while(temp)
        {
            temp->p=NULL;
            temp2=temp->sibling;
            temp->sibling=link->head;
            link->head=temp;
            temp=temp2;
        } 
        h=binomial_heap_union(h,link);
    }
    free(min);
    return h;
}
void binomial_heap_decrease_key(struct heap *h,struct node *x,int k)
{
    if(!x || k>x->key)
    {
        return;
    }  
    x->key=k;
    struct node *y=x,*z=NULL;
    z=y->p;
    while(z && y->key<z->key)
    {
        int temp=z->key;
        z->key=y->key;
        y->key=temp;
        y=z;
        z=z->p;
    }
}

struct heap * binomial_heap_delete(struct heap *h,struct node *x)
{
    binomial_heap_decrease_key(h,x,MIN);
    h=binomial_heap_extract(h);
    return h;
}

void print_root_list(struct heap *h)
{
    struct node *x=h->head;
    while(x)
    {
        printf("%d ",x->key);
        x=x->sibling;
    }
}
int main()
{
    struct heap *h1,*h2;
    h1=make_heap();
    h2=make_heap();
    char ch;
    int m,k;
    struct node *temp=NULL;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='i')
        {
            scanf("%d",&k);
            h1=binomial_heap_insert(h1,create_node(k));
        }
        else if(ch=='j')
        {
            scanf("%d",&k);
            h2=binomial_heap_insert(h2,create_node(k));
        }
        // else if (ch=='p')
        // {
        //     scanf("%d",&k);
        //     if(k==1)
        //     {
        //         struct node *x=h1->head;
        //         while(x && x->sibling)
        //         {
        //             x=x->sibling;
        //         }
        //         int d=x->degree;
        //         //printf("degree=%d\n",d);
        //         for(int i=0;i<=d;i++)
        //         {
        //             x=h1->head;
        //             if(i==0)
        //             {
        //                 print(x,i);
        //                 continue;
        //             }
        //             while(x)
        //             {
        //                 print(x,i);
        //                 x=x->sibling;
        //             }
        //         }
        //     }
        //     else if(k==2)
        //     {
        //         struct node *x=h2->head;
        //         while(x && x->sibling)
        //         {
        //             x=x->sibling;
        //         }
        //         int d=x->degree;
        //         //printf("degree=%d\n",d);
        //         for(int i=0;i<=d;i++)
        //         {
        //             x=h2->head;
        //             if(i==0)
        //             {
        //                 print(x,i);
        //                 continue;
        //             }
        //             while(x)
        //             {
        //                 print(x,i);
        //                 x=x->sibling;
        //             }
        //         }
        //     }
        //     printf("\n");
        // }
        else if(ch=='p')
        {
            scanf("%d",&k);
            if(k==1)
            {
                print_root_list(h1);
            }
            else
            {
                print_root_list(h2);
            }
            printf("\n");
        }
        else if(ch=='m')
        {
            printf("%d\n",binomial_min(h1)->key);
        }
        else if(ch=='c')
        {
            struct node *x=h1->head;
            while(x && x->sibling)
            {
                x=x->sibling;
            }
            int d=x->degree;
            //printf("degree=%d\n",d);
            for(int i=0;i<=d;i++)
            {
                x=h1->head;
                if(i==0)
                {
                    print(x,i);
                    continue;
                }
                while(x)
                {
                    print(x,i);
                    x=x->sibling;
                }
            }
            printf("\n");
        }
        else if(ch=='x')
        {
            struct node *min=binomial_min(h1);
            if(min)
            {
                printf("%d\n",min->key);
                h1=binomial_heap_extract(h1);
            } 
            else
            {
                printf("-1\n");
            }    
        }
        else if(ch=='s')
        {
            scanf("%d",&k);
            temp=search(h1->head,k);
            if(temp)
            {

                printf("found %d\n",temp->key);
            }
            else
            {
                printf("NOT FOUND\n");
            }
        }
        else if(ch=='r')
        {
            scanf("%d %d",&k,&m);
            temp=search(h1->head,k);
            if(!temp || (m>k))
            {
                printf("-1\n");
            }
            else
            {
                binomial_heap_decrease_key(h1,temp,m);
                printf("%d\n",m);
            }
        }
        else if(ch=='d')
        {
            scanf("%d",&k);
            temp=search(h1->head,k);
            if(!temp)
            {
                printf("-1\n");
            }
            else
            {
                h1=binomial_heap_delete(h1,temp);
                printf("%d\n",k);
            }
        }
        else if(ch=='u')
        {
            h1=binomial_heap_union(h1,h2);
            print_root_list(h1);
            printf("\n");
        }
        else if(ch=='e')
        {
            break;
        }
    }
}

