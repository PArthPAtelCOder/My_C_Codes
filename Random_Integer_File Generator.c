#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	srand(time(NULL));
	char file[50];
	
	printf("Enter the name of file in which you wanna store integers : ");
	scanf("%[^\n]s",file);
	
	FILE* fp = fopen (file,"wb");

	if( fp == NULL )
	{
		printf("Failed to open file a.bin!\n");
		return 1;
	}

	unsigned int i = ~0;
	i = i >> 6;
	printf("%u",i);
	int tmp;

	while(i--)
	{	tmp = rand();
		fwrite(&tmp,sizeof(int),1,fp);
	}

	fclose(fp);
	return 0;
}
