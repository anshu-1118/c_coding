#include<stdio.h>
#include<stdlib.h>
#define v 5
typedef struct node
{
    struct node *next;
    int vertex;
    int color;
}node;
void addedge(node *a[v],int u,int z)
{
    node *c=(node*)malloc(sizeof(node));
    c->vertex=z;
    c->next=a[u];
    a[u]=c;

    node *d=( node*)malloc(sizeof(node));
    d->vertex=u;
    d->next=a[z];
    a[z]=d;
    
}
void printgraph(node *a[v])
{
    for(int i=0;i<v;i++)
    {
        node *head=a[i];
        while(head!=NULL)
        {
            printf("%d -> %d\n",i,head->vertex);
            head=head->next;
        }
    }
} 
void fre(node *a[v])
{
    node *temp=NULL;
    for(int i=0;i<v;i++)
    {
        node *head=a[i];
        while(head!=NULL)
        {
            temp=head->next;
            free(head);
            head=temp;
        }
    }
}
int bipartite(node *a[v],int c[v],int u,int cu)
{
    c[u]=cu;
    int z=1;
    printf("Compromised Machine: %d\n", u);
    node *head=a[u];
    while(head!=NULL)
    {
        if(c[head->vertex]==cu)
        {
        return 0;
        }
        if(c[head->vertex]==0 )
        {
        int nc = (cu == 1) ? 2 : 1;
        if(bipartite(a,c,head->vertex,nc)==0)
         return 0;
        }
        head=head->next;
    }
    return 1;
}
int main()
{
    node *a[v]={NULL};
    int color[v]={0};
    int cu=1;
    addedge(a,0,1);
    addedge(a,0,2);
    addedge(a,2,3);
    addedge(a,1,3);
    addedge(a,2,4);
    addedge(a,3,2);
    addedge(a,4,3);
    printgraph(a);
    int b=bipartite(a,color,0,cu);
    if(b==1)
    printf("True");
    else
    printf("False");
    fre(a);
    return 0;
}