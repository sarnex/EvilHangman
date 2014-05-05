#include "assocarray.h"
#include "generic_vector.h"
#include "mystring.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int acceptChars(char ch, int* pbDiscardChar)
{

	if(isalpha(ch) || ch == '-')
	{
		*pbDiscardChar = 0;
		return 0;
	}
	*pbDiscardChar = 1;
	return 1;
}
void visit(MYSTRING s)
{
	mystring_output(s,stdout);
}
int main(int argc, char* argv[])
{
	int input;
	MYSTRING in = NULL;
	MYSTRING* t2 = NULL;
	MYSTRING word = NULL;
	int i;
	GENERIC_VECTOR* temp = NULL;
	MY_SET set = my_set_init_default();
	if(set == NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}
	do
	{
		printf("What do you want to do?\n");
		printf("1. Add a key to the tree with a key and a word inside the generic_vector, and then view the size of the tree\n");
		printf("2. Add a word to a key that exists, then view the size of the tree and the size of the vector(Run option 1 before doing this)\n");
		printf("3. Check the height of the AVL tree\n");
		printf("4. Print out all keys\n");
		printf("5. Print out the words in a key that exists(Make sure you added the key and data already)\n");
		printf("0. Exit\n");
		printf("\n");
		fscanf(stdin,"%d",&input);
		switch(input)
		{
			case 1:
				in = mystring_init_c_string("                             ");
				word = mystring_init_c_string("                             ");
				if(in == NULL || word == NULL)
				{
					mystring_destroy(&in);
					mystring_destroy(&word);
					my_set_destroy(&set);
					printf("Out of memory\n");
					exit(1);
				}
				printf("Enter the key, must be less than 29 characters\n");
				mystring_input(in,stdin,1,acceptChars);
				printf("Enter the word to add, must be less than 29 characters, there is no validation checking that the word should be under this key\n");
				mystring_input(word,stdin,1,acceptChars);
				my_set_add(set,in,word);
				mystring_destroy(&word);
				mystring_destroy(&in);
				printf("Size of the tree is %d\n",my_set_size(set));
				break;
			case 2:
				in = mystring_init_c_string("                             ");
				word = mystring_init_c_string("                             ");
				if(in == NULL || word == NULL)
				{
					mystring_destroy(&in);
					mystring_destroy(&word);
					my_set_destroy(&set);
					printf("Out of memory\n");
					exit(1);
				}
				printf("Enter the key, must be less than 29 characters\n");
				mystring_input(in,stdin,1,acceptChars);
				printf("Enter the word to add, must be less than 29 characters, there is no validation checking that the word should be under this key\n");
				mystring_input(word,stdin,1,acceptChars);
				my_set_add(set,in,word);
				mystring_destroy(&word);
				mystring_destroy(&in);
				printf("Size of the tree is %d\n",my_set_size(set));
				printf("Size of the vector is %d\n",my_set_vector_size(set));
				break;
			case 3:
				printf("The height of the AVL tree is %d\n",my_set_height(set));
				break;
			case 4:
				my_set_traverse(set,(void*) visit);
				break;
			case 5:
				in = mystring_init_c_string("                             ");
				if(in == NULL)
				{
					my_set_destroy(&set);
					printf("Out of memory\n");
					exit(1);
				}
				printf("Enter the key, must be less than 29 characters\n");
				mystring_input(in,stdin,1,acceptChars);
				printf("Words in the vector:\n");
				temp = (GENERIC_VECTOR*) my_set_at(set,in);
				if(temp != NULL)
				{
					for(i = 0; i < generic_vector_size(*temp); i++)
					{
						t2 = (MYSTRING*) generic_vector_at(*temp,i);
						if(t2 != NULL)
						{
							mystring_output(*t2,stdout);
						}
					}		
				}
				mystring_destroy(&in);
				break;
				printf("\n\n");
		}
	}
	while(input != 0);
	my_set_destroy(&set);
	return 0;
}
