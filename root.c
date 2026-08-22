#include<stdio.h>

#define v 4
void add_edge(int m[v][v],int u,int x)
{
 m[u][x]=1;
}
int check_root(int m[v][v])
{
	int out,in;
	for(int i=0;i<v;i++)
	{
		in=0;out=0;
		for(int j=0;j<v;j++)
		{
			if(m[j][i]==1)
			in++;
		}
		if(in==v-1)
		{
			for(int j=0;j<v;j++)
			{
			if(m[i][j]==1)
			out++;
			}
			if(out==0)
			return i;
		}
	}
return -1;
}
	
int main()
{
int m[v][v]={0};

add_edge(m,0,2);
add_edge(m,1,2);
add_edge(m,3,2);
add_edge(m,1,0);

int r=check_root(m);
if(r!=-1)
printf("%d",r);
else
printf("no root");
return 0;

}
