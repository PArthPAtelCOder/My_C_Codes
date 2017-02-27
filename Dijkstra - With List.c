//Name: Patel Parth Pragneshkumar
//Roll No: 111501019

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define L_CHILD(n) (2*(n) + 1)    //it's not a 2n because it's a index starting from 0 not 1
#define R_CHILD(n) (2*(n) + 2)    //same here
#define PARENT(n) (((n)/2) - 1) //parent index of node[n]

typedef struct stackNode
{
    int index;
    int edgeWeight;
    struct stackNode* next;
} StackNode;

//Structure used for Heap Data Structure
typedef struct
{
    int index;
    int distance;
    int predecessor;
} HeapNode;

//structure in which final minDistance and predecessor in shortest path will be stored
typedef struct
{
    int distance;
    int predecessor;
    int setMemberFlag; //0 means not a member else 1
} Point;

//functions for stack
int push(StackNode**, int, int);
void deleteStack(StackNode**);

//functions for graph
StackNode** createGraph(int);
Point* dijkstra(StackNode**, int, int);
HeapNode* createHeap(int, int);

//functions for heap
HeapNode extractMin(HeapNode*, int*);
void decreaseKey(int, int, int, HeapNode*, int);
void minHeapify(HeapNode*, int, int);

int main(void)
{
    int nVertices;

    printf("Enter the number of vertices : ");
    scanf("%d", &nVertices);

    StackNode** graph = createGraph(nVertices);
    if (graph == NULL)
        return 1;

    int source;
    printf("Enter the source vertex : ");
    scanf("%d", &source);
    //minDistData contains minDistance of every vertex from source
    //and it's predecessor in minDistance Path
    Point* minDistData = dijkstra(graph, source, nVertices);
    //if encountered error while allocating memory
    if (minDistData == NULL)
        return 1;

    int i = 0;
    printf("\n\nVertex | MinDistance From Source | predecessor :-->\n\n");

    while (i < nVertices)
    {   
        if( minDistData[i].setMemberFlag == 0 )
        {
            printf("%d | Not connected to vertex %d\n", i + 1, source );
            i++;
            continue;
        }

        printf("%d | %d | %d\n", i + 1, minDistData[i].distance, minDistData[i].predecessor);
        i++;
    }

    //removing memory allocated for adjacency lists
    i = 0;
    while (i < nVertices)
        deleteStack(&graph[i++]);
    //removing memory of array in which result is stored
    free(minDistData);
    return 0;
}

StackNode** createGraph(int nVertices)
{
    int i = 0;

    //creating nVertices * nVertices matrix representing Graph
    StackNode** graph = (StackNode**) calloc(nVertices, sizeof (StackNode*));

    if (graph == NULL)
        return NULL;

    printf("Enter the Vertex then it's number of edges and then vertice \
        connected with it with edge weight.\n\
        START IN INCREASING ORDER\n\n--->");

    int tmp; //number of edges connected with vertex u
    int u, v; //u and v are vertices
    int edgeWeight;
    int flag = 0;
    u = 0;

    while (u < nVertices)
    {
        printf("\nNumber of edges of vertex %d : ", u + 1);
        scanf("%d", &tmp);

        while (tmp--)
        {
            scanf("%d%d", &v, &edgeWeight);
            v--;
            //adding v in the adjacency list of u
            flag = push(&graph[u], v, edgeWeight);
            if (flag == 1)
                return NULL;
            //adding u in the adjacency list of v
            flag = push(&graph[v], u, edgeWeight);
            if (flag == 1)
                return NULL;
        }
        u++;
    }

    return graph;
}

