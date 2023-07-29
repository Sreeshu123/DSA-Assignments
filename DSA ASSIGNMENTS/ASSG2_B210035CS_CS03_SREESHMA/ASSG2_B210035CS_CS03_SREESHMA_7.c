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
        return 0;
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
    if(b>1 && x->key<r->left->key)
    {
        if(x->key>r->left->key)
        {
            r->left=left_rotate(r->left);
        }
        return right_rotate(r);
    }
    if(b<-1 && x->key>r->right->key)
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
int count_nodes(struct node *x,int k)
{
	if(x==NULL)
	{
		return 0;
	}
	int c=0;
	if(x->key>k)
	{
		c=1;
	}
	return (c+count_nodes(x->left,k)+count_nodes(x->right,k));
}
void print_nodes(struct node *x,int k)
{
    if(x!=NULL)
    {
    	print_nodes(x->left,k);
    	if(x->key>k)
        {
        	printf("%d ",x->key);
        }
        print_nodes(x->right,k);
    }
}
void print(struct node *x)
{
    if(x!=NULL)
    {
        print(x->left);
        printf("%d ",x->key);
        print(x->right);
    }
}
int main()
{
	struct tree *ptr=(struct tree*)malloc(sizeof(struct tree));
	ptr->root=NULL;
	int k;
	char ch;
	while(1)
	{
		scanf("%c",&ch);
		if(ch=='i')
		{
			scanf("%d",&k);
			struct node *link=create_node(k);
			avl_tree_insert(ptr,link);
			//printf("inserted\n");
		}
		else if(ch=='c')
		{
			scanf("%d",&k);
			printf("%d" ,count_nodes(ptr->root,k));
			printf("\n");
			print_nodes(ptr->root,k);
			printf("\n");
		}
        else if(ch=='p')
        {
            print(ptr->root);
            printf("\n");
        }
		else if(ch=='e')
		{
			break;
		}
	}
	return 0;
 }
