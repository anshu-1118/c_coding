//variable-length array with an initializer list like {0}.Because you defined v as an integer variable (int v = 6;) and then used it to set the array size (int matrix[v][v] ={0};), the compiler treats matrix as a VLA and rejects the {0} initialization.//

#include<stdio.h>
#include<stdlib.h>
#define ve 6
void add_edge(int m[ve][ve],int u ,int v)
{
	m[u][v]=1;
	m[v][u]=1;
}
void print_matrix(int m[ve][ve],int v)
{
	printf("Adjacency Matrix:\n");
	for (int i = 0; i < v; i++) 
	{
       	 for (int j = 0; j < v; j++)
		{
           	 printf("%d ", m[i][j]);
        	}
         printf("\n");
    }
	
}
int main()
{
	int v=6;
	int matrix[ve][ve]={0};

	add_edge(matrix,0,4);
	add_edge(matrix,1,5);
	add_edge(matrix,1,3);
	add_edge(matrix,2,3);
	add_edge(matrix,2,5);
	add_edge(matrix,3,5);

	print_matrix(matrix,v);
	return 0;
}