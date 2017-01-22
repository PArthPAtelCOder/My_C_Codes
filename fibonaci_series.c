#include <.h>
if (/* condition */)
{
	/* code */
}

switch()
{
	
}
//Name : Patel Parth Pragneshkumar
//Roll No : 111501019
//returns Nth term of fibonacci series

#include<stdio.h>
#include<stdlib.h>

struct snapShot //to save values that will be necessary when returning from recursive function
{
    short n; 
    struct snapShot *next; // pointer to next snapShot structure
};

typedef struct snapShot snapShot;

long fibonacci(short);
// fn for managing stack
void addInStack ( snapShot, snapShot**);
snapShot pop ( snapShot**);

int main()

{
    short n;
    long fibTerm; //to store asked fibonacci term

    printf("To get Nth fibonacci term please enter value of N : ");
    scanf("%hd",&n);

    fibTerm = fibonacci(n);
    printf("\n\nTerm %hd in fibonacci series is : %ld\n\n",n, fibTerm );
    
    return 0;
}

//return Nth fibonacci term
long fibonacci(short n)
{   
    long returnVal=0; //during fn execution value will be added in it to get Nth fibonacci term at the end of function
    snapShot *head = NULL; //head of stack
    snapShot currentSnap = {n, NULL}; 

    addInStack (currentSnap, &head);
    
    //loop will runun til stack becomes empty
    while(head)
    {   
        currentSnap = pop(&head);
        
        if(currentSnap.n == 1);  //because 0th term is 0 so need to add in returnVal
        
        else if(currentSnap.n == 2) //add 1 in returnVal because 2nd term is 1
        {
            returnVal += 1;
        }
        
        //every term of fibonacci series can be written in terms of 1st & 2nd term
        //so this algorithm adds value in returnVal only when N = 1,2
        //unless it will break term in smaller terms & proceed further
        else
        {
            snapShot newSnap = { currentSnap.n - 1, NULL};
            addInStack(newSnap, &head);
            newSnap.n = currentSnap.n - 2;
            addInStack(newSnap, &head);
        }
    }

    return (returnVal);
}

//adds given snapShot to stack pointed by given head
void addInStack ( snapShot addSnap , snapShot **headPtr)
{
    snapShot *tmp = (snapShot*) malloc(sizeof(snapShot));

    if (!tmp) //checks whether memory allocated succesfylly or not 
    {
        printf("\n----------------------------\nError in allocating memory!\n----------------------------\n");
        return;
    }

    *tmp = addSnap;

    if (!(*headPtr)) //if (stack is empty)
    {
        *headPtr = tmp;
        (*headPtr)->next = NULL;
    }

    else
    {
        tmp->next = *headPtr;
        *headPtr = tmp;
    }
}

//It returns & delete top snapShot from stack pointed by given head
snapShot pop ( snapShot **headPtr)
{   
    snapShot tmpSnap = **headPtr; //storing top snapShot to return it in the end
    snapShot *tmpPtr = *headPtr;  //storing it to free it later

    *headPtr = (*headPtr)->next; //head will point to next to next snapShot
    free(tmpPtr); // free memory of top snapShot
    return (tmpSnap); //returns top snapShot
}