

#include <stdio.h>
#define EMPTY -1 
int checkbst(int a[], int n, int i, int *pi) 
{
    if (i>= n || a[i] == EMPTY) 
    {
        return 1;
    }
    if (!checkbst(a, n, 2 * i + 1, pi)) 
    {
        return 0;
    }
    if (*pi != -1 && a[i] <= a[*pi])
    {
        return 0; 
    }
    *pi = i;
    return checkbst(a, n, 2 * i + 2, pi);
}

int isBST(int a[], int n) 
{
    int pi = -1; 
    return checkbst(a, n, 0, &pi);
}

int main() 
{
    int n,i;
    printf("Enter number of elements in binary tree\n");
    scanf("%d",&n);
    int a[n];
    printf("Enter binary tree elements\n");
    for(i=0;i<n;i++)
    {
    scanf("%d",&a[i]);
    }
    if (isBST(a, n)) 
    {
        printf("Tree 1 is a valid Binary Search Tree.\n");
    } 
    else 
    {
        printf("Tree 1 is NOT a Binary Search Tree.\n");
    }   
    return 0;
}
