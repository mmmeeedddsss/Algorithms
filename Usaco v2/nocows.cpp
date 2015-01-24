/*
ID: mmmeeed1
LANG: C++
TASK: nocows
*/
#include<stdio.h>
FILE* fin=fopen("nocows.in","r");
FILE* fout=fopen("nocows.out","w");
int main()
{
    int n,k,tree[100][200]={0},com[100][200]={0},c;
    fscanf(fin,"%d%d",&n,&k);
    tree[1][1]=1;
    for(int i=2;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            com[i-1][j]+=tree[i-1][j]+com[i-2][j];
            com[i-1][j]%=9901;
        }
        for(int j=1;j<=n;j++)
        {
            for(int k=1;k<=j-k-1;k+=2)
            {
                c=2;
                if(k==j-k-1)
                {
                    c=1;
                }
                tree[i][j]+=c*(tree[i-1][k]*tree[i-1][j-k-1]+tree[i-1][k]*com[i-2][j-k-1]+com[i-2][k]*tree[i-1][j-k-1]);
                tree[i][j]%=9901;
            }
        }
    }
    fprintf(fout,"%d\n",tree[k][n]);
    return 0;
}
