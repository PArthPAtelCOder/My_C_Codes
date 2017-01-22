#include<stdio.h>

int main(void)
{	
	char file[50];
	printf("Enter the name of file : ");
	scanf("%[^\n]s",file);

	FILE* fp = fopen (file,"rb");

	if( fp == NULL )
	{
		printf("Failed to open file %s!\n", file);
		return 1;
	}

	fseek(fp,0,SEEK_END);
	int n = ftell(fp);
	n = n/4;
	rewind(fp);
	int tmp;

	while(n--)
	{	
		fread(&tmp,sizeof(int),1,fp);
		printf("%d\n",tmp);
	}

	fclose(fp);
	return 0;
}
