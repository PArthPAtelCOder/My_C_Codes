//Name : Patel Parth Pragneshkunar
//Roll No : 111501019
//This program evaluates postfix

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_POSTFIX_LEN 100 // max length of postfix including null character
#define MAX_TOKEN_LEN 10 // max length of token including null character

struct operandStruct
{
    int operand ;
    struct operandStruct *next ;
} ;

typedef struct operandStruct operandStruct ;

short checkPostfix( char[] );
void evaluate( char[] ) ;
int getToken( char[], char[], int ) ;

//function for managing stack
void addInStack( int , operandStruct **) ;
int pop( operandStruct **) ;

int main()
{
    char postfix [MAX_POSTFIX_LEN] ;
    printf( "Enter the postfix expression (Length must be < %d) : ", MAX_POSTFIX_LEN ) ;
    scanf( "%[^\n]s", postfix ) ;

    if ( checkPostfix(postfix) )
        evaluate( postfix ) ;
    else
        printf("\nInvalid input!\n");
    return 0;
}

//checks whether unexpected characters are there or not
//if it is there then it will print error message
short checkPostfix( char postfix[] )
{
    int p = 0 ;

    while ( postfix[p] != '\0' )
    {
        if ( postfix[p] != ' ' && postfix[p] != '+' && postfix[p] != '-' && postfix[p] != '*' \
             && postfix[p] != '/' && postfix[p] != '^' && ( postfix[p] > '9' || postfix[p] < '0' ))
            return 0 ;
        p++ ;
    }
    //when everything is ok
    return 1 ;
}

//evaluates postfix & prints it
void evaluate( char postfix[] )
{
    int p = 0 ; //p is a iterator for postfix : p for postfix
    int t = 0 ; //t is a iterator for toke : t for token

    int integerA , integerB ; //these integers will be used to save operand value
    int tmp ; //will be used to calculate result of power operator
    char token[MAX_TOKEN_LEN] ;

    operandStruct *head = NULL ; //head of operandStack

    while( postfix[p] != '\0' )
    {
        p = getToken( postfix, token, p ) ;

        if ( p == -1)
            break ;

        t = 0 ;

        if ( '0' <= token[t] && token[t] <= '9' )
            addInStack ( atoi(token) , &head ) ;

        else
        {	//checking whether two operands are there or not
            //if not it will return
            if ( ( head->next == NULL ) || (head == NULL) )
            {
                printf( "\n---------------------------------------\nInvalid Input!\n---------------------------------------\n" ) ;
                if (head)
                {
                    operandStruct *tmp;

                    do
                    {
                        tmp = head->next ;
                        free( head ) ;
                        head = tmp ;
                    } while( head ) ;
                }
                return ;
            }

            integerA = pop(&head) ;
            integerB = pop(&head) ;

            if ( token[t] == '+' )
            {
                addInStack( integerB + integerA , &head ) ;
            }

            else if ( token[t] == '-' )
            {
                addInStack( integerB - integerA , &head ) ;
            }

            else if ( token[t] == '*' )
            {
                addInStack( integerB * integerA , &head ) ;
            }

            else if ( token[t] == '/' )
            {
                addInStack( integerB / integerA , &head ) ;
            }

            else if ( token[t] == '^' )
            {
                tmp = 1 ;

                //calculating integerB ^ integerA
                while( integerA-- )
                {
                    tmp *= integerB ;
                }

                addInStack( tmp , &head ) ;
            }

        }
    }

    if ( head->next != NULL )
        printf( "\nInvalid Input!\n" ) ;
    else
        printf("\n---------------------------------------\nValue is %d\
    \n---------------------------------------\n", pop(&head) ) ;
}

//this fn scans postfix string for token from p index & saves token in token string
//it returns the index from which next scanning should start
int getToken( char postfix[], char token[], int p)
{   //p is a iterator for postfix : p for postfix
    int t = 0 ; // iterator for tokenString : t for token

    // to skip space
    while ( postfix [p] == ' ' )
        p++;

    if ( postfix[p] == '-' || postfix[p] == '+' || postfix[p] == '*' || postfix[p] == '/' || postfix[p] == '^' )
    {
        token [t++] = postfix[p++] ;
    }

    else if( '0' <= postfix [p] && postfix [p] <= '9' )
    {   do
        {
            token [t++] = postfix [p++] ;
        } while ( '0' <= postfix [p] && postfix [p] <= '9') ;
    }

    else
        return -1 ;

    token [t] = '\0' ;

    return p ;
}

//adds given operand on the top of stack pointed by given head
void addInStack ( int add , operandStruct **headPtr)
{
    operandStruct *tmp = (operandStruct*) malloc(sizeof(operandStruct));

    if (!tmp) //checks whether memory allocated succesfylly or not
    {
        printf("\n----------------------------\nError in allocating memory!\n----------------------------\n");
        return;
    }

    tmp->operand = add;

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

//It returns top operand & delete top operandStruct from stack pointed by given head
int pop ( operandStruct **headPtr)
{
    int tmp = (*headPtr)->operand ; //storing top value to return it at the end
    operandStruct *tmpPtr = *headPtr;  //storing it to free it later
    *headPtr = (*headPtr)->next; //head will point to next to next operandStruct
    free(tmpPtr); // free memory of top operandStruct
    return (tmp); //returns top operand
}