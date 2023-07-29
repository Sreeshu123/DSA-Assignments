#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int key;
    int elems;
    struct node *left;
    struct node *right;
    int height;
};
struct tree
{
    struct node *root;
};
struct node *create_node(int k)
{
    struct node *x=(struct node*)malloc(sizeof(struct node));
    x->key=k;
    x->left=NULL;
    x->right=NULL;
    x->height=0;
    x->elems=1;
    return x;
}
int height(struct node *x)
{
    if(x==NULL)
    {
        return -1;
    }
    return x->height;
}
int max(int a,int b)
{
    return ((a>=b)?a:b);
}
int get_balance(struct node *x)
{
    if(x!=NULL)
    {
        return (height(x->left)-height(x->right));
    }
}
struct node *left_rotate(struct node *x)
{
    struct node *y=x->right;
    struct node *z=y->left;
    y->left=x;
    x->right=z;
    x->height=max(height(x->left)+1,height(x->right)+1);
    y->height=max(height(y->left)+1,height(y->right)+1);
    return y;
}
struct node *right_rotate(struct node *x)
{
    struct node *y=x->left;
    struct node *z=y->right;
    y->right=x;
    x->left=z;
    x->height=max(height(x->left)+1,height(x->right)+1);
    y->height=max(height(y->left)+1,height(y->right)+1);
    return y;
}
int count(struct node *x)
{
    if(x==NULL)
    {
        return 0;
    }
    return (count(x->left)+count(x->right)+1);
}
struct node *avl_insert(struct node *r,struct node *x)
{
    if(r==NULL)
    {
        return x;
    }
    //printf("%d %d\n",x->key,r->key);
    if(r->key<x->key)
    {
        r->right=avl_insert(r->right,x);
    }
    else if(r->key>x->key)
    {
        r->left=avl_insert(r->left,x);
    }
    else
    {
        return r;
    }
    r->height=max(height(r->left)+1,height(r->right)+1);
    int b=get_balance(r);
    if(b>1 )
    {
        if(x->key>r->left->key)
        {
            r->left=left_rotate(r->left);
        }
        return right_rotate(r);
    }
    if(b<-1)
    {
        if( x->key<r->right->key)
        {
            r->right=right_rotate(r->right);
        }
        return left_rotate(r);
    }
    r->elems=count(r);
    //printf("%d\n",r->elems);
    return r;
}
void avl_tree_insert(struct tree *pt,struct node *x)
{
    pt->root=avl_insert(pt->root,x);
}
struct node *find_median(struct node *x,int *c)
{
    if(x!=NULL)
    {
        struct node *t=find_median(x->left,c);
        (*c)--;
        //printf("%d %d\n",x->key,*c);
        if((*c)==0)
        {
            return x;
        }
        if(t==NULL)
        {
            return find_median(x->right,c);
        }
        return t;
    }
}
// struct node *minimum(struct node *r)
// {
//     if(r==NULL)
//     {
//         return NULL;
//     }
//     else 
//     {
//         while(r->left!=NULL)
//         {
//             r=r->left;
//         }
//     }
//     return r;
// }
// struct node *succ(struct node *r,struct node *x)
// {
//     //printf("%d %d\n",r->key,x->key);
//     if(r==NULL)
//     {
//         return NULL;
//     }
//     if(r->key==x->key)
//     {
//         return minimum(r->right);
//     }
//     else if(r->key>x->key)
//     {
//         return succ(r->right,x);
//     }
//     else
//     {
//         struct node *t=succ(r->left,x);
//         if(t==NULL)
//         {
//             return r;
//         }
//         return t;
//     }
//     return r;
// }
// struct node *find_median(struct node *r,int n)
// {
//     if(n%2==0)
//     {
//         return r;
//     }
//     return succ(r,r);
// }
void print(struct node *x)
{
    printf("( ");
    if(x!=NULL)
    {
        printf("%d %d ",x->key,x->elems);
        print(x->left);
        print(x->right);
    }
    printf(") ");
}
int main()
{
    struct tree *pt,ptr;
    pt=&ptr;
    pt->root=NULL;
    char ch;
    int k;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='i')
        {
            scanf("%d",&k);
            struct node *temp=create_node(k);
            avl_tree_insert(pt,temp);
        }
        else if(ch=='g')
        {
            int n=count(pt->root);
            int c;
            if(n%2==0)
            {
                c=n/2;
            }
            else
            {
                c=n/2+1;
            }
            //printf("%d\n",c);
            struct node *link=find_median(pt->root,&c);
            if(link!=NULL)
            {
                printf("%d\n",link->key);
            }
            else
            {
                printf("FALSE\n");
            }
        }
        else if(ch=='p')
        {
            print(pt->root);
            printf("\n");
        }
        else if(ch=='t')
        {
            break;
        }
    }
    return 0;
}