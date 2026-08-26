#include<stdio.h>
#define V 7
void addedge(int m[V][V],int u,int v)
{
m[u][v]=1;
m[v][u]=1;
}

int dfs(int m[V][V],int u,int id[V],int c)
{
id[u]=c;
for(int j=0;j<V;j++)
{
if(m[u][j]==1 && id[j]==0)
dfs(m,j,id,c);
}
return 0;
}

int map_network(int m[V][V], int id[V])
{
int c=1;
for(int i=0;i<V;i++)
{
if(id[i]==0)
{
dfs(m,i,id,c);
c++;
}
}
return c;
}
int can_communicate(int id[V],int u,int v)
{
 if(id[u]==id[v])
	return 1;
else
return 0;
}

int main()
{
int m[V][V]={0};
int id[V]={0};
addedge(m,0,1);
addedge(m,0,2);
addedge(m,1,2);
addedge(m,3,4);
addedge(m,3,5);
int c=map_network(m,id);
printf("No. of isolated segments:%d\n",c);
printf("Can Machine 0 talk to 2? %s\n", can_communicate(id, 0, 2) ? "Yes" : "No");
printf("Can Machine 2 talk to 4? %s\n", can_communicate(id, 2, 4) ? "Yes" : "No");
printf("Can Machine 6 talk to 0? %s\n", can_communicate(id, 6, 0) ? "Yes" : "No");return 0;

}
