//Name : Patel Parth Pragneshkunar
//Roll No : 111501019
//This program creates a expression tree from postfix & prints it


#include<stdio.h>
#include<stdlib.h>

#define MAX_POSTFIX_LEN 100 // max length of postfix including null character
#define MAX_TOKEN_LEN 10 // max length of token including null character

struct treeNode
{
    char string[MAX_TOKEN_LEN];
    struct treeNode *leftPtr;
    struct treeNode *rightPtr;
};

typedef struct treeNode treeNode;

struct stackNode
{
    treeNode *treePtr;
    struct stackNode *next;
};

typedef struct stackNode stackNode;

short checkPostfix( char[] );
int getToken( char[], char[], int ) ;

//function for stack
void addInStack( treeNode* , stackNode**) ;
treeNode* pop( stackNode **) ;

//function for tree
treeNode* createTree(char[]);
void deleteTree(treeNode*);
void printTree(treeNode*);
void createMatrix(treeNode* [][20], treeNode*,short, short);

int main()
{
    char postfix [MAX_POSTFIX_LEN] ;
    printf( "Enter the postfix expression (Length must be < %d) : ", MAX_POSTFIX_LEN ) ;
    scanf( "%[^\n]s", postfix ) ;

    if ( checkPostfix(postfix) )
    {
        treeNode* treeRoot = createTree(postfix);
        printTree(treeRoot);
        deleteTree(treeRoot);
    }
    else
        printf("\nInvalid Input!");

    return 0;
}

//adds given operand on the top of stack pointed by given head
void addInStack ( treeNode* add , stackNode **headPtr)
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

//It returns top operand & delete top operandStruct from stack pointed by given head
treeNode* pop ( stackNode **headPtr)
{
    treeNode *tmp = (*headPtr)->treePtr ; //storing top value to return it at the end
    stackNode *tmpPtr = *headPtr;  //storing it to free it later
    *headPtr = (*headPtr)->next; //head will point to next to next operandStruct
    free(tmpPtr); // free memory of top operandStruct
    return (tmp); //returns top operand
}

//returns 1 if postfix expression is right else returns 0
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

    p=0;

    short operands=0; //used to track no of operands

    char token[MAX_TOKEN_LEN];

    while(postfix[p])
    {
        p = getToken(postfix,token,p);

        if ( '0' <= token[0] && token[0] <= '9' )
            operands++;
        else
        {
            if(operands < 2) return 0;
            operands--;
        }
    }
    //because at last only operand is answer
    if(operands != 1)
        return 0;

    //when everything is ok
    return 1 ;
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

    token [t] = '\0' ;

    // to skip space
    while ( postfix [p] == ' ' )
        p++;

    return p ;
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

treeNode* createTree(char postfix[])
{
    int p=0; //p for postfix
    int t=0; //t for token

    char token[MAX_TOKEN_LEN];

    stackNode* head = NULL;

    while (postfix[p])
    {
        p = getToken(postfix, token, p);

        if( '0'<= token[0] && token[0] <= '9' )
        {
            treeNode* tmpNodeptr = (treeNode*) malloc(sizeof(treeNode));
            tmpNodeptr->leftPtr = NULL;
            tmpNodeptr->rightPtr = NULL;

            t=0;
            while(token[t])
            {
                tmpNodeptr->string[t] = token[t];
                t++;
            }

            tmpNodeptr->string[t] = '\0';
            addInStack(tmpNodeptr, &head);
        }

        else
        {
            treeNode *tmpPtr = (treeNode*) malloc(sizeof(treeNode));

            tmpPtr->string[0] = token[0];
            tmpPtr->string[1] = '\0';

            tmpPtr->rightPtr = pop(&head);
            tmpPtr->leftPtr = pop(&head);
            addInStack(tmpPtr, &head);
        }
    }

    return pop(&head);
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
