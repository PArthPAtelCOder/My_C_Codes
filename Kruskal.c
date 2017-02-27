/*******************************************
Name    : Patel Parth Pragneshkumar
Roll No : 111501019
Code    : Kruskal's Algorithm,
	      Using Disjoint Set DataStructure & 
	      Path Compression 
*******************************************/

#include <stdio.h>
#include <stdlib.h>

int n_heap = 0; //number of nodes in heap
int n_edges_in_MST = 0; //number of edges in MST

#define HEAP_MAX_SIZE(n) (((n)*(n-1)/2)+1 )

#define PARENT(n) ((n)/2)
#define LEFT_CHILD_INDEX(n) (2*(n))
#define RIGHT_CHILD_INDEX(n) (2*(n)+1)

//node in disjoint set data structure
typedef struct
{
	int parent ;
	int rank ;
} subset;


typedef struct
{
	int vertex1,vertex2;
	int edgeWeight;
} edge ;

//fns for heap
edge extract_Min(edge*);
void minHeapify(edge*,int);
void buildHeap(edge*);
edge* create_Min_Heap(int);

//disjoint set data-structure fns
int find(subset* , int);
void Union(subset*, int ,int);

edge* kruskal(edge*,int);


int main(void)
{	
	int n_vertices ;
	printf("Enter the number of Vertices in the graph : ");
	scanf("%d",&n_vertices);

	edge* heap =  create_Min_Heap(n_vertices);
	//if failed in creating heap
	if ( heap == NULL )
		return 1;

	edge* MST = kruskal(heap,n_vertices);

	if (MST == NULL)
		return 1;

	if( n_edges_in_MST < n_vertices-1 )
		printf("\n-----------------------------------\nThere are more than one components.\n");

	//printing edges in the Minimum Spanning Forest
	int i = 0;
	printf("\n-------------------------------\nVertex1--Vertex2 | EdgeWeight :\n\n");
	
	while(i < n_edges_in_MST)
	{
		printf("%d--%d | %d \n", MST[i].vertex1, MST[i].vertex2, MST[i].edgeWeight );
		i++;
	}

	free(MST);
	return 0;
}

//it removes min from Heap
//returns min
edge extract_Min(edge* heap)
{
        edge tmp = heap[1];
        heap[1] = heap[n_heap];
        
        n_heap--;

        minHeapify(heap,1);
        return tmp;
}
//given a node of binary tree with left and right sub tree assumed as a heap
//convert this whole tree with given node into a Heap
void minHeapify(edge* heap, int n)
{
    int end = PARENT(n_heap); //last heapNode's parent
    int i; //index of smallest child
    edge tmp; //used to swap integers

    while (n <= end)
    {
        if (LEFT_CHILD_INDEX(n) == n_heap) //if element has only one child
            i = LEFT_CHILD_INDEX(n);
        else if (heap[LEFT_CHILD_INDEX(n)].edgeWeight <= heap[RIGHT_CHILD_INDEX(n)].edgeWeight)
            i = LEFT_CHILD_INDEX(n);
        else
            i = RIGHT_CHILD_INDEX(n);

        if (heap[n].edgeWeight > heap[i].edgeWeight)
        {
            tmp = heap[n];
            heap[n] = heap[i];
            heap[i] = tmp;

            n = i; //next time it will do minHeapify for index i
        }
        else
            break;
    }
}

void buildHeap(edge* heap)
{
	if( n_heap == 0 || n_heap == 1 )
		return ;
    else
    {
        int n = PARENT(n_heap);

        while (n >= 1)
        {
            minHeapify(heap, n);
            n--;
        }
    }
}

edge* create_Min_Heap(int n_vertices)
{
	edge* heap = (edge*) malloc(sizeof(edge) * HEAP_MAX_SIZE(n_vertices));

	if( heap == NULL )
	{
		printf("Error in allocating memory!\n");
		return NULL;
	}

	int u = 1;
	int v;
	int edgeWeight;
	int n_adjacent; //no of edges adjacent to 'u' with condition 'v' > u
	int i = 1;

	while( u <= n_vertices )
	{	
		printf("Enter Number of edges adjacent to %d with adjacent vertex > %d : ",u,u);
		scanf("%d",&n_adjacent);

		while(n_adjacent--)
		{	
			scanf("%d%d",&v,&edgeWeight);

			heap[i].vertex1 = u;
			heap[i].vertex2 = v;
			heap[i].edgeWeight = edgeWeight;

			i++;
		}
		u++;
	}

	n_heap = i-1; 

	buildHeap(heap);

	return heap;
}

edge* kruskal(edge* heap,int n_vertices)
{	
	edge* MST = (edge*)calloc(n_vertices-1, sizeof(edge));
	//DSD : Disjoint Set Data structure
	subset* DSD = (subset*) calloc(n_vertices+1,sizeof(subset));

	if ( DSD == NULL )
	{
		printf("Error in allocating memory!");
		return NULL;
	}

	int i = 1;
	
	while(i <= n_vertices)
	{	
		DSD[i].parent = i;
		i++;
	}

	while( n_heap > 0 )
	{
		edge tmp_node = extract_Min(heap);

		if( find(DSD, tmp_node.vertex1) != find(DSD, tmp_node.vertex2))
		{
			Union(DSD, tmp_node.vertex1, tmp_node.vertex2 );
			MST[n_edges_in_MST] = tmp_node ; //adding edge in MST

			n_edges_in_MST++; 
		}
	}

	free(heap);
	free(DSD);

	return MST;
}

int find(subset* DSD, int i)
{
	if ( DSD[i].parent != i)
		DSD[i].parent = find(DSD,DSD[i].parent);
		
	return DSD[i].parent ;
}

void Union(subset* DSD, int u,int v)
{	
	int u_root = find(DSD, u) ;
	int v_root = find(DSD, v) ;

	//if both trees have same depth
	//attach vertex v's subtree to vertex u's subtree
	//increase the rank of u_root by one
	if ( DSD[u_root].rank == DSD[v_root].rank )
	{
		DSD[v_root].parent = u_root;
		(DSD[u_root].rank)++;
	}
	//if subtree of vertex u has lesser depth than te depth of subtree of vertex v 
	//attach subtree of vertex u to subtree of vertex v
	else if ( DSD[u_root].rank < DSD[v_root].rank )
		DSD[u_root].parent = v_root;
	//if subtree of vertex v has lesser depth than the depth of subtree of vertex v 
	//attach subtree of vertex v to subtree of vertex u
	else
		DSD[v_root].parent = u_root;
}