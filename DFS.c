//Name : Parth Patel
//Roll No : 111501019
//DFS

#include <stdio.h>
#include <stdlib.h>

struct node
{
    short member;
    struct node *next;
};

typedef struct node node;

void printComponents(short component[], short nComponent, short nPoints);
void dfs(short startPoint, node *edjList[], short visit[], short component[], short nComponent);
void push(node *adjList[] , int location,short add);
void clrList(node *edjList[], int nPoints);
short isComplete(short visit[], int nPoints);

int main(void)
{   int nPoints;
    int nEdges;

    printf("Enter the numbert of pointes : ");
    scanf("%d",&nPoints);

    printf("Enter the number of edges : ");
    scanf("%d",&nEdges);

    short* visit = (short*) calloc(nPoints, sizeof(short));
    node** adjList = (node**) calloc (nPoints, sizeof(node*));
    printf("Enter edges :\nExample : 1 2\n\n");
    short mem1, mem2;

    while( nEdges-- )
    {   printf("Edge -> ");
        scanf("%hd%hd",&mem1, &mem2);
        push(adjList, mem1 - 1, mem2);
        push(adjList , mem2 - 1, mem1);
    }

    printf("\nGraph is ready!");

    short startPoint;

    printf("Enter the point from which you wanna start : ");
    scanf("%hd",&startPoint);

    while ( startPoint < 1 || startPoint > nPoints )
    {
        printf("Enter valid input : ");
        scanf("%hd",&startPoint);
    }

    short *component = (short*) calloc(nPoints, sizeof(short));
    short nComponent = 0 ;
    dfs(startPoint, adjList, visit, component, ++nComponent);

    while ( (startPoint = isComplete(visit, nPoints)) != -1 )
    {
        dfs(startPoint, adjList, visit, component, ++nComponent);
    }

    printf("\n\n");

    printComponents(component, nComponent, nPoints);

    //clearing all memory allocated dynamically
    clrList(adjList, nPoints);
    free(visit);
    free(component);
    free(adjList);
    return 0;
}

void printComponents(short component[], short nComponent, short nPoints)
{   int i, j;

    for (i =1 ; i <= nComponent ; i++)
    {
        printf("Component %d members : ",i);
        for(j=0 ; j < nPoints ; j++)
        {
            if(component[j] == i)
            {
                printf("%d ",j+1);
            }
        }
        printf("\n");
    }
}

void dfs(short startPoint, node *edjList[], short visit[], short component[], short nComponent)
{
    visit[startPoint-1] = 1;
    component[startPoint-1] = nComponent;
    printf("%hd ",startPoint);

    node *tmpPtr = NULL;
    tmpPtr = edjList[startPoint-1];

    while( tmpPtr != NULL )
    {
        if( visit[(tmpPtr->member)-1] == 0)
        {
            dfs(tmpPtr->member, edjList, visit, component, nComponent);
        }

        tmpPtr = tmpPtr->next;
    }

}

void push(node *adjList[] , int location,short add)
{
    node *tmpPtr = (node*) malloc(sizeof(node));
    tmpPtr->member = add;
    tmpPtr->next = NULL;

    if( adjList[location] == NULL )
    {
        adjList[location] = tmpPtr;
    }

    else
    {
        tmpPtr->next = adjList[location];
        adjList[location] = tmpPtr;
    }
}

void clrList(node * edjList[], int nPoints)
{
    for (int i=0 ; i < nPoints ; i++ )
    {
        if(edjList[i] == NULL)
            continue;
        else
        {
            do
            {
                node *tmpPtr = edjList[i]->next;
                free(edjList[i]);
                edjList[i] = tmpPtr;
            } while( edjList[i] != NULL );
        }
    }
}

short isComplete(short visit[], int nPoints)
{
    int i=0;
    while( i < nPoints )
    {
        if(visit[i] == 0)
            return (i+1);
        i++;
    }

    return -1;
}
