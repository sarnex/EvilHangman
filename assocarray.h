#ifndef ASSOCARRAY_H
#define ASSOCARRAY_H	

#include "status.h"
#include "generic_vector.h"
#include "mystring.h"
enum boolean 
{
	FALSE, TRUE
};

typedef enum boolean Boolean;
typedef struct _MY_SET *MY_SET;
//typedef struct _MYSTRING *MYSTRING;


/*******************************************************
 * Creates a handle to a MY_SET Object
 *
 * @return
 *  If successful will return a handle to a MY_SET object
*   If Failure will return NULL
 *******************************************************/
MY_SET my_set_init_default();

/*******************************************************
* Takes a handle to and determines if a given item
* exists in a set or not
*
* @param hMY_SET
*      Handle to a set object
*
* @param item
*      Item to be determined it exists in the set or not
*
* @return
*      Returns TRUE if item is in the set. Exits on error
*
********************************************************/
Boolean my_set_is_element(MY_SET hMY_SET, MYSTRING item); //returns TRUE if item is in the set; exit on error


Boolean my_set_is_empty(MY_SET hMY_SET); //returns TRUE if the set is empty; exit on error


int my_set_size(MY_SET hMY_SET); //returns the number of elements in the set; -1 on error


Status my_set_traverse(MY_SET hMY_SET, void (*visit)(MYSTRING)); // call visit on each node in the set. (Use an inorder traversal of your AVL tree)


Status my_set_add(MY_SET hMY_SET, MYSTRING item, MYSTRING s); //adds item to the set if it is not already in it.


Status my_set_remove(MY_SET hMY_SET, MYSTRING item);//find and remove item from the set if it is present otherwise ignore.


void my_set_destroy(MY_SET* p_hMY_SET);//destroy the data structure and set the handle pointed to by the argument to NULL.

int my_set_height(MY_SET hMY_SET);
GENERIC_VECTOR my_set_assignment_at(MY_SET hMY_SET, MYSTRING item);
GENERIC_VECTOR* my_set_at(MY_SET hMY_SET, MYSTRING item);
int my_set_vector_size(MY_SET hMY_SET);
void my_set_largest_vector(MY_SET hMY_SET,MYSTRING* input);

#endif
