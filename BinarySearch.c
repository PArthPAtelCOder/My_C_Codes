#include <stdio.h>
#include <stdlib.h>

#define PARTH 32

//function to sort given integers
void quickSort( int[], int, int ) ;
int pivotPosition ( int[], int, int ) ;
void exchange ( int numbers[], int, int, int ) ;

//to check whether the data array contains query or not
int binarySearch (int[], int, int, int);


int main()
{
    int n; //number of integers
    printf("Enter the number of integers to be sorted : ");
    scanf("%d", &n);

    int *data = (int *) malloc(n*sizeof(int));

    printf("\n\nEnter those integers one by one :\n");

    //Taking input to be sorted
    for(int i=0; i<n ; i++)
    {
        scanf("%d",&data[i]);
    }

    //sorting given integers in increasing order
    quickSort(data, 0, n-1);

    int query;

    printf("\n\n--------------------\nEnter the query : ");
    scanf("%d",&query);

    if(query < data[0] || query > data[n-1])
    {
        printf("\n--------------------\nNot Found!\n--------------------\n");
    }
    else
    {
        binarySearch(data, query, 0, n-1);
    }

    free(data);
    return 0;
}

//checks whether the query is there in array data or not
//if it's there it will print it's position in increasingly sorted array

int binarySearch (int data[], int query, int start, int end)
{
    while(start <= end)
    {void swap ( int[], int, int ) ;
        int mid = ( start + end )/2 ;

        if(query == data[mid])
        {
            printf("----------------------------------------\nPosition of Element is %d\n----------------------------------------\n\n", mid+1);
            return 0;
        }

        else if(query < data[mid])
        {
            end = mid-1;
        }

        else
        {
            start = mid+1 ;
        }
    }

    printf("\nNot Found!\n\n");
    return 0;
}

// this fn sorts integers in given array in increasing order
// integers between indexes "start" & "end" will be sorted

void quickSort( int numbers[], int start, int end )
{
    while ( start != end )
    {
        int pivotPos = pivotPosition ( numbers, start, end ) ;

        if (pivotPos == start)
        {
            start++;
        }

        else if (pivotPos == end)
        {
            end--;
        }

        else
        {
            exchange (numbers, start, end, pivotPos ) ; // this insures that the integers on the left side of pivot are small or equal
            quickSort(numbers, pivotPos+1, end ) ;
            end = pivotPos - 1;

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
