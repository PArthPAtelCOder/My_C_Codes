
//Name : Patel Parth Pragneshkumar
//Roll No : 111501019
//Returns minimum steps & number of steps required to complete Tower Of Hanoi game

#include<stdio.h>
#include<stdlib.h>

struct snapShot //to store current values that will be used later after returning from recursive fn
{
    int numOfDiscs;
    short fromPole, toPole, usingPole;
    struct snapShot *next; // pointer to next snapShot
    short stage; //only two stages are there : 0,1
};

typedef struct snapShot snapShot;


void transferDisc(int, short, short, short);
// fn for managing stack
void addInStack ( snapShot, snapShot**);
snapShot pop ( snapShot**);

long stepsCount; //automatically initialised as 0 because it's a global variable

int main()
{
    short fromPole, usingPole, toPole;
    
    printf("Please Enter From Which Pole You Wanna Transfer Discs To Which Pole Using Which Pole One By One:\n\n");
    printf("From Pole : ");
    scanf("%hd", &fromPole);
    printf("To Pole : ");
    scanf("%hd", &toPole);
    printf("Using Pole : ");
    scanf("%hd", &usingPole);
    
    int numOfDiscs;

    printf("\n\nPlease Enter The Number Of Discs On The Pole Number %hd : ", fromPole);   
    scanf("%d", &numOfDiscs);
    printf("\n\n");
    
    transferDisc(numOfDiscs, fromPole, toPole, usingPole);

    printf("\n----------------------------------------\nTotal Number Of Moves Required Are : %ld\
        \n----------------------------------------\n",stepsCount);     
    return 0;
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

//It returns & delete top snapShot from stack pointed
//by given head
snapShot pop ( snapShot **headPtr)
{   
    snapShot tmpSnap = **headPtr; //storing top snapShot to return it in the end
    snapShot *tmpPtr = *headPtr;  //storing it to free it later

    *headPtr = (*headPtr)->next; //head will point to next to next snapShot
    free(tmpPtr); // free memory of top snapShot
    return (tmpSnap); //returns top snapShot
}

//Transfers given number of discs from "fromPole" to "toPole" using "usingPole"
void transferDisc(int numOfDiscs, short fromPole, short toPole, short usingPole)            
{   
    snapShot *head = NULL;
    snapShot currentSnap = { numOfDiscs, fromPole, toPole, usingPole, NULL, 0 };

    addInStack(currentSnap, &head);
    
    //as stack will become empty loop will stop
    while(head)
    {   
        currentSnap = pop(&head);
        
        //based on stage running different parts
        switch(currentSnap.stage)
        {
            case 0: if (currentSnap.numOfDiscs == 1)
                    {
                        //if only one disc is left then  transfer it to destination
                        printf("Transfer A Disc From Pole %hd To Pole %hd\n", currentSnap.fromPole, currentSnap.toPole);
                        stepsCount++ ;
                        continue;
                    }
                    else
                    {   
                        snapShot newSnap = { currentSnap.numOfDiscs - 1, currentSnap.fromPole, currentSnap.usingPole, currentSnap.toPole, NULL, 0};   
                        currentSnap.stage = 1;
                        addInStack (currentSnap, &head);
                        addInStack (newSnap, &head);
                    }
                    break;

            case 1: printf("transfer a disc from pole %hd to pole %hd\n", currentSnap.fromPole, currentSnap.toPole);
                    stepsCount++ ;
                    snapShot newSnap = { currentSnap.numOfDiscs - 1, currentSnap.usingPole, currentSnap.toPole, currentSnap.fromPole, NULL, 0};
                    addInStack (newSnap, &head);
                    break;
        }
    }
}
