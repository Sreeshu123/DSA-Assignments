#include <stdio.h>
#include<stdlib.h>
#include <string.h>
struct path
{
    char p1[100];
    char p2[100];
    int len;
    int sum;
};
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
};
int max_index(struct path a[],int len)
{
    int max=0;
    for(int i=1;i<len;i++)
    {
        if (a[max].sum<a[i].sum)
        {
            max=i;
        }
        else if(a[max].sum==a[i].sum && a[i].len<a[max].len)
        {
            max=i;
        }
    }
    return max;
}
void reverse(struct path a[],int len)
{
    int i=0;
    while(i<len)
    {
        int t=a[i].len;
        for(int j=0;j<t;j++)
        a[i].p2[j]=a[i].p1[t-j-1];
        i++;
    }
}
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
// void print(struct path a[],int len)
// {
//     for(int i=0;i<len;i++)
//     {
//         printf("%s %d ",a[i].p1,a[i].sum);
//     }
// }
void trace_path(struct node *pt,struct path a[],int *c)
{
    int i=0,sum=0;
    struct node *y=NULL;
    while(pt->p!=NULL)
    {
        y=pt;
        sum+=y->key;
        pt=pt->p;
        if(y==pt->left)
        {
            a[*c].p1[i++]='L';
        }
        else
        {
            a[*c].p1[i++]='R';
        }
    }
    while(i<100)
    {
        a[*c].p1[i++]='\0';
    }
    sum+=pt->key;
    a[*c].sum=sum;
    a[*c].len=strlen(a[*c].p1);
}
void count_path(struct node *pt,struct path a[],int *i)
{
    if(pt!=NULL)
    {
        if(pt->left==NULL && pt->right==NULL)
        {
            trace_path(pt,a,i);
            (*i)++;
        }
        count_path(pt->left,a,i);
        count_path(pt->right,a,i);
    }
}
int main()
{
    char e[1000];
    scanf("%[^\n]s",e);
    int len=strlen(e),key;
    //printf("%d\n",len);
    for(int i=len;i<1000;i++)
    {
        e[i]='\0';
    }
    struct tree *pt,ptr;
    pt=&ptr;
    pt->root=NULL;
    pt->root=build_tree(e,0,len-1,pt);
    struct path p[100];
    int lenp=0;
    count_path(pt->root,p,&lenp);
    reverse(p,lenp);
    int max=max_index(p,lenp);
    //printf("%d %d\n",lenp,max);
    //print(p,lenp);
    if(strlen(p[max].p2)!=0)
    {
        printf("%s %d",p[max].p2,p[max].sum);
    }
    else
    {
        printf("%d",p[max].sum);
    }
}