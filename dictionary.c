#include "mystring.h"
#include "generic_vector.h"
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
int acceptChars(char ch, int* pbDiscardChar)
{
	if(isalpha(ch))
	{
		*pbDiscardChar = 0;
		return 0;
	}
	*pbDiscardChar = 1;
	return 1;
}
GENERIC_VECTOR generateVector(void)
{
	int i = 0;
	FILE* list = fopen("dictionary.txt","r");
	Generic_vector_functions functions;
	MYSTRING a;
	GENERIC_VECTOR c;
	GENERIC_VECTOR* b;
	functions.assignment = vector_assignment;
	functions.destructor = vector_destructor;
	Generic_vector_functions functions2;
	functions2.assignment = string_assignment;
	functions2.destructor = string_destructor;
	GENERIC_VECTOR vector = generic_vector_init_default(functions);
	if(list == NULL)
	{
		fprintf(stderr,"Failed opening dictionary.txt\n");
		generic_vector_destroy(&vector);
		exit(1);
	}
	for(i = 0; i < 29; i++)
	{
		c = generic_vector_init_default(functions2);
		generic_vector_push_back(vector,c);
		generic_vector_destroy(&c);
	}
	while(!feof(list))
	{
		a = mystring_init_c_string("                             ");
		mystring_input(a,list,1,acceptChars);
		if(a != NULL && mystring_size(a) > 0)
		{	
			b = (GENERIC_VECTOR*) generic_vector_at(vector,mystring_size(a) - 1);
			if(b != NULL)
			{	
				generic_vector_push_back(*b,a);
			}
		}
		mystring_destroy(&a);
	}
	fclose(list);
	return vector;
}
