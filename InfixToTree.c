//Name : Patel Parth Prragnehskumar
//Roll No: 111501019
//this code creates expression tree from given infix expression
//also prints the tree

#include<stdio.h>
#include<stdlib.h>

#define MAX_INFIX_LEN 100 // max length of infix expression including null character
#define MAX_TOKEN_LEN 10 // max length of token including null character

//defining to store previous token type
#define lParenthesis 1
#define rParenthesis 2
#define number 3
#define operator 4

// associativity
#define leftAssoc 1
#define rightAssoc 2

//operator structure to store operator
//with it's precedance & associativity
struct operatorStruct
{
    char op ;
    short precedance ;
    short associativity ;
    struct operatorStruct *next ;
} ;

typedef struct operatorStruct operatorStruct ;

//structure for treeNode that contains a string
//and pointers to left & right child
struct treeNode
{
    char string[MAX_TOKEN_LEN];
    struct treeNode *leftPtr;
    struct treeNode *rightPtr;
};

typedef struct treeNode treeNode;

//structure for storing pointer to treeNode and pointer to next structure
struct stackNode
{
    treeNode *treePtr;
    struct stackNode *next;
};

typedef struct stackNode stackNode;

short checkExpression( char * );
int getToken( char[], char[], int ) ;
operatorStruct makeStruct ( char ) ;

//functions for treeNode Pointer stack
void addInStack_treeNode( treeNode* , stackNode**) ;
treeNode* pop_treeNode( stackNode **) ;

//functions for operator stack
void addInStack_operator ( operatorStruct , operatorStruct** ) ;
operatorStruct pop_operator ( operatorStruct**) ;

//functions for expression tree
treeNode* createTree(char[]);
void deleteTree(treeNode*);
void printTree(treeNode*);
void createMatrix(treeNode* [][20], treeNode*,short, short);

int main()
{
    char infix [MAX_INFIX_LEN] ;
    printf( "Enter the infix expression (Length must be < %d) : ", MAX_INFIX_LEN ) ;
    scanf( "%[^\n]s", infix ) ;

    if ( checkExpression(infix) )
    {
        treeNode* treeRoot = createTree(infix); //here fn will return pointer to created Tree
        printTree(treeRoot);
        deleteTree(treeRoot); //remove all allocated memory
    }

    else
        printf("\nInvalid Input!");

    return 0;
}

void createMatrix(treeNode *matrix[60][20], treeNode *tree,short x, short y)
{   while(tree)
    {
            matrix[x][y] = tree;
            createMatrix(matrix, tree->leftPtr, x+2, y-2);
            tree = tree->rightPtr;
            x+=2;
            y+=2;
    }
}

void printTree(treeNode *tree)
{
    treeNode* matrix[60][20] = { NULL };
    int x = 0;
    int y = 9;
    matrix[x][y] = tree;
    createMatrix(matrix,tree->leftPtr,2,y-2);
    createMatrix(matrix,tree->rightPtr,1,y+2);

    x=0;
    y=0;

    while(x<60)
    {   y=0;
        while(y<20)
        {
            if(matrix[x][y] == NULL)
                printf("        ");
            else
                printf("%10s",matrix[x][y]->string);
            y++;
        }
        printf("\n");
        x++;
    }
}

//adds given treeNode pointer to top of stack pointed by given head
void addInStack_treeNode ( treeNode* add , stackNode **headPtr)
{
    stackNode *tmp = (stackNode*) malloc(sizeof(stackNode));

    if (!tmp) //checks whether memory allocated succesfylly or not
    {
        printf("\n----------------------------\nError in allocating memory!\n----------------------------\n");
        return;
    }

    tmp->treePtr = add;

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

//It returns & delete top treeNode pointer from stack pointed by given head
treeNode* pop_treeNode ( stackNode **headPtr)
{
    treeNode *tmp = (*headPtr)->treePtr ; //storing top value to return it at the end
    stackNode *tmpPtr = *headPtr;  //storing it to free it later
    *headPtr = (*headPtr)->next;
    free(tmpPtr); // free memory of top structure
    return (tmp); //returns top treeNode pointer
}

// to check whether infix expression is correct or not
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
            else
                previous = number ;

            // this will skip checking of next digits because together they represents a number
            while ( '0' <= infix[++i] && infix[i] <= '9' ) ;

            i-- ;
        }

        else if ( infix[i] == ' ' ) ; //if space

        // if ( operator )
        else if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '^' || infix[i] == '/' )
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

    if ( previous != number && previous != rParenthesis )
    	return 0;

    //if everything is ok
    return 1 ;
}

