#include<stdio.h>
#include<stdlib.h>
#define v 5
typedef struct node
{
    struct node *next;
    int vertex;
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
int dfs(node *a[v],int d[v],int u)
{
    d[u]=1;
    printf("Compromised Machine: %d\n", u);
    node *head=a[u];
    while(head!=NULL)
    {
        if(d[head->vertex]==0)
        dfs(a,d,head->vertex);
        head=head->next;
    }
    return 0;
}
int main()
{
    node *a[v]={NULL};
    int visited[v]={0};
    addedge(a,0,1);
    addedge(a,0,4);
    addedge(a,1,2);
    addedge(a,1,3);
    addedge(a,1,4);
    addedge(a,2,3);
    addedge(a,3,4);
    printgraph(a);
    dfs(a,visited,0);
    fre(a);
    return 0;
}