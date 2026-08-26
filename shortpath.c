#include<stdio.h>
#define V 6
void addedge(int m[V][V],int u,int v)
{
m[u][v]=1;
m[v][u]=1;
}
void bfs(int m[V][V],int u,int t)
{
int v[V]={0};
int queue[V]={0};
int f=0,r=0;
int p[V];
int fo=0;

for(int a=0;a<V;a++)
p[a]=-1;

v[u]=1;
queue[r]=u;
r++;

while(r>f)
{
int x=queue[f++];
if(x==t)
{
fo=1;
break;
}

for(int i=0;i<V;i++)
{
if(m[x][i]==1 && v[i]!=1)
{
queue[r]=i;
r++;
v[i]=1;
p[i]=x;
}
}
}


if(fo==1)
{
int pa[V],l=0;
int z=t;
while(z!=-1)
{
pa[l++]=z;
z=p[z];
}




for(int i=0;i<l;i++)
{
printf(" %d ",pa[i]);
}
}
else {
        printf("No path exists between %d and %d.\n", u, t);
}}

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
bfs(m,0,4);
return 0;
}