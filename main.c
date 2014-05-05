#include "generic_vector.h"
#include "dictionary.h"
#include <stdio.h>
#include "mystring.h"
#include "assocarray.h"
void visit(MYSTRING s)
{
	mystring_output(s,stdout);
}
int main()
{
	MY_SET tree = my_set_init_default();
	MYSTRING key = mystring_init_c_string("do-ble");
	MYSTRING data1 = mystring_init_c_string("double");
	MYSTRING data2 = mystring_init_c_string("doable");
	GENERIC_VECTOR listofwords;
	my_set_add(tree,key,data1);
	my_set_add(tree,key,data2);
	my_set_traverse(tree,visit);
	listofwords = my_set_assignment_at(tree,key);
	printf("There are %d words\n",generic_vector_size(listofwords));
	
	return 0;

}
