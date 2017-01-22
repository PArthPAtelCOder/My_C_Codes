/* Name        : MergeSort_File_Version.c
   Author      : Patel Parth Pragneshkumar
   Roll No     : 111501019 */
#include <stdio.h>
#include <limits.h>

void copyFile ( FILE*, FILE* );
void makeReadable ( FILE* , FILE* , int );

int main(void)
{
	FILE* inputFile = fopen( "input.bin","rb"); //input file
	FILE* readFile = fopen( "input_copy.bin","wb+"); //initially data will be read from this file
	FILE* writeFile = fopen ( "tmp.bin","wb+"); //initially data will be written into this file

	if ( readFile == NULL || writeFile == NULL || inputFile == NULL )
	{
		printf("Error while opening file!\n");
		return 1;
	}

	copyFile ( inputFile, readFile ); //copy from inputFile to readFile
	fclose ( inputFile );

	fseek(readFile,0,SEEK_END);
	//number of integers in input file
	int nInt = ftell( readFile ) / 4;
	rewind(readFile) ;
	//we are taking two blocks and merging them
	//ptr1 points to current reading location of block 1 in file
	//if ptr1 = x means it is pointing to (X+1)th integer in file
	int ptr1 = 0 ;
	int ptr2 ; //pointer for block 2
	int difference = 1; //size of one block, intitially block size is 1 after that 2 then 4,8,16,.....
	int end_ptr1 = 0 ; //points to the end of block1
	int end_ptr2 ; //points to the end of block 2
	FILE* tmp; //used to swap file pointers
	int i1, i2; //will be used to store integers read from file
	short flag ; //if flag is 1, integer will be read from 1st block
	// for value 2, integer will be read from block 2 ;for flag = 0 , will read from both file
	int i; // 2* difference
	do
	{	//in this loop already sorted blocks of size "difference" will be merged
		ptr1 = 0; //points to first integer on starting everytime
		ptr2 = difference ;
		end_ptr1 = difference ;
		end_ptr2 = 2 * difference ;

		while ( ptr1 < nInt ) //if there is something to sort
		{	//in this loop two blocks of size "difference" will be merged
			i = 2*difference;
			flag = 0; //bcoz initially we have to read numbers from both blocks

			while ( i-- ) //until i numbers are not sorted
			{
				if ( ptr1 == end_ptr1 && ( ptr2 >= nInt || ptr2 == end_ptr2) ) //if reading of two blocks is completed
					break;
				else if ( end_ptr1 >= nInt ) //if there is only first block copy all integers as it is
				{
					do
					{
						fseek(readFile, ptr1* sizeof(int), SEEK_SET );
						fread( &i1,sizeof(int),1, readFile );
						fwrite(&i1, sizeof(int), 1 , writeFile );
						ptr1++ ;
					} while ( ptr1 < nInt ) ;
					break;
				}

				if ( flag == 1 || flag == 0 ) //reading int from block 1
				{
					fseek(readFile, ptr1* sizeof(int), SEEK_SET );
					fread( &i1,sizeof(int),1, readFile );
				}

				if( flag == 2 || flag == 0 ) //reading int from block 2
				{
					fseek(readFile, ptr2* sizeof(int), SEEK_SET );
					fread( &i2,sizeof(int),1, readFile );
				}

				if ( i1 <= i2 )
				{
					fwrite(&i1, sizeof(int), 1 , writeFile );
					ptr1++ ;

					if( ptr1 == end_ptr1 )
					{
						i1 = INT_MAX ;// i1 is infinity
						flag = 2; //next time int will be read from block 2
					}
					else
						flag = 1; //next time int will be read from block 1
				}

				else
				{
					fwrite( &i2, sizeof(int), 1, writeFile );
					ptr2++ ;

					if( ptr2 == end_ptr2 || ptr2 == nInt )
					{
						i2 = INT_MAX ;// i2 is infinity
						flag = 1; //next time int will be read from block 1
					}
					else
						flag = 2; //next time int will be read from block 2
				}
			}

			ptr1 += difference;
			ptr2 += difference;
			end_ptr1 += 2 * difference;
			end_ptr2 += 2 * difference;
		}
		rewind ( readFile ); rewind ( writeFile );
		//exchanging file pointers because after one loop we will take input from
		//the file that was used used for writing
		//and will write in the file from which we read in this loop
		tmp = readFile ; readFile = writeFile ; writeFile = tmp ;

		difference = 2 * difference ;
	} while ( difference < nInt ) ;

	FILE* outputTXT = fopen ( "output.txt","w"); //file in which readable sorted integers will be stored

	if ( tmp == NULL )
	{
		printf("Error while creating file!");
		fclose( readFile ); fclose ( writeFile );
		return 1;
	}
	//storing sorted integers into human readable form in output.txt
	makeReadable ( readFile, outputTXT , nInt);

	fclose ( readFile );
	fclose ( writeFile );
	fclose ( outputTXT );

	return 0;
}
//to make a copy of file
void copyFile ( FILE* from, FILE* to)
{
	int c;

	while ( (c = fgetc(from)) != EOF )
		fputc(c, to);
}
//convert binary integer files into human readable integer file
void makeReadable ( FILE* from, FILE* to, int n)
{
	int tmp;

	while( n-- )
	{
		fread (&tmp, sizeof(int), 1, from );
		fprintf( to, "%d\n", tmp );
	}
}
