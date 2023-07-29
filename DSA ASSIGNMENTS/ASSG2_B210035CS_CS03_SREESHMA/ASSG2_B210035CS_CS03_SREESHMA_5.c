#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int key;
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
struct node *minimum(struct node *r)
{
    if(r==NULL)
    {
        return NULL;
    }
    while(r->left!=NULL)
    {
        r=r->left;
    }
    return r;
}
struct node *maximum(struct node *r)
{
    if(r==NULL)
    {
        return NULL;
    }
    else 
    {
        while(r->right!=NULL)
        {
            r=r->right;
        }
    }
    return r;
}
// struct node *pred(struct node *r,int x)
// {
//     if(r==NULL)
//     {
//         return NULL;
//     }
//     if(r->key==x)
//     {
//         if(r->left!=NULL)
//         {
//             return maximum(r->left);
//         }
//     }
//     else if(x<r->key)
//     {
//         return pred(r->left,x);
//     }
//     else
//     {
//         struct node *t= pred(r->right,x);
//         if(t==NULL)
//         {
//             return r;
//         }
//         else
//         {
//             return t;
//         }
//     }
//     return r;
// }
// struct node *pred(struct node *r,int x,struct node **pre)
// {
//     if(r==NULL)
//     {
//         return NULL;
//     }
//     if(r->key==x)
//     {
//         if(r->left!=NULL)
//         {
//             *pre=maximum(r->left);
//         }
//     }
//     else if(x<r->key)
//     {
//         return pred(r->left,x);
//     }
//     else
//     {
//         struct node *t= pred(r->right,x);
//         if(t==NULL)
//         {
//             return r;
//         }
//         else
//         {
//             return t;
//         }
//     }
//     return r;
// }
struct node *pred(struct node *r,struct node *x)
{
    //printf("%d %d\n",r->key,x->key);
    if(r==NULL)
    {
        return NULL;
    }
    if(r->key==x->key)
    {
        return maximum(r->left);
    }
    else if(r->key>x->key)
    {
        return pred(r->left,x);
    }
    else
    {
        struct node *t=pred(r->right,x);
        if(t==NULL)
        {
            return r;
        }
        return t;
    }
    return r;
}
struct node *search(struct node* x,int k)
{
    if(x==NULL)
    {
        return NULL;
    }
    if(x->key==k)
    {
        return x;
    }
    else if(x->key>k)
    {
        search(x->left,k);
    }
    else
    {
        search(x->right,k);
    }
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
    return r;
}
void avl_tree_insert(struct tree *pt,struct node *x)
{
    pt->root=avl_insert(pt->root,x);
}
struct node* avl_delete(struct tree *pt,struct node *r,struct node *x)
{
    if(r==NULL)
    {
        return NULL;
    }
    if(r->key>x->key)
    {
        r->left=avl_delete(pt,r->left,x);
    }
    else if(r->key<x->key)
    {
        r->right=avl_delete(pt,r->right,x);
    }
    else
    {
        if(r->left==NULL && r->right==NULL)
        {
            return NULL;
        }
        if(r->left==NULL)
        {
            struct node *a=r->right;
            r->right=NULL;
            return a;
        }
        else if(r->right==NULL)
        {
            struct node *a=r->left;
            r->left=NULL;
            return a;
        }
        struct node *a=pred(r,r);
        //printf("done\n");
        struct node *bl=avl_delete(pt,r,a);
        a->left=r->left;
        a->right=r->right;
        r->right=r->left=NULL;
        {
            return a;
        }
    }
}
void avl_tree_delete(struct tree *pt,struct node *x)
{
    pt->root=avl_delete(pt,pt->root,x);
}
void print(struct node *x)
{
    printf("( ");
    if(x!=NULL)
    {
        printf("%d ",x->key);
        print(x->left);
        print(x->right);
    }
    printf(") ");
}
void inorder(struct node *x)
{
    if(x!=NULL)
    {
        inorder(x->left);
        printf("%d ",x->key);
        inorder(x->right);
    }
}
int main()
{
    struct tree *pt=(struct tree*)malloc(sizeof(struct tree));
    pt->root=NULL;
    char ch;
    int k;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='i')
        {
            scanf("%d",&k);
            struct node *link=create_node(k);
            avl_tree_insert(pt,link);
        }
        else if(ch=='d')
        {
            scanf("%d",&k);
            struct node *x=search(pt->root,k);
            if(x==NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                avl_tree_delete(pt,x);
                printf("%d\n",k);
            }
        }
        else if(ch=='s')
        {
            scanf("%d",&k);
            if(search(pt->root,k))
            {
                printf("TRUE\n");
            }
            else
            {
                printf("FALSE\n");
            }
        }
        else if(ch=='r')
        {
            scanf("%d",&k);
            struct node *x=search(pt->root,k);
            if(x==NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                struct node *temp=pred(pt->root,x);
                if(temp!=NULL)
                {
                    printf("%d\n",temp->key);
                }
                else
                {
                    printf("FALSE\n");
                }
            }
        }
        else if(ch=='b')
        {
            scanf("%d",&k);
            struct node *x=search(pt->root,k);
            if(x==NULL)
            {
                printf("FALSE\n");
            }
            else
            {
                printf("%d\n",get_balance(x));
            }
        }
        else if(ch=='p')
        {
            print(pt->root);
            printf("\n");
        }
        else if(ch=='o')
        {
            inorder(pt->root);
            printf("\n");
        }
        else if(ch=='e')
        {
            break;
        }
    }
}