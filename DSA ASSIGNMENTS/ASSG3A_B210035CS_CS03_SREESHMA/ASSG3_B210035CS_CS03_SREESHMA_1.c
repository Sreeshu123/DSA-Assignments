#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int colour;
};
struct tree
{
    struct node *root;
};
struct node *left_rotate(struct node *x)
{
    struct node *y,*z;
    y=x->right;
    z=y->left;
    y->left=x;
    x->right=z;
    return y;
}
struct node *right_rotate(struct node *x)
{
    struct node *y,*z;
    y=x->left;
    z=y->right;
    y->right=x;
    x->left=z;
    return y;
}
struct node*create_node(int k)
{
    struct node *t=(struct node*)malloc(sizeof(struct node));
    t->key=k;
    t->left=t->right=NULL;
    t->colour=1;
}
struct node *rb_insert(struct node *r,struct node *x)
{
    if(r==NULL)
    {
        return x;
    }
    else if(x->key<r->key)
    {
        r->left=rb_insert(r->left,x);
        if(r->left->colour==1)
        {
            if((r->left->left && r->left->left->colour==1)||(r->left->right && r->left->right->colour==1))
            {
                if(r->right && r->right->colour==1)
                {
                    r->colour=1;
                    r->left->colour=r->right->colour=0;
                    return r;
                }
                else
                {
                    if(r->left->right && r->left->right->colour==1)
                    {
                        r->left=left_rotate(r->left);
                    }
                    r=right_rotate(r);
                    r->right->colour=1;
                    r->colour=0;
                    return r;
                }
            }
        }
        else
        {
            return r;
        }
    }
    else if(x->key>r->key)
    {
        r->right=rb_insert(r->right,x);
        if(r->right->colour==1)
        {
            if((r->right->left && r->right->left->colour==1)||(r->right->right && r->right->right->colour==1))
            {
                if(r->left && r->left->colour==1)
                {
                    r->colour=1;
                    r->left->colour=r->right->colour=0;
                    return r;
                }
                else
                {
                    if(r->right->left && r->right->left->colour==1)
                    {
                        r->right=right_rotate(r->right);
                    }
                    r=left_rotate(r);
                    r->left->colour=1;
                    r->colour=0;
                }
            }
        }
        else
        {
            return r;
        }
    }
    return r;
}
void print(struct node *r)
{
    printf("( ");
    if(r)
    {
        printf("%d ",r->key);
        if(r->colour==0)
        {
            printf("B ");
        }
        else
        {
            printf("R ");
        }
        print(r->left);
        print(r->right);
    }
    printf(") ");
}
int main()
{
    struct tree *pt,ptr;
    pt=&ptr;
    pt->root=NULL;
    char ch[10];
    while(1)
    {
        scanf("%s",ch);
        if(ch[0]=='t')
        {
            break;
        }
        else
        {
            int k=atoi(ch);
            //printf("%d\n",k);
            struct node *x=create_node(k);
            pt->root=rb_insert(pt->root,x);
            pt->root->colour=0;
            print(pt->root);
            printf("\n");
        }
    }
    return 0;
}

