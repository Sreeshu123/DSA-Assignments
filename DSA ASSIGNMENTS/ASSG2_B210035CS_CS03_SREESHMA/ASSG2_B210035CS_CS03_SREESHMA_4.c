#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
};
struct node *create_node(int k)
{
    struct node *x=(struct node*)malloc(sizeof(struct node));
    x->key=k;
    return x;
}
int prime(int n)
{
	int prime=-1;
	for(int i=n-1;i>=0;i--)
	{
		int check=0;
		for(int j=2;j<i;j++)
		{
			if(i%j==0)
			{
				check=1;
				break;
			}
		}
		if(check==0)
		{
			prime=i;
			break;
		}
	}
	return prime;
}
int compute_hash(int key,int n,int r,int i)
{
	int i1=key%n;
	int i2=r-(key%r);
	int index=i1+i*i2;
	index=index%n;
	return index;
}
int linear(struct node *a[],int k,int n,int *co)
{
    //printf("%d\n",n);
    int i=1;
    int hash=k%n;
    int temp=hash;
    //printf("first hash=%d key=%d\n",hash,k);
    if(a[temp]==NULL)
    {
        a[temp]=create_node(k);
        return temp;
    }
    while(a[temp]!=NULL && i<=n)
    {
        (*co)++;
        temp=(hash+i)%n;
        i++;
        //printf("co hash=%d\n",hash);
        if(a[temp]==NULL)
        {
            a[temp]=create_node(k);
            return temp;
        }
    }
    return -1;
}
int quad(struct node *a[],int k,int n,int *co)
{
    //printf("%d\n",n);
    int i=1;
    int hash=k%n;
    int temp=hash;
    //printf("first hash=%d key=%d\n",hash,k);
    if(a[temp]==NULL)
    {
        a[temp]=create_node(k);
        return temp;
    }
    while(a[temp]!=NULL && i<=n)
    {
        (*co)++;
        temp=(hash+i*i)%n;
        //printf("\ni=%d hash=%d\n",i,hash);
        i++;
        //printf("co hash=%d\n",hash);
        if(a[temp]==NULL)
        {
            a[temp]=create_node(k);
            return temp;
        }
    }
    return -1;
}
int double_hashing(struct node *a[],int k,int n,int *co,int r)
{
	int i=1;
	int hash=k%n;
	int temp=hash;
	if(a[temp]==NULL)
	{
		a[temp]=create_node(k);
		return temp;
	}
	while(a[temp]!=NULL && i<=n)
	{
		(*co)++;
		temp=compute_hash(k,n,r,i);
        i++;
		if(a[temp]==NULL)
		{
		    a[temp]=create_node(k);
		    return temp;
		}
	}
	return -1;
}
int main()
{
    int n;
    scanf("%d",&n);
    struct node *a[n];
    for(int i=0;i<n;i++)
    {
        a[i]=NULL;
    }
    int elems[1000],k,len=0;
    char ch;
    while(1)
    {
        scanf("%d%c",&k,&ch);
        elems[len++]=k;
        if(ch=='\n')
        {
            break;
        }
    }
    int co=0;
    for(int i=0;i<len;i++)
    {
        int index=linear(a,elems[i],n,&co);
        if(index==-1)
        {
            printf("E ");
        }
        else
        {
            printf("%d ",index);
        }
    }
    printf("\n");
    printf("%d\n",co);
    co=0;
    for(int i=0;i<n;i++)
    {
        a[i]=NULL;
    }
    for(int i=0;i<len;i++)
    {
        int index=quad(a,elems[i],n,&co);
        if(index==-1)
        {
            printf("E ");
        }
        else
        {
            printf("%d ",index);
        }
    }
    printf("\n");
    printf("%d\n",co);
    int r=prime(n);
    co=0;
    for(int i=0;i<n;i++)
    {
        a[i]=NULL;
    }
    for(int i=0;i<len;i++)
    {
    	//printf("looping\n");
        int index=double_hashing(a,elems[i],n,&co,r);
        //printf("done\n");
        if(index==-1)
        {
            printf("E ");
        }
        else
        {
            printf("%d ",index);
        }
    }
    printf("\n");
    printf("%d\n",co);
    
}
