#include <stdio.h>
#include<stdlib.h>
struct node
{
    int key;
    struct node *p;
    struct node *left;
    struct node *right;
};
struct tree
{
    struct node *root;
    int c;
};
struct node *createnode(int k)
{
    struct node *link=(struct node*)malloc(sizeof(struct node));
    link->key=k;
    link->p=NULL;
    link->left=NULL;
    link->right=NULL;
    return link;
}
struct node *search(struct node *pt,int k)
{
    if(pt==NULL)
    {
        return pt;
    }
    if(pt->key==k)
    {
        return pt;
    }
    else if(pt->key>k)
    {
        search(pt->left,k);
    }
    else
    {
        search(pt->right,k);
    }
}
struct node *findmin(struct node *x)
{
    if(x!=NULL)
    {
        while(x->left!=NULL)
        {
            x=x->left;
        }
    }
    return x;
}
struct node *findmax(struct node *x)
{
    if(x!=NULL)
    {
        while(x->right!=NULL)
        {
            x=x->right;
        }
    }
    return x;
}
void insert(struct tree *pt,int k)
{
    struct node *x=pt->root,*y=NULL,*t;
    t=createnode(k);
    while(x!=NULL)
    {
        y=x;
        if(t->key>x->key)
        {
            x=x->right;
        }
        else
        {
            x=x->left;
        }
    }
    t->p=y;
    if(y==NULL)
    {
        pt->root=t;
    }
    else if(y->key>t->key)
    {
        y->left=t;
    }
    else
    {
        y->right=t;
    }
}
void transplant(struct tree *pt,struct node *u,struct node *v)
{
    if(u->p==NULL)
    {
        pt->root=v;
    }
    else if(u==u->p->left)
    {
        u->p->left=v;
    }
    else
    {
        u->p->right=v;
    }
    if(v!=NULL)
    {
        v->p=u->p;
    }
}
struct node *delete(struct tree *pt,long int k)
{
    struct node *x=search(pt->root,k),*y;
    if(x!=NULL)
    {
        if(x->left==NULL)
        {
            transplant(pt,x,x->right);
        }
        else if(x->right==NULL)
        {
            transplant(pt,x,x->left);
        }
        else
        {
            y=findmin(x->right);
            if(y->p!=x)
            {
                transplant(pt,y,y->right);
                y->right=x->right;
                y->right->p=y;
            }
            transplant(pt,x,y);
            y->left=x->left;
            y->left->p=y;
        }
    }
    return x;
}
struct node *successor(struct node *x)
{
    if(x!=NULL)
    {
        if(x->right!=NULL)
        {
            return findmin(x->right);
        }
        struct node *y=x->p;
        while(y!=NULL && x==y->right)
        {
            x=y;
            y=y->p;
        }
        return y;
    }
    return x;
}
struct node *predecessor(struct node *x)
{
    if(x!=NULL)
    {
        if(x->left!=NULL)
        {
            return findmax(x->left);
        }
        struct node *y=x->p;
        while(y!=NULL && x==y->left)
        {
            x=y;
            y=y->p;
        }
        return y;
    }
    return x;
}
void preorder(struct node *pt)
{
    if(pt!=NULL)
    {
        printf("%d ",pt->key);
        preorder(pt->left);
        preorder(pt->right);
    }
}
void postorder(struct node *pt)
{
    if(pt!=NULL)
    {
        postorder(pt->left);
        postorder(pt->right);
        printf("%d ",pt->key);
    }
}
void inorder(struct node *pt)
{
    if(pt!=NULL)
    {
        inorder(pt->left);
        printf("%d ",pt->key);
        inorder(pt->right);
    }
}
int level(struct node *pt)
{
    int level=1;
    if(pt==NULL)
    {
        return -1;
    }
    while(pt->p!=NULL)
    {
        pt=pt->p;
        level++;
    }
    return level;
}
int main()
{
    struct tree *pt,ptr;
    struct node *link=NULL;
    pt=&ptr;
    pt->root=NULL;
    char ch;
    int k;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='a')
        {
            scanf("%d",&k);
            insert(pt,k);
        }
        else if(ch=='d')
        {
            scanf("%d",&k);
            link=delete(pt,k);
            if(link==NULL)
            {
                printf("-1\n");
            }
        }
        else if(ch=='x')
        {
            link=findmax(pt->root);
            if(link!=NULL)
            {
                printf("%d\n",link->key);
            }
        }
        else if(ch=='m')
        {
            link=findmin(pt->root);
            if(link!=NULL)
            {
                printf("%d\n",link->key);
            }
        }
        else if(ch=='s')
        {
            scanf("%d",&k);
            link=search(pt->root,k);
            if(link==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("1\n");
            }
        }
        else if(ch=='l')
        {
            scanf("%d",&k);
            //printf("inputted\n");
            struct node *temp=search(pt->root,k);
            //printf("searched\n");
            int l=level(temp);
            printf("%d\n",l);
        }
        // else if(ch=='r')
        // {
        //     scanf("%d",&k);
        //     struct node *temp=search(pt->root,k);
        //     if(temp==NULL)
        //     {
        //         printf("-1\n");
        //     }
        //     else
        //     {
        //         link=predecessor(temp);
        //         printf("%d\n",link->key);
        //     }
        // }
        else if(ch=='r')
        {
            scanf("%d",&k);
            struct node *temp=search(pt->root,k);
            link=predecessor(temp);
            if(link==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n",link->key);
            }
        }
        else if(ch=='u')
        {
            scanf("%d",&k);
            struct node *temp=search(pt->root,k);
            link=successor(temp);
             if(link==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n",link->key);
            }
        }
        else if(ch=='i')
        {
            inorder(pt->root);
            printf("\n");
        }
         else if(ch=='p')
        {
            preorder(pt->root);
            printf("\n");
        }
         else if(ch=='t')
        {
            postorder(pt->root);
            printf("\n");
        }
        else if(ch=='e')
        {
            break;
        }
    }
}