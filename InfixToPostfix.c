//Name : Patel Parth Pragneshkunar
//Roll No : 111501019
//This program converts infix expression into postfix

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100 // max length of expression ; INCLUDING NULL CHARACTER
#define MAX_TOKEN_LEN 10 // maximim token length of token (INCLUDING NULL CHARACTER): it affects size of number that can be scanned

//defining to store previous token type
#define lParenthesis 1
#define rParenthesis 2
#define number 3
#define operator 4

// associativity
#define leftAssoc 1
#define rightAssoc 2

struct operatorStruct
{
	char op ;
	short precedance ;
	short associativity ;
	struct operatorStruct *next ;
} ;

typedef struct operatorStruct operatorStruct ;

short checkExpression( char * );
void createPostfix ( char*, char* );
int getToken ( char *, char *, int i ) ;
operatorStruct makeStruct ( char ) ;

//function for stack management
void addInStack ( operatorStruct , operatorStruct** ) ;
operatorStruct pop ( operatorStruct**) ;

int main()
{
    char infix [MAX_LENGTH];


    printf("Enter the expression to be converted into postfix (LENGTH MUST BE < %d): ", MAX_LENGTH );
    scanf( "%[^\n]s", infix ) ;

    if( checkExpression( infix ) )
    {
	   char postfix [MAX_LENGTH] ;
	   createPostfix ( infix, postfix ) ;

	   printf( "\npostfix is : %s\n" , postfix );
    }

    else
    	printf("\nInvalid Input!\n");

    return 0;
}

// to check whether expression is correct or not
short checkExpression( char *infix )
{	// "previous" variable store previously encountered token's type
	// token types are : lParenthesis , rParenthesis , number , operator
    // this default value allows only number or lParenthesis as a first token
	short previous = operator ;
	// parenthesis variable will be used to check whether number of parenthesis are correct or not
	// whenever we encounter "(" value will be increased by one & when we encounter ")" value will be decreased by one
	// so at last value of parenthesis variable must be 0
	short parenthesis = 0 ;
	int i ;
	
	for (  i = 0 ; infix[i] ; ++i )
	{
		if ( '0' <= infix[i] && infix[i] <= '9' ) // if (digit)
		{
			if ( previous != operator && previous != lParenthesis )
				return 0 ;

			previous = number ;

			// this will skip checking of next digits because together they represents a number
			while ( '0' <= infix[++i] && infix[i] <= '9' ) ;

			i-- ;
		}

		else if ( infix[i] == ' ' ) ; //space

		else if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '^' || infix[i] == '/' ) // if ( operator )
		{
			if ( previous != number && previous != rParenthesis )
				return 0 ;

			previous = operator ;
		}

		else if ( infix[i] == '(' )
		{
			if ( previous != operator && previous != lParenthesis )
				return 0 ;

			parenthesis++ ;

			previous = lParenthesis ;
		}

		else if ( infix[i] == ')' )
		{
			if ( previous != number && previous != rParenthesis )
				return 0 ;

			parenthesis-- ;

			previous = rParenthesis ;
		}

		else
			return 0 ;
	}

	if ( parenthesis != 0 )
		return 0 ;

	//if everything is ok
	return 1 ;
}

void createPostfix ( char *infix, char *postfix )
{
	int i = 0 ; // it points to location of infix to be checked for finding token
	int t = 0 ; // points to current location in token string
	int p = 0 ; // points to current location of postfix string

	char token [MAX_TOKEN_LEN] ;

	operatorStruct *head = NULL ; // head to operator stack

	while( infix[i] )
	{
		i = getToken ( infix, token, i ) ;
		t = 0 ;

		if ( '0' <= token [t] && token [t] <= '9' )
		{
			while ( token[t] )
			{
				postfix [p++] = token [t++] ;
			}

			postfix [p++] = ' ' ;
		}

		else if ( token [t] == '(' )
		{
			addInStack ( makeStruct(token[t]) , &head ) ;
		}

		else if ( token [t] == ')' )
		{
			do
			{
				postfix [p++] = (pop(&head)).op ;
				postfix [p++] = ' ' ; //adding space after operator
			} while ( head->op != '(' );

			pop( &head ) ; //removing leftParenthesis from stack
		}

		else
		{
			operatorStruct tmp = makeStruct( token[t] ) ;

			while ( (head != NULL) && (head->op != '(') && (( tmp.associativity == leftAssoc && tmp.precedance <= head->precedance ) || \
				( tmp.associativity == rightAssoc && tmp.precedance < head->precedance )))
			{
				postfix [p++] = pop(&head).op ;
				postfix [p++] = ' ' ; //adding space
			}

			addInStack( tmp, &head ) ;
		}
	}

	while (head)
	{
		postfix [p++] = pop(&head).op ;
		postfix [p++] = ' ' ; //adding space
	}

	postfix [p] = '\0' ;
}

int getToken ( char *checkString , char *tokenString , int i )
{
	int j = 0 ; // iterator for tokenString

	while ( checkString [i] == ' ' )
		i++; // to skip space

	if ( checkString[i] == '(' || checkString[i] == ')' || checkString[i] == '-' || checkString[i] == '+' || checkString[i] == '*' || \
		checkString[i] == '/' || checkString[i] == '^')
	{
		tokenString [j++] = checkString[i++] ;
	}

	else
	{	do
		{
			tokenString [j++] = checkString [i++] ;
		} while ( '0' <= checkString [i] && checkString [i] <= '9') ;
	}

	tokenString [j] = '\0' ;

	return i ;
}

// this returns structure containing operator, it's precedance & and associativiity
operatorStruct makeStruct( char query )
{
	operatorStruct tmp ;
	tmp.next = NULL ;
	tmp.op = query ;

	if ( query == '+' || query == '-' )
	{
		tmp.precedance = 1 ;
		tmp.associativity = leftAssoc ;
	}

	else if ( query == '*' || query == '/' )
	{
		tmp.precedance = 2 ;
		tmp.associativity = leftAssoc ;
	}

	else if ( query == '(' || query == ')' )
	{
		tmp.precedance = 0 ; // 0 means nothing
		tmp.associativity = 0 ; // 0 means nothing
	}

	else
	{
		tmp.precedance = 3 ;
		tmp.associativity = rightAssoc ;
	}

	return tmp ;
}

//adds given snapShot to stack pointed by given head
void addInStack ( operatorStruct add , operatorStruct **headPtr )
{
    operatorStruct *tmp = (operatorStruct*) malloc(sizeof(operatorStruct));

    if (!tmp) //checks whether memory allocated succesfylly or not
    {
        printf( "\n----------------------------\nError in allocating memory!\n----------------------------\n" ) ;
        return ;
    }

    *tmp = add;

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

//It returns & delete top operatorStruct from stack pointed by given head
operatorStruct pop ( operatorStruct **headPtr)
{
    operatorStruct tmp = **headPtr; //storing top operatorStruct to return it in the end
    operatorStruct *tmpPtr = *headPtr;  //storing it to free it later

    *headPtr = (*headPtr)->next; //head will point to next to next operatorStruct
    free(tmpPtr); // free memory of top structure
    return (tmp); //returns top structure
}