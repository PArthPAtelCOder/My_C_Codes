#include<stdio.h>
#include<stdlib.h>

void quickSort( int[], int, int ) ;
int pivotPosition ( int[], int, int ) ;
void swap ( int[], int, int ) ;
void exchange ( int numbers[], int, int, int ) ;

int main()
{  
	int n ; // number of integers to be sorted
	
	printf("Enter the number of integers : ") ;
	scanf("%d", &n) ;
    
    while ( n<=1 )
    {
    	printf("\nenter valid value : ");
    	scanf("%d", &n) ;
    }
    
    // creating an int array to store data to be sorted
	int* numbers = (int*) malloc ( n * sizeof(int)) ; 

    // taking inputs for sorting
	printf("\nEnter those %d integers one by one :\n",n );
	for ( int i = 0 ; i < n ; i++ )
	{
		scanf("%d",&numbers[i]);
	}

	quickSort ( numbers, 0, n-1 ) ;
    
    // printing sorted integers
	printf("\n\nSorted Integers : ");
	for (int i = 0; i < n; ++i)
	{
		printf("%d ",numbers[i] ) ;
    }
    
    free(numbers);
	return 0 ;
}


// this fn sorts integers in given array in increasing order 
// integers between indexes "start" & "end" will be sorted

void quickSort( int numbers[], int start, int end )
{   
	if ( start != end )
    {
		int pivotPos = pivotPosition ( numbers, start, end ) ;

		if (pivotPos == start)
		{
			quickSort(numbers, start+1 , end) ;
		}

		else if (pivotPos == end)
		{
			quickSort(numbers, start, end-1) ;
		}
		
	    else
	    {
	    	exchange (numbers, start, end, pivotPos ) ; // this insures that the integers on the left side of pivot are small or equal
	    	quickSort(numbers, start, pivotPos-1 ) ;
	        quickSort(numbers, pivotPos+1, end ) ;
	    }
	}    
}

//  find the right place of first integer ( first in the given range ) in the array and replace it 
// returns new position of pivot
int pivotPosition ( int numbers[], int start, int end )
{
    int k=0 ;
    
	for ( int i = start + 1 ; i <= end ; i++ )
    {
        if ( numbers[i] <= numbers[start] )
        {
        	k++ ;
        }
    }
    
    if ( k!=0 )
    {   // swaping numbers[start] & numbers[start+k]
    	int tmp = numbers[start] ;
		numbers[start] = numbers[start+k] ;
		numbers[start+k] = tmp ;
    }

    return (start + k) ;
}
                 
// swap two numbers of given indexes of given array  
void swap ( int numbers[], int a, int b )
{
	
}

// this fn ensures that integers on the left side of pivot are less than or equal to the pivot within given index range
// right side integers will be greater than pivot
void exchange (int numbers[], int start, int end, int pivotPos)
{
	for (int i = start, k = pivotPos + 1 ; i < pivotPos ; ++i)
	 {
	 	if ( numbers[i] > numbers[pivotPos] )
	 	{
	 		while (1)
	 		{
	 			if ( numbers[k] <= numbers[pivotPos] )
	 			{   // swaping numbers[i] & numbers[k]
	 				int tmp = numbers[i] ;
					numbers[i] = numbers[k] ;
					numbers[k] = tmp ;
	 				break ;
	 			}

	 			k++ ;
	 		}
	 	}
	 } 
}
