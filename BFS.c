/*********************************
Name : Patel Parth Pragneshkumar *
Roll No : 111501019				 *
Code : BFS 						 *
*********************************/

#include <stdio.h>
#include <stdlib.h>

// structure for stack and queue
struct member
{
	short int point;
	struct member* next;
};

typedef struct member member;

//structure to store detail of a point of graph
struct point
{
	short int visited;
	member* head; // head of adjacency list
};

typedef struct point point;

short addInStack ( member** , short );
void deleteStack ( member** );
short enqueue ( member** , member** , short );
short dequeue ( member** , member** );
short bfs ( short , point* );
short isComplete(point*, short);

int main(void)
{	
	short trackException; //to track failure in allocating memory
	short nPoints;
	short nEdges; 

	do //number of points
	{	
		printf("Enter the number of points : ");
		scanf("%hd",&nPoints);
	} while ( nPoints < 1 );	

	do //number of edges
	{
		printf("Enter the number of edges : ");
		scanf("%hd",&nEdges);
	} while ( nEdges < 0 );

	// Dynamically allocating memory for
	// array of Point structures that represents the whole Graph
	point* graph = (point*) calloc(nPoints, sizeof(point));
	
	if ( nEdges >= 1 ) //if there are edges in graph it will take inputs for edges
	{
		printf("Enter edges :\nExample : 1 2\n\n");
		short mem1, mem2; // tmp variables to store inputs during Edge input
		short i = 1;
		
		while( i <= nEdges ) //taking input for edges
		{   
			printf("Edge %d -> ", i );
			scanf("%hd%hd",&mem1, &mem2);
			
			//ensures correct pair for of Edge
			while( mem1 < 1 || mem1 > nPoints || mem2 < 1 || mem2 > nPoints )
			{
				printf("Enter Correct Pair : \n");
				scanf("%hd%hd",&mem1, &mem2);
			}

			trackException = addInStack ( &(graph[mem1-1].head), mem2); //adding mem2 in mem1 adjacency list
			if( trackException == 0 ) //0 means failure in allocating memory
				return 1;
			
			trackException = addInStack ( &(graph[mem2-1].head), mem1); //adding mem1 in mem2 adjacency list
			if( trackException == 0 )
				return 1;

			i++;
		}
	}

	printf("\nGraph is ready!\n\
---------------------------------------------------------------\n");

	short startingPoint;

	do //assures correct startingPoint
	{	
		printf("Enter The Starting Point :");
		scanf("%hd", &startingPoint );
	} while( startingPoint < 1 || startingPoint > nPoints );

	trackException = bfs( startingPoint, graph ); 					//calling bfs
	if( trackException == 0 )
		return 1;

	//if there are more than one components
	if ( !isComplete( graph, nPoints ) )  
	{
		printf("\n--------------------------------------------------\n\
Other points are in different component.\n--------------------------------------------------\
		\n");
	}

	//clearing all memory allocated dynamically
	int i=0 ;
	while( i<nPoints) //deletes all memory allocated for adjacency list
	{
		deleteStack(&(graph[i].head));
		i++;
	}

	free(graph);
	return 0;
}

// returns 0 on failure else 1
short addInStack ( member** headptr, short addValue )
{
	member* tmpptr = (member*) calloc (1, sizeof(member));

	//checking whether memory is allocated correctly or not
	if( tmpptr == NULL )
	{
		printf("\nError in allocating memory!\n");
		return 0;
	}

	tmpptr->point = addValue;

	if( *headptr == NULL )
	{
		*headptr = tmpptr;
	}

	else
	{
		tmpptr->next = *headptr;
		*headptr = tmpptr;
	}

	return 1;
}
// returns 0 on failure else 1
short enqueue ( member** frontptr, member** backptr, short addValue )
{
	member* tmpptr = (member*) calloc (1, sizeof(member));

	//checking whether memory is allocated correctly or not
	if( tmpptr == NULL )
	{
		printf("\nError in allocating memory!\n");
		return 0;
	}

	tmpptr->point = addValue;

	if( *frontptr == NULL && *backptr == NULL )
	{
		*frontptr = tmpptr;
		*backptr = tmpptr;
	}

	else
	{
		(*backptr)->next = tmpptr;
		*backptr = tmpptr;
	}

	return 1;
}
short dequeue ( member** frontptr, member** backptr )
{
	short tmp = (*frontptr)->point; //value to be returned
	member* tmpptr = *frontptr; // point to first member that will be used to free that memory
	*frontptr = (*frontptr)->next;
	free(tmpptr);

	if( *frontptr == NULL )
	{
		*backptr = NULL;
	}
	return tmp;
}

//returns 0 on failure otherwise 1
short bfs ( short startingPoint, point* graph )
{	
	short trackException; // equals 0 when failed in allocating memory
	member* front = NULL; //front of queue
	member* back = NULL; //back of queue
	short n = 1; // no of points at specific distance from starting point
	short tmp = 1; //used to track no of points at specific distance from starting point during loop
	short distance = -1; //distance from "startingPoint"
	short currentPoint; // currentPoint of BFS process

	trackException = enqueue( &front, &back, startingPoint ); //adding startingPoint in queue
	if( trackException == 0 )
		return 0;

	graph[startingPoint-1].visited = 1;

	printf("\n\nPoint and its distance from Point %hd will be displayed in this format : Point [Distance]\n\
---------------------------------------------------------------\n", startingPoint);

	do
	{
		n = tmp;
		tmp = 0; //reseted
		distance++;

		while(n--) //scans all points at distance "distance"
		{
			currentPoint = dequeue ( &front, &back );
			printf("  ||  %hd [%hd]\n", currentPoint, distance);

			member* tmpptr = graph[currentPoint-1].head ; // currently points to head of adjacency list head

			while( tmpptr != NULL )	//it scans all member of adjacency list of currentPoint
			{
				if( graph[(tmpptr->point)-1].visited == 0 ) //if point is not visited
				{
					graph[(tmpptr->point)-1].visited = 1; //making visited
					
					trackException = enqueue( &front, &back, tmpptr->point); //adding in queue
					if( trackException == 0 )
						return 0;
					
					tmp++; //tracks no of points that are one unit more far from startingPoint than currentPoint
				}

				tmpptr = tmpptr->next;
			}

		}
	} while ( front != NULL && back != NULL );
	return 1;
}
void deleteStack ( member** headptr )
{
	member* tmpptr; // ptr used to store location of memory to be freed

	while( *headptr != NULL )
	{
		tmpptr = *headptr;
		*headptr = (*headptr)->next;
		free(tmpptr);
	}
}

//returns 1 if all points are visited else 0
short isComplete( point* graph, short nPoints )
{
    int i=0;
    while( i < nPoints)
    {
        if( graph[i].visited == 0)
            return 0;
        i++;
    }

    return 1; //if all are visited
}
