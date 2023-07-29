#include <stdio.h>
void print_list(int a[][100],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",i);
        for(int j=0;j<n;j++)
        {
            if(a[i][j]==1)
            {
                printf("%d ",j);
            }
        }
        printf("\n");
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int adj[n][100];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&adj[i][j]);
        }
    }
    print_list(adj,n);
    return 0;
}