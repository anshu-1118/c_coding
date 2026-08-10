//Finding degree of vertex 0//
#include <stdio.h>
#define V 6

int get_degree(int m[V][V], int t) 
{
    int c = 0;
    
    for (int j = 0; j < V; j++) 
{
        if(m[t][j]==1)
	c++;
               
    }
    
    return c;
}
void add_edge(int m[V][V],int u ,int v)
{
	m[u][v]=1;
	m[v][u]=1;
}

int main() {
    int matrix[V][V] = {0};

    add_edge(matrix, 0, 4);
    add_edge(matrix, 1, 5);
    add_edge(matrix, 1, 3);
    add_edge(matrix, 2, 3);
    add_edge(matrix, 2, 5);
    add_edge(matrix, 3, 5);

    int edges_for_one = get_degree(matrix, 1);
    printf("Vertex 1 has %d connections.\n", edges_for_one);

    return 0;
}