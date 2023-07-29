#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char first[100];
    char last[100];
    char gender;
    char dob[15];
    char dept[5];
    float cgpa;
    struct node *p;
    struct node *left;
    struct node *right;
};
void inorder(struct node *x)
{
    if(x!=NULL)
    {
        inorder(x->left);
        printf("%s %s\n",x->first,x->last);
        inorder(x->right);
    }
}
struct node *search(struct node * root,char first[],char last[],int *count,char path[])
{
    if(root==NULL)
    {
        return NULL;
    }
    if(strcmp(root->first,first)==0)
    {
        while(root!=NULL && strcmp(root->first,first)==0)
        {
            //printf("%s %s %s %s\n",root->first,root->last,first,last);
            if(strcmp(root->last,last)==0)
            {
                //printf("found\n");
                return root;
            }
            else if(strcmp(root->last,last)<0)
            {
                path[(*count)++]='R';
                root=root->right;
            }
            else
            {
                //printf("left\n");
                path[(*count)++]='L';
                root=root->left;
            }
        }
        return NULL;

    }
    else if(strcmp(root->first,first)<0)
    {
        path[(*count)++]='R';
        search(root->right,first,last,count,path);
    }
    else
    {
        path[(*count)++]='L';
        search(root->left,first,last,count,path);
    }
}
struct node *findmin(struct node *x)
{
    while(x->left!=NULL)
    {
        x=x->left;
    }
    return x;
}
void transplant(struct node *T[],struct node *u,struct node *v,int hash)
{
    if(u->p==NULL)
    {
        T[hash]=v;
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
void delete(struct node* T[],struct node *x,int hash)
{
    if(x!=NULL)
    {
        if(x->left==NULL)
        {
            transplant(T,x,x->right,hash);
        }
        else if(x->right==NULL)
        {
            transplant(T,x,x->left,hash);
        }
        else
        {
            struct node *y=NULL;
            y=findmin(x->right);
            if(y->p!=x)
            {
                transplant(T,y,y->right,hash);
                y->right=x->right;
                y->right->p=y;
            }
            transplant(T,x,y,hash);
            y->left=x->left;
            y->left->p=y;
        }
    }
    return ;
}
int update(struct node *root,char first[],char last[],int cgpa,int *check)
{
    if(root!=NULL)
    {
        if((strcmp(root->first,first)==0))
        {
            int c1=0;
            while(root!=NULL && strcmp(root->first,first)==0)
            {
                if(strcmp(root->last,last)==0)
                {
                    root->cgpa=cgpa;
                    *check=1;
                    return c1;
                }
                else if(strcmp(root->last,last)<0)
                {
                    root=root->right;
                }
                else
                {
                    root=root->left;
                }
                c1++;
            }
            return c1;
        }
        else if(strcmp(root->first,first)<0)
        {
            return(update(root->right,first,last,cgpa,check)+1);
        }
        else
        {
            return(update(root->left,first,last,cgpa,check)+1);
        }
    }
    return -1;
}
int bst_insert(struct node *T[],struct node *t)
{
    int hash=t->first[0]-65;
    //printf("hash=%d\n",hash);
    int c=0;
    struct node *x=T[hash],*y=NULL;
    while(x!=NULL)
    {
        y=x;
        if(strcmp(x->first,t->first)<0)
        {
            x=x->right;
            c++;
        }
        else if(strcmp(x->first,t->first)>0)
        {
            x=x->left;
            c++;
        }
        else
        {
            //printf("equal\n");
            while(x!=NULL && strcmp(x->first,t->first)==0)
            {
                y=x;
                if(strcmp(x->last,t->last)<0)
                {
                    x=x->right;
                    c++;
                }
                else if(strcmp(x->last,t->last)>0)
                {
                    //printf("check2\n");
                    x=x->left;
                    c++;
                }
            }
        }
    }
    t->p=y;
    if(y==NULL)
    {
        T[hash]=t;
    }
    else if(strcmp(y->first,t->first)<0)
    {
        y->right=t;
    }
    else if(strcmp(y->first,t->first)>0)
    {
        y->left=t;
    }
    else
    {
        if(strcmp(y->last,t->last)<0)
        {
           y->right=t; 
        }
        else if(strcmp(y->last,t->last)>0)
        {
            y->left=t;
        }
    }
    return c;
}
void print(struct node *x)
{
    if(x!=NULL)
    {
        print(x->left);
        printf("%s %s ",x->first,x->last);
        print(x->right);
    }
}
int main()
{
    struct node *T[26];
    for(int i=0;i<26;i++)
    {
        T[i]=NULL;
    }
    char ch;
    char first[100],last[100];
    float k;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='i')
        {
            struct node *pt=(struct node*)malloc(sizeof(struct node));
            scanf("%s %s %c %s %s %f",pt->first,pt->last,&pt->gender,pt->dob,pt->dept,&pt->cgpa);
            //printf("%s %s %c %s %s %f\n",pt->first,pt->last,pt->gender,pt->dob,pt->dept,pt->cgpa);
            pt->p=pt->left=pt->right=NULL;
            printf("%d\n",bst_insert(T,pt));
        }
        else if(ch=='u')
        {
            for(int j=0;j<100;j++)
            {
                first[j]=last[j]='\0';
            }
            scanf("%s %s %f",first,last,&k);
            int hash=first[0]-65;
            int check=0;
            int u=update(T[hash],first,last,k,&check);

            if(check==1)
            {
                printf("%d\n",u);
            }
            if(check==0)
            {
                printf("-1\n");
            }
            //inorder(T[hash]);
        }
        else if(ch=='l')
        {
            char path[100];
            for(int i=0;i<100;i++)
            {
                first[i]=last[i]=path[i]='\0';
            }
            scanf("%s %s",first,last);
            //printf("%s %s\n",first,last);
            int count=0;
            int hash=first[0]-65;
            //print(T[hash]);
            // printf("\n");
            if(hash>25 || search(T[hash],first,last,&count,path)==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d-%s\n",hash,path);
            }
            //inorder(T[hash]);
        }
        else if(ch=='d')
        {
            char path[100];
            for(int i=0;i<100;i++)
            {
                first[i]=last[i]=path[i]='\0';
            }
            scanf("%s %s",first,last);
            //printf("%s %s\n",first,last);
            int count=0;
            int hash=first[0]-65;
            struct node *temp=search(T[hash],first,last,&count,path);
            if(temp==NULL)
            {
                printf("-1\n");
            }
            else
            {
                delete(T,temp,hash);
                printf("%d\n",count);
            }
            //printf("%s\n",path);
            // print(T[hash]);
            // printf("\n");
            //inorder(T[hash]);
        }
        else if(ch=='t')
        {
            int hash=17;
            inorder(T[hash]);
        }
        else if(ch=='e')
        {
            break;
        }
    }
    return 0;
}