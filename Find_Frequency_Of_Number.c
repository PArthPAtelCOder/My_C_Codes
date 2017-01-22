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

	int num, tmp;
	long frequency = 0;

	printf("Enter the number whose frequency you wanna find : ");
	scanf("%d",&num);
	
	fscanf(fp, "%d", &tmp );

	do
	{
		if( tmp == num )
			frequency++ ;

		fscanf( fp, "%d", &tmp );
	} while ( !feof(fp) ) ;

	printf("\nFrequency of num %d is %ld \n", num, frequency );
	fclose(fp);
	return 0;
}
