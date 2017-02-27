//Name: Patel Parth Pragneshkumar
//Roll No: 111501019

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define L_CHILD(n) (2*(n) + 1)    //it's not a 2n because it's a index starting from 0 not 1
#define R_CHILD(n) (2*(n) + 2)    //same here
#define PARENT(n) (((n)/2) - 1) //parent index of node[n]

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
} Point;

//functions for graph
int** createGraph(int);
Point* dijkstra(int**, int, int);
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

    int** graph = createGraph(nVertices);
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
        printf("%d | %d | %d\n", i + 1, minDistData[i].distance, minDistData[i].predecessor);
        i++;
    }
    free(minDistData);
    free(graph);
    return 0;
}

int** createGraph(int nVertices)
{
    int i = 0;

    //creating nVertices * nVertices matrix representing Graph
    int**graph = (int**) calloc(nVertices, sizeof (int*));

    if (graph == NULL)
        return NULL;

    while (i < nVertices)
    {
        graph[i] = (int*) calloc(nVertices, sizeof (int));
        if (graph[i] == NULL)
            return NULL;
        i++;
    }

    printf("Enter the Vertex then it's number of edges and then vertice \
        connected with it with edge weight.\n\
        START IN INCREASING ORER\n\n--->");

    int tmp; //number of edges connected with vertex u
    int u, v; //u and v are vertices
    int edgeWeight;

    u = 0;
    while (u < nVertices)
    {
        printf("\nNumber of edges of vertex %d : ", u + 1);
        scanf("%d", &tmp);

        while (tmp--)
        {
            scanf("%d%d", &v, &edgeWeight);
            v--;
            graph[u][v] = edgeWeight;
            graph[v][u] = edgeWeight;
        }
        u++;
    }

    return graph;
}

Point* dijkstra(int**graph, int source, int nVertices)
{
    Point* result = (Point*) malloc(sizeof (Point) * nVertices);
    short* setMemeber = (short*) calloc(nVertices, sizeof (short));

    HeapNode* heap = createHeap(nVertices, source);

    if (heap == NULL || result == NULL || setMemeber == NULL)
    {
        printf("Error in allocating memory!\n");
        return NULL;
    }

    int nElementHeap = nVertices;
    int i = 0, j;

    while (i < nVertices)
    {
        result[i].distance = INT_MAX;
        result[i].predecessor = -1;
        i++;
    }

    HeapNode tmp; //to store returned HeapNode
    while (nElementHeap > 0)
    {
        tmp = extractMin(heap, &nElementHeap);

        //when vertex from other component is returned for first time
        if (tmp.distance == INT_MAX)
            break;

        i = tmp.index;
        setMemeber[i] = 1; //now it's a member of set
        //least distance from source to vertex (i+1) is saved
        //and it's predecessor is also saved as a result
        result[i].distance = tmp.distance;
        result[i].predecessor = tmp.predecessor;

        //i is a index of vertex that just became member of set
        j = 0;
        while (j < nVertices)
        { //if vertex is adjacent and it's not a member of set
            if (graph[i][j] && !setMemeber[j])
                decreaseKey(j, result[i].distance + graph[i][j],\
                 i + 1, heap, nElementHeap);
            j++;
        }
    }
    free(heap);
    free(setMemeber);
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
//

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
