//Name: Patel Parth Pragneshkumar
//Roll No: 111501019
//this code creates BST : Binary Search Tree
//contains fns for insertion, deletion, printing , searching, depth of BST,
//finding max & min value of BST

#include<stdio.h>
#include<stdlib.h>

struct treeNode
{
    int value;
    struct treeNode* lChildptr;
    struct treeNode* rChildptr;
};

typedef struct treeNode treeNode;

//functions for BST
void postOrderTraversal(treeNode*);
void preOrderTraversal(treeNode*);
void inOrderTraversal(treeNode*);
void insert(int, treeNode**);
int deleteNode(int, treeNode**);
void search(int, treeNode*);
void deleteTree(treeNode*);
int minInTree(treeNode *);
int maxInTree(treeNode *);
int getTreeDepth( treeNode *);

int main(void)
{
    short choice = 0;  //choices : 1-insert, 2-delete, 3-print,4-search, 5-Min in tree, 6-Max in tree,
    //7 -depth of Tree, 8-Exit
    treeNode* root = NULL; //pointer to root of BST
    int num_add;  // to store number to be added in BST
    int num_delete; // to store number to be deleted from BST
    int num_search; //to store number to be searched

    while(choice != 8)
    {
        printf("\n--------------------------------\n\
To Insert node in BST : 1\n\
To Delete node from BST : 2\n\
To Print BST : 3\nTo Search Tree : 4\n\
To Find Minimum value in BST : 5\n\
To Find Maximum in BST : 6\n\
To Get Depth of Tree : 7\n\
To Exit : 8\n\n\
Enter your Choice : ");

        scanf("%hd",&choice);
        printf("--------------------------------\n");

        while( choice != 1 && choice != 2 && choice  != 3 \
               && choice !=4 && choice != 5 && choice != 6 \
               && choice != 7 && choice!= 8 )
        {
            printf("Enter Valid Input : ");
            scanf("%hd",&choice);
            printf("--------------------------------\n");
        }

        if (choice == 1) //insert
        {
            printf("\n--------------------------------\nEnter the number which you wanna add : ");
            scanf("%d",&num_add);
            printf("--------------------------------\n");

            insert(num_add, &root);
        }

        else if (choice == 2) //Delete
        {
            if (!root)
            {
                printf("\n--------------------------------\nNothing to Delete!\n--------------------------------\n");
                continue;
            }

            else
            {   printf("\n--------------------------------\nEnter the number which you wanna delete: ");
                scanf("%d",&num_delete);
                printf("--------------------------------\n");

                if(deleteNode(num_delete, &root))
                    printf("\n--------------------------------\n%d is Succesfully Deleted from Tree\n--------------------------------\n", num_delete);
            }
        }

        else if (choice == 3) //Print
        {
            if (!root)
            {
                printf("--------------------------------\nNothing to print!\n--------------------------------\n");
                continue;
            }

            printf("\n--------------------------------\n1 : Pre-Order Traversal\n2 : In-Order Traversal\n3 : Post-Order Traversal\
\n\nEnter Your Choice : ");
            scanf("%hd",&choice);

            printf("--------------------------------\n");

            while( choice != 1 && choice != 2 && choice != 3 )
            {
                printf("\n--------------------------------\nEnter Valid Input : ");
                scanf("%hd",&choice);
                printf("--------------------------------\n");
            }

            switch (choice)
            {
               case 1:
                   printf("\n--------------------------------\nPre-order Traversal : ");
                   preOrderTraversal(root);
                   printf("\n--------------------------------\n");
                   break;
               case 2:
                   printf("\n--------------------------------\nIn-order Traversal : ");
                   inOrderTraversal(root);
                   printf("\n--------------------------------\n");
                   break;
               case 3:
                   printf("\n--------------------------------\nPost-order Traversal : ");
                   postOrderTraversal(root);
                   printf("\n--------------------------------\n");
                   break;
            }
        }

        else if (choice == 4) //search tree
        {
            if (!root)
            {
                printf("--------------------------------\nNothing to search!\n--------------------------------\n");
                continue;
            }

            printf("\n--------------------------------\nEnter the number which you wanna search: ");
            scanf("%d",&num_search);
            printf("--------------------------------\n");
            search(num_search, root);
        }

        else if (choice == 5) //min in tree
        {
            if (!root)
            {
                printf("\n--------------------------------\nTree is Empty!\n--------------------------------\n");
                continue;
            }

            else
                printf("\n--------------------------------\nMin value in tree is %d\n--------------------------------\n", minInTree(root));
        }

        else if (choice == 6) //max in tree
        {
            if (!root)
            {
                printf("\n--------------------------------\nTree is Empty!\n--------------------------------\n");
                continue;
            }

            else
                printf("\n--------------------------------\nMax value in tree is %d\n--------------------------------\n", maxInTree(root));
        }

        else if (choice == 7) //depth of tree
        {
            if(!root)
                printf("\nTree is empty!");
            else
                printf("\n--------------------------------\nDepth of Tree is %d\
\n--------------------------------\n", getTreeDepth(root));
        }
    }

    deleteTree(root); //de-allocate all memory allocated for tree
    printf("\n--------------------------------\n\
Whole tree is deleted.\n--------------------------------\n\n");
}

//prints BST in post-order traversal
void postOrderTraversal(treeNode* ptr)
{
    if(ptr)
    {
        postOrderTraversal(ptr->lChildptr);
        postOrderTraversal(ptr->rChildptr);
        printf("%d ",ptr->value);
    }
}

