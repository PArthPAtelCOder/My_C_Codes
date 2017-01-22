// Name : Patel Parth Pragneshkumar
// Roll No : 111501019
//To create stack & to reverse it 

#include<stdio.h>
#include<stdlib.h>

struct node 
{
	int number;
	struct node *next; // pointer to next node
};

typedef struct node node;

node * reverseStack(node *, node *);

int main()
{
	short choice = 0;  //choices : add, delete, print, reverse, exit
	node* head = NULL;
    int num_add;  // to store number to be added in stack

    while(choice != 5)
    {
    	printf("\nTo Add - 1\nTo Delete - 2\nTo Print - 3\nTo Revese Linked List - 4\nTo Exit - 5\n\nEnter your Choice : ");
    	scanf("%hd",&choice);
		
		if (choice == 1)  //add
		{   
			printf("\n----------------------------\nEnter the number which you wanna add :");
			scanf("%d",&num_add);
			printf("----------------------------\n");

			node* tmp;
			tmp = (node*) malloc(sizeof(node));

			if (!tmp)
			{
				printf("\n----------------------------\nError in allocating memory!\n----------------------------\n");
				return 0;
			}

			tmp->number = num_add;

			if (!head)
			{
				head = tmp;
				head->next = NULL;
			}

			else
			{
				tmp->next = head;
				head = tmp;
			}

		}

		else if (choice == 2)    //Delete
		{
			if (!head)
			{
				printf("----------------------------\nNothing to Delete!\n----------------------------\n");
				continue;
			}
			
			else
			{
				node* tmp = head;
				head = head->next;

				free(tmp);
			}
		}

		else if (choice == 3)  //Print
		{
			if (!head)
			{
				printf("----------------------------\nNothing to print!\n----------------------------\n");
				continue;
			}

			else
			{
				node *tmp = head;
				printf("----------------------------\n");

				while(tmp)
				{
					printf("%d ",tmp->number );
					tmp = tmp->next;
				} 
				
				printf("\n----------------------------");
			}
		}

		else if (choice == 4)  //reverse
		{
			if (!head || !(head->next))
			{
				printf("----------------------------\nNothing to reverse!\n----------------------------\n");
				continue;
			}

			else
			{
				node *tmp = reverseStack(head, head->next);
				head->next = NULL;
				head = tmp;
			}
		}
	}

    //Deleting allocated memory
	if (head)
	{   
		node *tmp;
		
		do
		{
			tmp = head->next;
			free(head);
			head = tmp->next;
		
		} while(head);

	    printf("----------------------------\nAll are deleted!\n----------------------------\n");
    }
}

node * reverseStack(node *pointer_1, node *pointer_2)
{	
	while(1)
	{
		node *tmp1 = pointer_2, *tmp2 = pointer_2->next;

		pointer_2->next = pointer_1;

		if (!tmp2)
		{
			return pointer_2;
		}

		else
		{
			pointer_1 = tmp1;
			pointer_2 = tmp2;
		}
	}
}