void deleteTree(treeNode* treeRoot)
{
    if (treeRoot)
    {
        deleteTree(treeRoot->leftPtr);
        deleteTree(treeRoot->rightPtr);
        free(treeRoot);
    }
}
//creates a expression tree from infix and returns Root Node's pointer
treeNode* createTree(char infix[])
{
    int i=0; //i for infix
    int t=0; //t for token

    char token[MAX_TOKEN_LEN];

    stackNode* headT = NULL; //head of treeNode pointer stack
    operatorStruct* headO = NULL; //head of operator stack
    
    while (infix[i]) //runs untill null character
    {
        i = getToken(infix, token, i);
        t=0;

        if( '0'<= token[0] && token[0] <= '9' )
        {   //creates treeNode with leftChild & rightChild pointer NULL
            //and copy token in string
            treeNode* tmpNodeptr = (treeNode*) malloc(sizeof(treeNode));
            tmpNodeptr->leftPtr = NULL;
            tmpNodeptr->rightPtr = NULL;

            while(token[t])
            {
                tmpNodeptr->string[t] = token[t];
                t++;
            }
            tmpNodeptr->string[t] = '\0';

            addInStack_treeNode(tmpNodeptr, &headT);
        }

        else if ( token [t] == '(' )
		{
			addInStack_operator ( makeStruct(token[t]) , &headO ) ;
		}

		else if ( token [t] == ')' )
        {
            //untill '(' it will pop operator operator stack
            //and create a treeNode with given operator
            //it pops two treeNode pointer from stack and add them as rightChild & leftChild
            //and push this created treeNode's pointer onto the top of stack
			do
			{	treeNode* tmpPtr = (treeNode*) malloc(sizeof(treeNode));
                tmpPtr->string[0] = (pop_operator(&headO)).op ;
				tmpPtr->string[1] = '\0';
				tmpPtr->rightPtr = pop_treeNode(&headT);
           		tmpPtr->leftPtr = pop_treeNode(&headT);
           		addInStack_treeNode(tmpPtr, &headT);
			} while ( headO->op != '(' );

            pop_operator( &headO ) ; //removing leftParenthesis from operator stack
		}

        else
        {
        	operatorStruct tmp = makeStruct( token[t] ) ;

			while ( (headO != NULL) && (headO->op != '(') && (( tmp.associativity == leftAssoc && tmp.precedance <= headO->precedance ) || \
				( tmp.associativity == rightAssoc && tmp.precedance < headO->precedance )))
            {   //create a treeNode with given operator
                //it pops two treeNode pointer from stack and add them as rightChild & leftChild
                //and push this created treeNode's pointer onto the top of stack
				treeNode* tmpPtr = (treeNode*) malloc(sizeof(treeNode));
				tmpPtr->string[0] = pop_operator(&headO).op ;
				tmpPtr->string[1] = '\0';
				tmpPtr->rightPtr = pop_treeNode(&headT);
           		tmpPtr->leftPtr = pop_treeNode(&headT);
           		addInStack_treeNode(tmpPtr, &headT);
			}

			addInStack_operator( tmp, &headO ) ;
        }
    }
    //if operator stack is non-empty
    while (headO)
    {
        treeNode* tmpPtr = (treeNode*) malloc(sizeof(treeNode));
        tmpPtr->string[0] = pop_operator(&headO).op ;
        tmpPtr->string[1] = '\0';
        tmpPtr->rightPtr = pop_treeNode(&headT);
        tmpPtr->leftPtr = pop_treeNode(&headT);
        addInStack_treeNode(tmpPtr, &headT);
    }

    return pop_treeNode(&headT); //returns rootNode pointer
}

int getToken ( char *infix , char *tokenString , int i )
{
    int t = 0 ; // iterator for tokenString

    while ( infix [i] == ' ' )
        i++; // to skip space

    if ( infix[i] == '(' || infix[i] == ')' || infix[i] == '-' || infix[i] == '+' || infix[i] == '*' || \
        infix[i] == '/' || infix[i] == '^')
    {
        tokenString [t++] = infix[i++] ;
    }

    else
    {	do
        {
            tokenString [t++] = infix [i++] ;
        } while ( '0' <= infix [i] && infix [i] <= '9') ;
    }

    tokenString [t] = '\0' ;

    return i ;
}

// this returns structure containing passed operator, it's precedance & associativiity
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

//push passed structure onto the top of operator stack
void addInStack_operator ( operatorStruct add , operatorStruct **headPtr )
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

//It pop top operatorStruct from stack
operatorStruct pop_operator ( operatorStruct **headPtr)
{
    operatorStruct tmp = **headPtr; //storing top operatorStruct to return it in the end
    operatorStruct *tmpPtr = *headPtr;  //storing it to free it later

    *headPtr = (*headPtr)->next; //head will point to next to next operatorStruct
    free(tmpPtr); // free memory of top structure
    return (tmp); //returns top structure
}