//prints BST in pre-order traversal
void preOrderTraversal(treeNode* ptr)
{
    if(ptr)
    {
        printf("%d ",ptr->value);
        preOrderTraversal(ptr->lChildptr);
        preOrderTraversal(ptr->rChildptr);
    }
}

//prints BST in in-order traversal
void inOrderTraversal(treeNode* ptr)
{
    if(ptr)
    {
        inOrderTraversal(ptr->lChildptr);
        printf("%d ",ptr->value);
        inOrderTraversal(ptr->rChildptr);
    }
}

//inserts given value in BST
//equal and bigger values will be added in the right subtree
void insert(int addValue, treeNode** rootptr)
{
    while(1) //because removed tail recursion
    {
        if (!(*rootptr))
        {
            treeNode* tmp = (treeNode*) malloc( sizeof(treeNode) );
            tmp->rChildptr = tmp->lChildptr = NULL ;
            tmp->value = addValue ;
            *rootptr = tmp;

            printf("\n--------------------------------\n%d is inserted.\n--------------------------------\n",addValue);
            return ;
        }

        else
        {
            if ( addValue < ((*rootptr)->value) )
                rootptr = &(*rootptr)->lChildptr;

            else
                rootptr = &(*rootptr)->rChildptr;
        }
    }
}

//delete given value from BST
//on succesfull deletion returns 1
//if there are multiple nodes containing same value only first will be deleted
int deleteNode(int deleteValue, treeNode** rootptr)
{
    treeNode* parentptr = NULL;
    treeNode* nodeptr = *rootptr;

    while(1) //because tail recursion is removed
    {
        if(nodeptr)
        {
            if( deleteValue == nodeptr->value )
                break;
            else if ( deleteValue < nodeptr->value )
            {
                parentptr = nodeptr;
                nodeptr = nodeptr->lChildptr;
            }
            else
            {   parentptr = nodeptr;
                nodeptr = nodeptr->rChildptr;
            }
        }

        else
        {   printf("\n--------------------------------\nSorry, it's not there in the Tree!\n--------------------------------\n");
            return 0;
        }
    }
    
    //if node is leaf
    if ( nodeptr->lChildptr == NULL && nodeptr->rChildptr == NULL )
    {   //if deleting node is root
        if( parentptr == NULL )
        {
            *rootptr = NULL;
            free(nodeptr); //deleting asked node
        }

        else
        {
            if( parentptr->lChildptr == nodeptr )
                parentptr->lChildptr = NULL;

            else
                parentptr->rChildptr = NULL;

            free(nodeptr); //deleting asked node
        }
    }
    //if node has only one child
    else if ( nodeptr->lChildptr == NULL || nodeptr->rChildptr == NULL )
    {   //if deleting node is root
        if( parentptr == NULL )
        {
            if( nodeptr->lChildptr == NULL )
                *rootptr = nodeptr->rChildptr;

            else
                *rootptr = nodeptr->lChildptr;
            free(nodeptr); //deleting asked node
        }

        else
        {
            if( parentptr->lChildptr == nodeptr )
            {
                if( nodeptr->lChildptr == NULL )
                    parentptr->lChildptr = nodeptr->rChildptr;

                else
                    parentptr->lChildptr = nodeptr->lChildptr;
            }

            else
            {
                if( nodeptr->lChildptr == NULL )
                    parentptr->rChildptr = nodeptr->rChildptr;

                else
                    parentptr->rChildptr = nodeptr->lChildptr;
            }

            free(nodeptr); //deleting asked node
        }
    }
    //if node has two child
    else
    {
        nodeptr->value = minInTree(nodeptr->rChildptr); //replacing with in-order successor
        deleteNode(nodeptr->value, &(nodeptr->rChildptr)); //deleting in-order successor
    }

    return 1; //when succesfully deleted
}

//serach given value in BST
void search(int deleteValue, treeNode* root)
{   while(1) //because tail recursion is removed
    {
        if(root)
        {
            if( deleteValue == root->value )
            {
                printf("\n--------------------------------\n\nYes, it is there in the Tree!\n--------------------------------\n");
                return;
            }
            else if ( deleteValue < root->value )
                root = root->lChildptr;
            else
                root = root->rChildptr;
        }

        else
        {   printf("\n--------------------------------\nSorry, it's not there in the Tree!\n--------------------------------\n");
            return;
        }
    }
}

//delete whole BST
void deleteTree(treeNode* rootptr)
{
    if(rootptr)
    {
        deleteTree(rootptr->lChildptr);
        deleteTree(rootptr->rChildptr);
        free(rootptr);
    }
}
//returns min value in BST
int minInTree(treeNode *rootptr)
{
    while(1)
    {
        if(rootptr->lChildptr != NULL)
            rootptr = rootptr->lChildptr;
        else
            return (rootptr->value);
    }
}
//returns max value in BSt
int maxInTree(treeNode *rootptr)
{
    while(1)
    {
        if(rootptr->rChildptr != NULL)
            rootptr = rootptr->rChildptr;
        else
            return (rootptr->value);
    }
}
//returns depth of BST
int getTreeDepth( treeNode *rootptr)
{
    if(!rootptr) //if tree is empty
        return -1;
    else
    {
        int lDepth = getTreeDepth(rootptr->lChildptr); //get Depth of left sub-tree
        int rDepth = getTreeDepth(rootptr->rChildptr); //get depth of right sub-tree
        //returns max depth + 1
        //extra one is for current node
        return (( (lDepth >= rDepth) ? lDepth : rDepth) + 1 ) ;
    }
}