Point* dijkstra(StackNode**graph, int source, int nVertices)
{   //result is created by using calloc so setMemberFlag is by default 0
    Point* result = (Point*) calloc( nVertices, sizeof (Point));
    HeapNode* heap = createHeap(nVertices, source);

    if (heap == NULL || result == NULL)
    {
        printf("Error in allocating memory!\n");
        return NULL;
    }

    int nElementHeap = nVertices;
    int i = 0, j;

    HeapNode tmp; //to store returned HeapNode
    while (nElementHeap > 0)
    {
        tmp = extractMin(heap, &nElementHeap);

        //when vertex from other component is returned for first time
        if (tmp.distance == INT_MAX)
            break;

        i = tmp.index;
        //now it's a member of set
        //least distance from source to vertex (i+1) is saved
        //and it's predecessor is also saved as a result
        result[i].setMemberFlag = 1;
        result[i].distance = tmp.distance;
        result[i].predecessor = tmp.predecessor;

        //i is a index of vertex that just became member of set
        StackNode* currentPtr = graph[i];

        while (currentPtr != NULL)
        {
            j = currentPtr->index;
            //if vertex j is not a member of set
            //update the distance
            if ( !(result[j].setMemberFlag) )
                decreaseKey(j, result[i].distance + (currentPtr->edgeWeight),\
                 i + 1, heap, nElementHeap);

            currentPtr = currentPtr->next;
        }
    }
    free(heap);
    return result;
}
//to create initial heap with source vertex having distance 0
//and others having infinite distance

HeapNode* createHeap(int nElement, int source)
{
    HeapNode* heap = (HeapNode*) malloc(sizeof (HeapNode) * nElement);
    if (heap == NULL)
        return NULL;
    int i = 0;
    
    while (i < nElement)
    {
        heap[i].index = i;
        heap[i].distance = INT_MAX;
        heap[i].predecessor = -1;
        i++;
    }
    //Now no need to use buildheap!
    heap[0].index = source - 1;
    heap[0].distance = 0;
    heap[source - 1].index = 0;
    return heap;
}

//it removes & returns node with minDistance from Heap
HeapNode extractMin(HeapNode* heap, int* nElement)
{
    HeapNode tmp = heap[0];
    (*nElement)--;
    heap[0] = heap[*nElement];

    minHeapify(heap, *nElement, 0);
    return tmp;
}

void decreaseKey(int v, int newDistance, int predecessor, HeapNode* heap, int nElement)
{ //if newDistance < current distance ( of vertex (v+1))
    //then it will replace distance
    int i = 0;
    //finding node with index = v
    while (i < nElement)
    {
        if (heap[i].index == v)
            break;
        i++;
    }
    //if newDistance is < oldDistance
    //update distance and make passed predecessor, Node's predecessor
    if (heap[i].distance > newDistance)
    {
        heap[i].distance = newDistance;
        heap[i].predecessor = predecessor; //passed predecessor

        HeapNode tmp; //used for exchange
        int parentIndex = (i - 1) / 2; //i is child index

        while (i > 0)
        {
            if (heap[parentIndex].distance > heap[i].distance) //if inserted key is < it's parent's Key
            { //exchange keys
                tmp = heap[i];
                heap[i] = heap[parentIndex];
                heap[parentIndex] = tmp;
                //updating childIndex and accordingly parentIndex
                i = parentIndex;
                parentIndex = (i - 1) / 2;
            }
            else
                break;
        }
    }
}

void minHeapify(HeapNode *heap, int nElement, int n)
{
    int end = PARENT(nElement); //subtracting 1 because it's a index
    int i; //index of smallest child
    HeapNode tmp; //will be used to swap nodes

    while (n <= end)
    {
        if (n == end || heap[ L_CHILD(n) ].distance <= heap[ R_CHILD(n) ].distance)
            i = L_CHILD(n);
        else
            i = R_CHILD(n);

        if (heap[n].distance > heap[i].distance)
        { //swaping heap[n] & heap[i]
            tmp = heap[n];
            heap[n] = heap[i];
            heap[i] = tmp;
            n = i; //next time it will do minHeapify for index i
        }
        else
            break;
    }
}

//delete list
void deleteStack(StackNode** headPtr)
{
    if (*headPtr == NULL)
        return;
    else
    {
        StackNode* tmpptr;
        do
        {
            tmpptr = *headPtr;
            *headPtr = (*headPtr)->next;
            free(tmpptr);
        }
        while (*headPtr != NULL);
    }
}

//push vertex with it's edgeWeigght in the adjacency list
//return 0 on success, else 1
int push(StackNode** headptr, int index, int edgeWeight)
{
    StackNode* tmpptr = (StackNode*) calloc(1, sizeof (StackNode));

    if (tmpptr == NULL)
        return 1;

    tmpptr->index = index;
    tmpptr->edgeWeight = edgeWeight;

    if (*headptr == NULL)
    {
        *headptr = tmpptr;
    }
    else
    {
        tmpptr->next = *headptr;
        *headptr = tmpptr;
    }

    return 0;
}
