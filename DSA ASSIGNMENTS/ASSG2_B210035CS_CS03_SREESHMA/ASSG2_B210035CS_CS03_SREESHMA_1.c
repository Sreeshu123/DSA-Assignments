#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node 
{
    char name[100];
    char roll[10];
    int age;
    struct node* next;
    struct node *prev;
};
int hash_value(char name[],int age)
{
    //printf("%s\n",name);
    int sum=age,j=0;
    while(name[j]!='\0')
    {
        sum+=name[j++];
    }
    //printf("%d\n",sum);
    return sum%4;
}
void insert(struct node* T[],struct node* x)
{
    int hash=hash_value(x->name,x->age);
    //printf("%d\n",hash);
    x->next=T[hash];
    if(x->next!=NULL)
    {
        x->next->prev=x;
    }
    T[hash]=x;
}
void count(struct node *x)
{
    int c=0;
    struct node *y=NULL;
    while(x!=NULL)
    {
        y=x;
        x=x->next;
        //printf("moved\n");
        c++;
    }
    printf("%d ",c);
    while(y!=NULL)
    {
        printf("%s ",y->name);
        y=y->prev;
    }
    return;
}
int same_branch(struct node* x,char branch[])
{
    int c=0;
    for(int i=0;branch[i]!='\0';i++)
    {
        if(branch[i]>=97 && branch[i]<=122)
        {
            branch[i]-=32;
        }
    }
    //printf("%s\n",branch);
    char br[10];
    for(int j=0;j<10;j++)
    {
        br[j]='\0';
    }
    //printf("%s\n",x->roll);
    if(x!=NULL)
    {
        while(x->next!=NULL)
        {
            x=x->next;
        }
    }
    while(x!=NULL)
    {
        br[0]=x->roll[7];
        br[1]=x->roll[8];
        //printf("br=%s\n",br);
        int cmp=strcmp(br,branch);
        if(cmp==0)
        {
            c++;
            printf("%s ",x->name);
        }
        x=x->prev;
    }
    return c;
}
int main()
{
    struct node* T[4];
    for(int i=0;i<4;i++)
    {
        T[i]=NULL;
    }
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        struct node *pt=(struct node*)malloc(sizeof(struct node));
        for(int j=0;j<100;j++)
        {
            pt->name[j]='\0';
        }
        scanf("%s %s %d", pt->name, pt->roll, &pt->age);
        pt->next=NULL;
        pt->prev=NULL;
        //printf("scanned\n");
        insert(T,pt);
        //printf("inserted\n");
    }
    char ch;
    int k;
    while(1)
    {
        getchar();
        ch=getchar();
        //printf("%c",ch);
        if(ch=='c')
        {
            //printf("scan\n");
            scanf("%d",&k);
            count(T[k]);
            printf("\n");
        }
        else if(ch=='e')
        {
            break;
        }
        else
        {
            //printf("%c",ch);
            int t=ch-48;
            //printf("%d\n",t);
            char str[10];
            int j=10;
            while(j--)
            {
                str[j]='\0';
            }
            scanf(" %s",str);
            //printf("%s\n",str);
            if(same_branch(T[t],str)==0)
            {
                printf("-1");
            }
            printf("\n");
        }
    }
    return 0;
}