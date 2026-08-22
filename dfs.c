#include<stdio.h>
#define V 6
void addedge(int m[V][V],int u,int v)
{
m[u][v]=1;
m[v][u]=1;
}
void dfs(int m[V][V],int v[V],int u)
{
v[u]=1;
for(int i=0;i<V;i++)
{
if(m[u][i]==1 && v[i]!=1)
dfs(m,v,i);
}
}
int checkseg(int m[V][V],int v[V])
{int c=0;
for(int i=0;i<V;i++)
{
if(v[i]==0)
{
c++;
dfs(m,v,i);
}
}
return c;
}
int main()
{
int m[V][V]={0};
int v[V]={0};

addedge(m,0,1);
addedge(m,0,2);
addedge(m,1,2);
addedge(m,3,4);
int c=checkseg(m,v);
printf("number of segment:%d",c);
}