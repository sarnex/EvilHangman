#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include <ctype.h>
#include <string.h>
struct mystring
{
	int size;
	int capacity;
	char* data;
};
typedef struct mystring Mystring;
void my_swap(char* a, char* b);
MYSTRING mystring_init_default(void)
{
	Mystring* temp = (Mystring*) malloc(sizeof(Mystring));
	if(temp != NULL)
	{
		temp->size = 0;
		temp->capacity = MYSTRING_STARTING_CAPACITY;
		temp->data = (char*) malloc(sizeof(char) * MYSTRING_STARTING_CAPACITY);
		if(temp->data == NULL)
		{
			free(temp);
			temp = NULL;
		}
	}
	return (MYSTRING) temp;
}
MYSTRING mystring_init_c_string(const char * const c_string)
{
	int i;
	int size = 0;
	Mystring* def = (Mystring*) malloc(sizeof(Mystring));
	if(def != NULL && c_string != NULL)
	{
		for(i = 0; c_string[i] != '\0'; i++)
		{
			size++;
		}
		def->data = (char*) malloc(sizeof(char) * size);
		if(def->data == NULL)
		{
			free(def);
			return NULL;
		}
		for(i = 0; i < size; i++)
		{
			if(c_string[i] != '\0')
			{
				def->data[i] = c_string[i];
			}
		}
		def->size = size;
		def->capacity = size;
	}
	return (MYSTRING) def;
}
int mystring_size(MYSTRING hString)
{
	Mystring* string = (Mystring*) hString;
	if(string == NULL)
	{
		return -1;
	}
	return string->size ;
}
int mystring_capacity(MYSTRING hString)
{
	Mystring* string = (Mystring*) hString;
	if(string == NULL)
	{
		return -1;
	}
	return string->capacity;
}
MyString_Status mystring_output(MYSTRING hString, FILE* out)
{
	Mystring* string = (Mystring*) hString;
	int i;
	if(string == NULL || out == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	for(i = 0; i < string->size;i++)
	{
		fprintf(out,"%c",string->data[i]);
	}
	fprintf(out,"\n");
	return MYSTRING_STATUS_SUCCESS;
}
MyString_Status mystring_concatenate_c_string(MYSTRING hString, char * c_string)
{
	Mystring* string = (Mystring*) hString;
	int i ;
	int size = 0;
	char* data;
	if(string == NULL || c_string == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	for(i = 0; c_string[i] != '\0';i++)
	{
		size++;
	}
	if(string->capacity >= string->size + size)
	{
		for(i = string->size ; i < string->size + size; i++)
		{ 
			string->data[i] = c_string[i - string->size ];
		}
		string->size += size;
	}
	else
	{
		data = (char*) malloc(sizeof(char) * (string->size + size) );
		if(data == NULL)
		{
			return MYSTRING_STATUS_ERROR;
		}
		for(i = 0; i < string->size; i++)
		{
			data[i] = string->data[i];
		}
		for(i = string->size ; i < string->size + size; i++)
		{
			data[i] = c_string[i - string->size];
		}
		free(string->data);
		string->data = data;
		string->size += size;
		string->capacity = string->size;
	}
	return MYSTRING_STATUS_SUCCESS;
}
MyString_Status mystring_concatenate_mystring(MYSTRING hStringDest,
		MYSTRING hStringSource)
{
	Mystring* dest = (Mystring*) hStringDest;
	Mystring* source = (Mystring*) hStringSource;
	int i;
	if(dest == NULL || source == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	} 
	if(dest->capacity >= source->size + dest->size)
	{
		for(i = dest->size; i < dest->size + source->size;i++)
		{
			dest->data[i] = source->data[i-dest->size];
		}
		dest->size +=source->size;
	}
	else
	{
		char* new = (char*) malloc(sizeof(char) * dest->size + source->size);
		if(new == NULL)
		{	
			return MYSTRING_STATUS_ERROR;
		}
		for(i = 0; i < dest->size ; i++)
		{
			new[i] = dest->data[i];
		}
		for(i = dest->size; i < (dest->size + source->size); i++)
		{
			new[i] = source->data[i-dest->size];
		}
		free(dest->data);
		dest->data = new;
		dest->size += source->size;
		dest->capacity = dest->size;
	}
	return  MYSTRING_STATUS_SUCCESS;
}
MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen)
{
	Mystring* string = (Mystring*) hString;
	if(string == NULL || newMaxLen > string->size || newMaxLen < 0)
	{
		return MYSTRING_STATUS_ERROR;
	}
	string->size = newMaxLen;
	return MYSTRING_STATUS_SUCCESS;
}
void mystring_destroy(MYSTRING* p_hString)
{
	if(p_hString != NULL)
	{
		Mystring* string = (Mystring*) *p_hString;
		if(string != NULL)
		{
			//printf("Address of data, %d\n",string->data);
			if(string->data != NULL)
			{
				free(string->data);
			}			
			free(string);
		}
		*p_hString = NULL;
	}
}
MyString_Status mystring_push(MYSTRING hString, char ch)
{
	Mystring* string = (Mystring*) hString;
	if(string == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	char* new;
	int i;
	int newsize = string->size + 1;
	if(newsize <= string->capacity)
	{
		string->data[string->size] = ch;
		string->size++;
	}
	else
	{
		new = (char*) malloc(sizeof(char) * newsize);
		if(new == NULL)
		{
			return MYSTRING_STATUS_ERROR;
		}
		for(i = 0; i < string->size;i++)
		{
			new[i] = string->data[i];
		}
		new[string->size] = ch;
		free(string->data);
		string->data = new;
		string->size++;
		string->capacity = string->size;
	}
	return MYSTRING_STATUS_SUCCESS;
}
char mystring_pop(MYSTRING hString)
{
	Mystring* string = (Mystring*) hString;
	int size = string->size;
	char c;
	if(size > 0 && string != NULL)
	{
		c = string->data[string->size-1];
		string->size--;
		return c;
	}
	return '\0';
}
char mystring_peek(MYSTRING hString)
{
	Mystring* string = (Mystring*) hString;
	if(string->size > 0 && string != NULL)
	{
		return string->data[string->size - 1];
	}
	return '\0';
}
char mystring_get(MYSTRING hString, int index)
{
	Mystring* string = (Mystring*) hString;
	if(string != NULL && index + 1 <= string->size && index >= 0)
	{
		return string->data[index];
	}
	return '\0';
}
MyString_Status mystring_put(MYSTRING hString, int index, char ch)
{
	Mystring* string = (Mystring*) hString;
	if(string != NULL && index + 1 <= string->size && index >= 0)
	{
		string->data[index] = ch;
		return MYSTRING_STATUS_SUCCESS;
	}
	return MYSTRING_STATUS_ERROR;
}
MYSTRING mystring_init_substring(MYSTRING hStringSource, int index, int length)
{
	Mystring* string = (Mystring*) hStringSource;
	int i;
	char* new;
	MYSTRING ms;
	if(hStringSource == NULL || index < 0 || length <= 0 || length > string->size || index > string->size - 1)
	{
		return NULL;
	}
	new = (char*) malloc((sizeof(char) * length) + 1);
	if(new  == NULL)
	{
		return NULL;
	}
	for(i = index; i < length + index;i++)
	{
		new[i - index] = string->data[i];
	}	
	new[length] = '\0';
	ms = mystring_init_c_string(new);
	free(new);
	return ms;
}
char * mystring_to_c_string(MYSTRING hString, char c_string_arr[], int arrSize)
{	Mystring* string = (Mystring*) hString;
	int i;
	if(string == NULL || c_string_arr == NULL || arrSize < 1)
	{
		return NULL;
	}	
	for(i = 0; i < string->size && i < arrSize - 1; i++)
	{	
		c_string_arr[i] = string->data[i];	
	}
	c_string_arr[i] = '\0';
	return c_string_arr;
}
MyString_Status mystring_input(MYSTRING hString, FILE* hFile,int bIgnoreLeadingWhiteSpace, int (* fTerminate)(char ch, int * pbDiscardChar))
{
	Mystring* string = (Mystring*) hString;
	char c;	
	int discard = 0;
	int realchar = 0;
	if(hFile == NULL || string == NULL || fTerminate == NULL)
	{
		return MYSTRING_STATUS_ERROR;
	}
	string->size = 0;
	while(fscanf(hFile,"%c",&c) != EOF)
	{
		if(bIgnoreLeadingWhiteSpace)
		{
			if(!realchar && !isspace(c) && !isblank(c))
			{
				realchar = 1;
			}
			if(realchar)
			{
				if(fTerminate(c,&discard))
				{
					break;
				}
				if(discard == 0)
				{
					mystring_push(hString,c);
				}
			}
		}
		else
		{
			if(fTerminate(c,&discard))
			{
				break;
			}
			if(discard == 0)
			{
				mystring_push(hString,c);
			}
		}
	}
	return MYSTRING_STATUS_SUCCESS;
}
void string_destructor(void** object)
{
	mystring_destroy((MYSTRING*)object);
}
void string_assignment(void** left, void* right)
{
	char* temp;
	int i; 
	Mystring* real_left = (Mystring*) *left;
	Mystring* real_right = (Mystring*) right;
	if(real_left == NULL)
	{
		*left = real_left = (Mystring*) mystring_init_default();
	}
	if(real_left != NULL && real_right != NULL)
	{
		//both objects "supposedly" exist so try to do a deep copy
		//if the left side is not big enough to store the right's data then 
		//make it bigger.
		if(real_left->capacity < real_right->size)
		{
			real_left->capacity = real_right->size;
			temp = (char*)malloc(sizeof(char)*real_left->capacity);
			if(temp == NULL)
			{
				fprintf(stderr, "I ran out of memory and I give up...\n");
				exit(1);
			}
			free(real_left->data);
			real_left->data = temp;
		}
		//fix left's size to match right's
		real_left->size = real_right->size;
		//copy over all the data
		for(i=0; i<real_right->size; i++)
		{
			real_left->data[i] = real_right->data[i];
		}
	}
	else
	{
		//if right is NULL we can't really do the right thing so let's just crash for now
		fprintf(stderr, "Tried to do string_assignment but the right hand side was NULL\n");
		exit(1);
	}
}
int mystring_contains(MYSTRING hString, char c, int index)
{
	Mystring* string = (Mystring*) hString;
	if(string != NULL)
	{
		if(tolower(string->data[index]) == tolower(c))
		{
			return 1;
		}
	}
	return 0;
}
int mystring_contains_at_all(MYSTRING hString, char c)
{
	int i;
	Mystring* string = (Mystring*) hString;
	if(string != NULL)
	{
		for(i = 0; i < mystring_size(hString); i++)
		{
			if(tolower(string->data[i]) == tolower(c))
			{
				return 1;
			}
		}
	}
	return 0;
}
void mystring_sort(MYSTRING hString)
{
	int i,j;
	int min;
	Mystring* string = (Mystring*) hString;
	for(i = 0; i < string->size - 1; i++)
	{
		min = i;//selection sort
		for(j = i + 1; j < string->size; j++ )
		{
			if(string->data[j] < string->data[min])
			{
				min = j;
			}
		}
		if(min != i)
		{
			my_swap(&string->data[i],&string->data[min]);
		}
	}
	return;
}
void my_swap(char* a, char* b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}
int mystring_compare(MYSTRING left, MYSTRING right)
{
	int i;
	Mystring* real_left = (Mystring*) left;
	Mystring* real_right = (Mystring*) right;
	if(left == NULL && right != NULL)
	{
		return 1;
	}
	if(left != NULL && right == NULL)
	{
		return -1;
	}
	if(left == NULL && right == NULL)
	{
		return 0;
	}
	if(real_left->size == real_right->size)
	{
		for(i = 0; i < real_left->size; i++)
		{
			if(real_left->data[i] != real_right->data[i])
			{
				//return real_left->data[i] - real_right->data[i];
				return real_right->data[i] - real_left->data[i];
			}
		}
		return 0;
	}
	else if(real_left->size > real_right->size)
	{
		for(i = 0; i < real_right->size; i++)
		{
			if(real_left->data[i] != real_right->data[i])
			{
				return real_right->data[i] - real_left->data[i];
			}
		}
		return 1;
	}
	else if(real_left->size < real_right->size)
	{
		for(i = 0; i < real_left->size; i++)
		{
			if(real_left->data[i] != real_right->data[i])
			{
				return real_right->data[i] - real_left->data[i];
			}
		}
		return -1;
	}
	return 0;
}
