#include "dictionary.h"
#include <stdio.h>
#include "mystring.h"
#include "generic_vector.h"
int main(int argc, char* argv[])
{
	GENERIC_VECTOR vector = generateVector();
	int letters;
	int input;
	int i;
	GENERIC_VECTOR* temp = NULL;
	MYSTRING* ms = NULL;
	do
	{
		printf("What do you want to do?\n");
		printf("1. See the number of inner vectors of mystrings\n");
		printf("2. See the number of mystrings in a vector of a specific length\n");
		printf("3. List all of the mystrings in a vector of a specific length\n");
		printf("0. Exit\n");
		fscanf(stdin,"%d",&input);
		switch(input)
		{
			case 1: 
				printf("Size of outer vector: %d\n",generic_vector_size(vector));
				break;
			case 2: 
				printf("How many letters should the words have?\n");
				fscanf(stdin,"%d",&letters);
				temp = (GENERIC_VECTOR*) generic_vector_at(vector,letters-1);
				if(temp == NULL || generic_vector_size(*temp) == 0)
				{
					printf("There are no words of this size.\n");
				}
				else
				{
					printf("Size of inner vector: %d\n",generic_vector_size(*temp));
				}
				break;
			case 3:
				printf("How many letters should the words have?\n");
				fscanf(stdin,"%d",&letters);
				temp = (GENERIC_VECTOR*) generic_vector_at(vector,letters-1);
				if(temp == NULL || generic_vector_size(*temp) == 0)
				{
					printf("There are no words of this size.\n");
					break;
				}
				for(i = 0; i < generic_vector_size(*temp); i++)
				{
					ms = (MYSTRING*) generic_vector_at(*temp,i);
					if(ms != NULL)
					{
						mystring_output(*ms,stdout);
					}
				}
				break;
		}
		printf("\n\n");
	}
	while(input != 0);
	generic_vector_destroy(&vector);
}
