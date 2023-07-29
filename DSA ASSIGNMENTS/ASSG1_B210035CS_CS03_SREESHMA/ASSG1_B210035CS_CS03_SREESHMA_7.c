#include <stdio.h>
#include<stdlib.h>
#include <string.h>
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
int find_index(char exp[],int b,int e)
{
    int c1=0,c2=0;
    while(b<e)
    {
        if(exp[b]=='(')
        {
            c1++;
        }
        else if(exp[b]==')')
        {
            c2++;
        }
        if(c1==c2)
        {
            return b;
        }
        b++;
    }
    return -1;
}
struct node *search(struct node *pt,int k)
{
    if(pt==NULL||pt->key==k)
    {
        return pt;
    }
    if(pt->key>k)
    {
        return search(pt->left,k);
    }
    return search(pt->right,k);
}
struct node *create_node(int k)
{
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->key=k;
    temp->p=NULL;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct node *build_tree(char exp[],int b,int e,struct tree *pt)
{
    if(b>e||b==e-2)
    {
        return NULL;
    }
    int num=0,i,j=0;
    char str[10];
    for(i=b+2;i<e && exp[i]!=' ';i++)
    {
        str[j++]=exp[i];
    }
    while(j<10)
    {
        str[j++]='\0';
    }
    //printf("%s ",str);
    num=atoi(str);
    //printf("%d\n",num);
    struct node *link=create_node(num);
    int t=find_index(exp,i+1,e);
    //printf("%d\n",t);
    if(t!=-1)
    {
        link->left=build_tree(exp,i+1,t,pt);
        if(link->left!=NULL)
        {
            link->left->p=link;
        }
        link->right=build_tree(exp,t+2,e-2,pt);
         if(link->right!=NULL)
        {
            link->right->p=link;
        }
    }
    return link;
}
void ancestors(struct node *x)
{
    if(x!=NULL)
    {
        while(x->p!=NULL)
        {
            x=x->p;
            printf("%d ",x->key);
        }
    }
}

int main()
{
    char e[1000];
    int k;
    scanf("%[^\n]s",e);
    int len=strlen(e);
    scanf("%d",&k);
    //printf("%d\n",len);
    for(int i=len;i<1000;i++)
    {
        e[i]='\0';
    }
    struct tree *pt,ptr;
    pt=&ptr;
    pt->root=NULL;
    pt->root=build_tree(e,0,len-1,pt);
    //printf("%d %d\n",pt->root->key,pt->root->p->key);
    //pt->root->p=NULL;
    struct node *x=search(pt->root,k);
    //printf("%d",x->key);
    ancestors(x);
    if(x==NULL||x->p==NULL)
    {
        printf("-1\n");
    }
}