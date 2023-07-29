#include <stdio.h>
#include<stdlib.h>
#include <string.h>
struct node
{
    int key;
    struct node *left;
    struct node *right;
};
struct tree
{
    struct node *root;
    struct node *val;
    int x;
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
    if(num==pt->x)
    {
        pt->val=link;
    }
    int t=find_index(exp,i+1,e);
    //printf("%d\n",t);
    if(t!=-1)
    {
        link->left=build_tree(exp,i+1,t,pt);
        link->right=build_tree(exp,t+2,e-2,pt);
    }
    return link;
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
void print(struct node *pt,int c,int *check)
{
    if(pt==NULL)
    {
        return;
    }
    print(pt->left,c-1,check);
    if(pt!=NULL && c==0)
    {
        printf("%d ",pt->key);
        (*check)++;
        return;
    }
    print(pt->right,c-1,check);
}
int main()
{
    char e[1000];
    int x,k;
    scanf("%[^\n]s",e);
    int len=strlen(e);
    //printf("%d\n",len);
    for(int i=len;i<1000;i++)
    {
        e[i]='\0';
    }
    scanf("%d",&x);
    scanf("%d",&k);
    struct tree *pt,ptr;
    pt=&ptr;
    pt->root=NULL;
    pt->val=NULL;
    pt->x=x;
    pt->root=build_tree(e,0,len-1,pt);
    //preorder(pt->root);
    //printf("\n%d\n",pt->val->key);
    int check=0;
    print(pt->val,k,&check);
    if(check==0||pt->val==NULL)
    {
        printf("-1\n");
    }
}