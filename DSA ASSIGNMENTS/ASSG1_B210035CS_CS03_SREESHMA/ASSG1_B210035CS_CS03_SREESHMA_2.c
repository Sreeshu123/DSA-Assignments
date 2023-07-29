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
void count(struct node *ptr,struct tree *pt)
{
    if(ptr==NULL)
    {
        //printf("yes1 ");
        return;
    }
    if(ptr->p!=NULL && ptr->p->p!=NULL)
    {
        //printf("yes2 ");
        struct node *l,*r,*ptr1;
        ptr1=ptr->p->p;
        l=ptr1->left;
        r=ptr1->right;
        if(l->left==NULL && l->right==NULL||r->left==NULL && r->right==NULL)
        {
            //printf("%d\n",ptr->key);
            pt->c=pt->c+1;
        }
    }
    //printf("yes3 ");
    count(ptr->right,pt);
    count(ptr->left,pt);
    
}
// void preorder(struct node *pt)
// {
//     if(pt!=NULL)
//     {
//         printf("%d ",pt->key);
//         preorder(pt->left);
//         preorder(pt->right);
//     }
// }
int main()
{
    char e[1000];
    scanf("%[^\n]s",e);
    int len=strlen(e);
    //printf("%d\n",len);
    for(int i=len;i<1000;i++)
    {
        e[i]='\0';
    }
    struct tree *pt,ptr;
    pt=&ptr;
    pt->c=0;
    pt->root=NULL;
    pt->root=build_tree(e,0,len-1,pt);
    //pt->root->p=NULL;
    //preorder(pt->root);
    count(pt->root,pt);
    //printf("%d %d\n",pt->root->p,pt->root);
    printf("%d",pt->c);
}