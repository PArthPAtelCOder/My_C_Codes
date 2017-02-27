//Name: Patel Parth Pragneshkumar
//Roll No: 111501019

#include <stdio.h>
#include <stdlib.h>

#define lChild(n) (2*n + 1)    //it's not a 2n because it's a index starting from 0 not 1
#define rChild(n) (2*n + 2)    //same here
#define MAX_HEAP_SIZE 500

//functions for Heap
void displayHeap(int*, int);
int extractMin(int*, int*);
void findMin(int*, int nInt);
void minHeapify(int*, int, int);
void buildHeap(int*, int);
void insert(int*, int*, int);
void decreaseKey(int*, int, int, int);
void heapSort(int*, int*);

int main(void)
{
    short choice = 0; //1:Buildheap 2:findMin 3:extractMin 4:decreaseKey 5:insert 6:Display elements 7:heapSort 8:exit
    int heap[MAX_HEAP_SIZE];
    int nInt = 0; //initially heap is empty
    //used to store integer to be inserted while selecting option 5 (insert)
    //and also newKey value in decreasekey
    int add;
    int i; //used in decreaseKey option to save the index

    printf("Enter the number of elements in Heap (Use buildHeap to convert it into Heap later)\n\
	(limit is %d elements) ---> ", MAX_HEAP_SIZE);
    scanf("%d", &nInt);

    i = 0;
    while (i < nInt) //taking
    {
        printf("Element %d -->", i);
        scanf("%d", &heap[i]);
        i++;
    }

    while (choice != 8)
    {
        printf("\n\n--------------------------------\n\
1:Buildheap \n\
2:findMin \n\
3:extractMin \n\
4:decreaseKey\n\
5:insert\n\
6:Display elements \n\
7:heapSort\n\
8:exit\n\n\
Enter your Choice : ");

        scanf("%hd", &choice);
        printf("--------------------------------\n");

        while (!(choice <= 8 && choice >= 1))
        {
            printf("Enter Valid Input : ");
            scanf("%hd", &choice);
            printf("--------------------------------\n");
        }

        if (choice == 1) //buildHeap
            buildHeap(heap, nInt);

        else if (choice == 2) //findMin
            findMin(heap, nInt);

        else if (choice == 3) //extractMin
            printf("%d is extracted\n", extractMin(heap, &nInt));

        else if (choice == 4) //decreaseKey
        {
            printf("\n--------------------------------\nEnter the index (it starts from 0) and new decreased key value ---> ");
            scanf("%d%d", &i, &add);
            printf("--------------------------------\n");

            decreaseKey(heap, nInt, i, add);
        }
        else if (choice == 5) //insert
        {
            printf("Enter the key to be inserted ---> ");
            scanf("%d", &add);
            insert(heap, &nInt, add);
        }
        else if (choice == 6) //displayElements
            displayHeap(heap, nInt);
        else if (choice == 7) //heapSort
            heapSort(heap, &nInt);
    }
    return 0;
}

//display elements of Heap

void displayHeap(int*heap, int nInt)
{
    if (nInt == 0)
    {
        printf("\n--------------------------------\nHeap is Empty!\n--------------------------------\n");
    }
    else
    {
        int i = 0;
        printf("\nElements of heap ---> ");

        while (i < nInt)
            printf("%d ", heap[i++]);
    }
}

//it returns min without removing it from Heap

void findMin(int* heap, int nInt)
{
    if (nInt == 0)
    {
        printf("\n--------------------------------\nHeap is empty!\n--------------------------------\n");
    }
    else
        printf("\nMin is ---> %d\n\n", heap[0]);
}

//it removes min from Heap
//returns min

int extractMin(int* heap, int* nInt)
{
    if (*nInt == 0)
        printf("\nHeap is empty\n");
    else
    {
        int tmp = heap[0];
        heap[0] = heap[(*nInt) - 1];
        (*nInt)--;

        minHeapify(heap, *nInt, 0);
        return tmp;
    }

    return 0;
}

//given a node of binary tree with left and right sub tree assumed as a heap
//convert this whole tree with given node into a Heap

void minHeapify(int *heap, int nInt, int n)
{
    int end = (nInt / 2) - 1; //subtracting 1 because it's a index
    int i; //index of smallest child
    int tmp; //used to swap integers

    while (n <= end)
    {
        if (lChild(n) == nInt - 1) //if element has only one child
            i = lChild(n);
        else if (heap[lChild(n)] <= heap[rChild(n)])
            i = lChild(n);
        else
            i = rChild(n);

        if (heap[n] > heap[i])
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

//conver an array into Heap

void buildHeap(int* heap, int nInt)
{
    if (nInt == 0)
        printf("\nHeap is empty!\n");
    else if (nInt == 1)
        printf("\nIt's already a heap!\n");
    else
    {
        int n = (nInt / 2) - 1;

        while (n >= 0)
        {
            minHeapify(heap, nInt, n);
            n--;
        }
    }
}

//insert element in Heap

void insert(int* heap, int* nInt, int add)
{
    (*nInt)++;
    heap[*nInt - 1] = add;
    int tmp;
    int childIndex = *nInt - 1;
    int parentIndex = (childIndex - 1) / 2;

    while (childIndex > 0) //until inserted
    {
        if (heap[parentIndex] > heap[childIndex]) //if inserted key is < it's parent's Key
        { //exchange keys
            tmp = heap[childIndex];
            heap[childIndex] = heap[parentIndex];
            heap[parentIndex] = tmp;
            //updating childIndex and accordingly parentIndex
            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
        else
            break;
    }
}

//decrease key value of given index in Heap

void decreaseKey(int* heap, int nInt, int i, int add)
{
    if (i < 0 || i > (nInt - 1))
        printf("Invalid Index!\n");
    else
    {
        heap[i] = add;
        int tmp; //used for exchange
        int parentIndex = (i - 1) / 2; //i is child index

        while (i > 0)
        {
            if (heap[parentIndex] > heap[i]) //if inserted key is < it's parent's Key
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

//sort given array in non decreasing order

void heapSort(int* heap, int* nInt)
{
    buildHeap(heap, *nInt);
    printf("Elements in increasing order -->\n");

    while ((*nInt) >= 1)
    {
        printf("%d ", extractMin(heap, nInt));
    }
}