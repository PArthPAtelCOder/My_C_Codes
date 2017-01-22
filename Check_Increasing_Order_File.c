#include<stdio.h>

int main(void)
{
	char fileName[50];
	
	printf("Enter the name of file : ");
	scanf("%[^\n]s",fileName);
	
	FILE* fp = fopen ( fileName, "r");

	if( fp == NULL )
	{
		printf("Error occured while opening file!\n");
		return 1;
	}

	int tmp, i1, i2;

	fscanf(fp, "%d", &i1 );
	fscanf(fp, "%d", &i2 );

	short flag = 1; //1 means sorted in increasing order

	do
	{
		if( i2 < i1 )
		{
			flag = 0;
			break;
		}

		i1 = i2;

		fscanf( fp, "%d", &i2 );
	} while ( !feof(fp) ) ;

	if ( flag == 1 )
		printf("\n\nFile is sorted In increasing order!\n\n");
	else
		printf("\nFile is not sorted in increasing order!\n");
	fclose(fp);
	return 0;
}
