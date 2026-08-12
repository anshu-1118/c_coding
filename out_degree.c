#include <stdio.h>
#define V 4

int get_out(int m[V][V], int t) 
{
    int c = 0;
    for (int j = 0; j < V; j++) 
    {
	if(m[t][j]==1)
	c++;

    }
    return c;
}

int get_in(int m[V][V], int t) 
{
    int c = 0;
    for(int i=0;i<V;i++)
	{
		if(m[i][t]==1)
		c++;
	}
    return c;
}

void add(int m[V][V], int u, int v) 
{
    m[u][v] = 1;
}

int main() 
{
    int m[V][V] = {0};

    add(m, 0, 1);
    add(m, 0, 2);
    add(m, 1, 2);
    add(m, 3, 2);

    int in_deg = get_in(m, 2);
    int out_deg = get_out(m, 2);
    
    printf("Vertex 2 In-Degree: %d\n", in_deg);
    printf("Vertex 2 Out-Degree: %d\n", out_deg);

    return 0;
}