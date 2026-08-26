#include<stdio.h>
#define V 6
void addedge(int m[V][V],int u,int v)
{
m[u][v]=1;
m[v][u]=1;
}
int bfs(int m[V][V],int u)
{
int v[V]={0};
int queue[V]={0};
int f=0,r=0;

v[u]=1;
queue[r]=u;
r++;
printf("bfs traversal:");

while(r>f)
{
int x=queue[f++];
printf("%d",x);
for(int i=0;i<V;i++)
{
if(m[x][i]==1 && v[i]!=1)
{
queue[r]=i;
r++;
v[i]=1;
}
}
printf("\n");
}
}

int main()
{
int m[V][V]={0};
    addedge(m, 0, 1);
    addedge(m, 0, 2);
    addedge(m, 1, 3);
    addedge(m, 1, 4);
    addedge(m, 2, 4);
    addedge(m, 3, 5);
    addedge(m, 4, 5);
bfs(m,0);
return 0;
}