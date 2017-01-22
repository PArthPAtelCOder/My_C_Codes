#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand(time(NULL));
	char fileName[50];

	printf("Enter the File name in which you wanna store random combination of n numbers starting from 1 to n : \n");
	scanf("%[^\n]s",fileName);

	printf("\n\nEnter n : \n");
	long unsigned n;
	scanf("%d",&n);

	unsigned long int* array = (unsigned long int*) malloc(sizeof(unsigned long int)*n);

	for(unsigned long int i=0; i < n ; i++ )
		array[i] = i+1;

	printf("\n\nLevel of randomisation : \nLow : 1\nMedium : 2\nHigh : 3\n------> ");
	
	unsigned long int level;
	scanf("%lu",&level);
	level *= n;
	unsigned long int tmp;
	unsigned long int j,k;
	
	while(level--)
	{
		j = (((unsigned long int)rand())*((unsigned long int)rand())) % n ;
		k = (((unsigned long int)rand())*((unsigned long int)rand())) % n ;
		tmp = array[j];
		array[j] = array[k];
		array[k] = tmp;
	}

	FILE* fp = fopen(fileName, "w");

	fprintf(fp,"%lu\n",n);
	j=0;

	while(n--)
	{
		fprintf(fp,"%lu\n",array[j]);
		j++;
	}

	fclose(fp);
	free(array);

	return 0;
}
