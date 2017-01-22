//Name : Patel Parth Pragneshkumar
//Roll No : 111501019
//This Program returns minimum steps & number of steps also required to complete Tower Of Hanoi Game 
//Full Recursion

#include <stdio.h>

void transferDisc(int, short, short, short);  

unsigned long int stepsCount;

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

	printf("\n----------------------------------------\nTotal Number Of Moves Required Are : %ld\n----------------------------------------\n",stepsCount);     
	return 0;
}

//Transfers given number of discs from "fromPole" to "toPole" using "usingPole"
void transferDisc(int numOfDiscs, short fromPole, short toPole, short usingPole)            
{   
	short tmp ;
	
	if (numOfDiscs == 1)
	{
		 printf("Transfer A Disc From Pole %hd To Pole %hd\n", fromPole, toPole);    //if only one disc is left then  transfer it to destination
	     stepsCount++ ;
	}
	else
	{
		transferDisc(numOfDiscs-1, fromPole, usingPole, toPole);      
		
		printf("transfer a disc from pole %hd to pole %hd\n", fromPole, toPole);
		stepsCount++ ;
		
		transferDisc(numOfDiscs-1, usingPole, toPole, fromPole);             
	}
}