#include <stdio.h>
#include <stdlib.h>
#include "assocarray.h"
#include "mystring.h"
#include "generic_vector.h"
typedef struct node Node;
typedef struct my_set My_set;
struct node
{
	MYSTRING key; 
	Node* left;
	Node* right;
	int height;
	GENERIC_VECTOR data;
};
struct my_set 
{
	Node* head;
};
/*********************************************
 *Function Declarations 
 *  Used for functions implicity to the .c file and not
 *  necessary for user interface
 *********************************************/
Boolean find(Node* head, MYSTRING item);
Node* insert(Node* pRoot, MYSTRING item, MYSTRING s);
void destroy(Node* root);
void in_order_traverse(Node* head, void (*visit)(MYSTRING));
Node* set_remove(Node* head, MYSTRING item);
int size(Node* head);
void data_in_order_traverse(Node* head, void (*visit)(GENERIC_VECTOR));
int height(Node* head);
int max(int a, int b);
GENERIC_VECTOR* at(Node* head, MYSTRING item);
GENERIC_VECTOR assignment_at(Node* head, MYSTRING item);
Node* right_rotate(Node* head);
Node* left_rotate(Node* head);
void getLargestVector(Node* head, int max,MYSTRING* input);
int maxthree(int a, int b, int c);
Node* findmin(Node* head);
int compare(MYSTRING left, MYSTRING right);
int vectorSize(Node* head);
/***************************************************
 * Returns difference of left and right tree heights
 ***************************************************/
int balance_factor(Node *head);
/*******************************************************
 * Creates a handle to a MY_SET Object
 *
 * @return
 *  If successful will return a handle to a MY_SET object
 *   If Failure will return NULL
 *******************************************************/
MY_SET my_set_init_default(void)
{
	My_set* temp = (My_set*) malloc(sizeof(My_set));
	if(temp != NULL)
	{
		temp->head = NULL;
	}
	return (MY_SET) temp;
}
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
Boolean my_set_is_element(MY_SET hMY_SET, MYSTRING item)
{
	My_set* set = (My_set*) hMY_SET;
	if(set == NULL)
	{
		exit(1);
	}
	return find(set->head,item);
}
Boolean find(Node* head, MYSTRING item)
{
	if(head == NULL)
	{
		return FALSE;
	}
	if(mystring_compare(head->key,item) == 0)
	{
		return TRUE;
	}
	if(mystring_compare(item,head->key) < 0)
	{
		return find(head->left,item);
	}
	else
	{
		return find(head->right,item);
	}
}
Status my_set_add(MY_SET hMY_SET, MYSTRING item, MYSTRING s)
{
	My_set* set = (My_set*) hMY_SET;
	GENERIC_VECTOR* add;
	Boolean exists = my_set_is_element(hMY_SET,item);
	if(set != NULL && exists == TRUE)
	{
		add = my_set_at(hMY_SET,item);
		return generic_vector_push_back(*add,s);
	}
	if(set != NULL && exists == FALSE)
	{
		set->head = insert(set->head,item, s);
		if(set->head != NULL)
		{
			return SUCCESS;
		}
		return FAIL;
	}
	return FAIL;
}
Node* insert(Node* head, MYSTRING key, MYSTRING s)
{
	int balfac;
	Generic_vector_functions ms;
	ms.assignment = string_assignment;
	ms.destructor = string_destructor;
	if (head == NULL)
	{
		Node* temp = (Node*) malloc(sizeof(Node));
		if(temp != NULL)
		{
			temp->key = NULL;
			temp->data = generic_vector_init_default(ms);
			string_assignment((void**)&temp->key,(void*)key);
			generic_vector_push_back(temp->data,s);
			temp->left = NULL;
			temp->right = NULL;
			temp->height = 1;
		}
		return temp;
	}
	if(mystring_compare(key,head->key) < 0)
	{
		head->left  = insert(head->left, key,s);
	}
	else if(mystring_compare(key,head->key) > 0)
	{
		head->right = insert(head->right, key,s);
	}
	head->height = max(height(head->left), height(head->right)) + 1;
	balfac = balance_factor(head);
	if (balfac > 1 && mystring_compare(key,head->key) < 0)
	{
		return right_rotate(head);
	}
	if (balfac < -1 && mystring_compare(key,head->key) > 0)
	{
		return left_rotate(head);
	}
	if (balfac > 1 &&  mystring_compare(key,head->key) > 0)
	{
		head->left =  left_rotate(head->left);
		return right_rotate(head);
	}
	if (balfac < -1 && mystring_compare(key,head->key) < 0)
	{
		head->right = right_rotate(head->right);
		return left_rotate(head);
	}
	return head;
}
void my_set_destroy(MY_SET* p_hMY_SET)
{
	if(p_hMY_SET != NULL)
	{
		My_set* set = (My_set*)*p_hMY_SET;
		if(set != NULL)
		{
			destroy(set->head);
			free(set);
			*p_hMY_SET = NULL;
			return;
		}
	}
	return;
}
void destroy(Node* root)
{
	if(root == NULL)
	{
		return;
	}
	else
	{
		destroy(root->left);
		destroy(root->right);
		generic_vector_destroy(&(root->data));
		mystring_destroy(&(root->key));
		free(root);
	}
}
Status my_set_traverse(MY_SET hMY_SET, void (*visit)(MYSTRING))
{
	My_set* set = (My_set*) hMY_SET;
	if(set != NULL)
	{
		in_order_traverse(set->head, visit);
		return SUCCESS;
	}
	return FAIL;
}
void in_order_traverse(Node* head, void (*visit)(MYSTRING))
{
	if(head == NULL)
	{
		return;
	}
	else
	{	
		in_order_traverse(head->left, visit);
		visit(head->key);
		in_order_traverse(head->right, visit);
		return;
	}
}
Boolean my_set_is_empty(MY_SET hMY_SET)
{
	My_set* set = (My_set*) hMY_SET;
	if(set == NULL)
	{
		exit(1);
	}
	if(set->head == NULL)
	{
		return TRUE;
	}
	return FALSE;
}
Status my_set_remove(MY_SET hMY_SET, MYSTRING item)
{
	My_set* set = (My_set*) hMY_SET;
	if(set == NULL || my_set_is_element(hMY_SET,item) == FALSE )
	{
		return FAIL;
	}	
	set->head = set_remove(set->head,item);
	return SUCCESS;
}
Node* set_remove(Node* head, MYSTRING item)
{
	int balfac;
	Node* temp;
	if(head == NULL)
	{
		return head;
	}
	if(mystring_compare(item,head->key) < 0)
	{
		head->left = set_remove(head->left,item);
	}
	else if(mystring_compare(item,head->key) > 0)
	{
		head->right = set_remove(head->right,item);
	}
	else
	{
		if(head->left == NULL || head->right == NULL)
		{
			if( head->left != NULL)
			{
				temp = head->left;
			}
			else
			{
				temp = head->right;
			}
			if(temp == NULL)
			{
				temp = head;
				head = NULL;
			}
			else
			{
				*head = *temp;
			}
			free(temp);
			generic_vector_destroy(&(temp->data));
			mystring_destroy(&(temp->key));
		}
		else
		{
			temp = findmin(head->right);
			head->key = temp->key;
			head->data = temp->data;
			head->right = set_remove(head->right, temp->key);
		}
	}
	if(head == NULL)
	{ 
		return head;
	}
	head->height = max(height(head->left), height(head->right)) + 1;
	balfac = balance_factor(head);
	if(balfac > 1 && balance_factor(head->left) >= 0) 
	{
		return right_rotate(head);
	}
	if(balfac > 1 && balance_factor(head->left) < 0)
	{
		head->left =  left_rotate(head->left);
		return right_rotate(head);
	}
	if(balfac < -1 && balance_factor(head->right) <= 0)
	{
		return left_rotate(head);
	}
	if(balfac < -1 && balance_factor(head->right) > 0)
	{
		head->right = right_rotate(head->right);
		return left_rotate(head);
	}
	return head;
}
int my_set_size(MY_SET hMY_SET)
{
	My_set* set = (My_set*) hMY_SET;
	if(set == NULL)
	{
		return -1;
	}
	return size(set->head);
}
int size(Node* head)
{
	if(head == NULL)
	{
		return 0;
	}
	return 1 + size(head->left) + size(head->right);
}
int my_set_height(MY_SET hMY_SET)
{
	My_set* set = (My_set*) hMY_SET;
	if(set == NULL)
	{
		return -1;
	}
	return height(set->head);
}
int height(Node* head)
{
	if(head == NULL)
	{
		return 0;
	}
	return head->height;
}
int max(int a, int b)
{
	if(a > b )
	{
		return a;
	}
	return b;
}
int maxthree(int a, int b, int c)
{
	int max = a;
	if(b > max)
	{
		max = b;
	}
	if(c > max)
	{
		max = c;
	}
	return max;
}
int balance_factor(Node *head)
{
	return (height(head->left) - height(head->right));
}
Node* left_rotate(Node *head)
{
	Node *temp = head;
	if(temp == NULL)
	{
		return NULL;
	}
	else if(temp->right == NULL)
	{
		return NULL;
	}
	else
	{
		temp = head->right;
		head->right = temp->left;
		temp->left = head;
		head->height = max(height(head->left),height(head->right)) + 1;
		temp->height = max(height(temp->left),height(temp->right)) + 1;
	}
	return temp;
}
Node* right_rotate(Node *head)
{
	Node *temp = head;
	if(temp == NULL)
	{
		return NULL;
	}
	else if(temp->left == NULL)
	{
		return NULL;
	}
	else
	{
		temp = head->left;
		head->left = temp->right;
		temp->right = head;
		head->height = max(height(head->left),height(head->right)) + 1;
		temp->height = max(height(temp->left),height(temp->right)) + 1;
	}
	return temp;
}
Node* findmin(Node* head)
{
	Node* temp = head;
	while(temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}
GENERIC_VECTOR* my_set_at(MY_SET hMY_SET, MYSTRING item)
{
	My_set* set = (My_set*) hMY_SET;
	if(set != NULL)
	{
		return at(set->head,item);
	}
	return NULL;
}
GENERIC_VECTOR* at(Node* head, MYSTRING item)
{
	if(head != NULL)
	{
		if(mystring_compare(head->key,item) == 0)
		{
			return &head->data;
		}
		else if(mystring_compare(item,head->key) < 0)
		{
			return at(head->left,item);
		}
		else 
		{
			return at(head->right,item);
		}
	} 
	return NULL;
}
GENERIC_VECTOR my_set_assignment_at(MY_SET hMY_SET, MYSTRING item)
{			
	My_set* set = (My_set*) hMY_SET;
	if(set != NULL)
	{
		return assignment_at(set->head,item);
	}
	return NULL;
}
GENERIC_VECTOR assignment_at(Node* head, MYSTRING item)
{
	GENERIC_VECTOR ret = NULL;
	if(head != NULL)
	{
		if(mystring_compare(item,head->key) == 0)
		{
			vector_assignment((void**)&ret,(void*) head->data);
			return ret;
		}
		else if(mystring_compare(item, head->key) < 0)
		{
			return assignment_at(head->left,item);
		}
		else 
		{
			return assignment_at(head->right,item);
		}
	} 
	generic_vector_destroy(&ret);
	return NULL;
}
int my_set_vector_size(MY_SET hMY_SET)
{
	My_set* set = (My_set*) hMY_SET;
	if(set != NULL)
	{
		return vectorSize(set->head);
	}
	return -1;
}
int vectorSize(Node* head)
{
	int left,right,current;
	if(head == NULL)
	{
		return 0;
	}
	left = vectorSize(head->left);
	current = generic_vector_size(head->data);
	right = vectorSize(head->right);
	return maxthree(left,right,current);
}
void my_set_largest_vector(MY_SET hMY_SET,MYSTRING* input)
{
	My_set* set = (My_set*) hMY_SET;
	int max;
	if(set != NULL)
	{
		max = vectorSize(set->head);
		getLargestVector(set->head, max,input);
	}
}
void getLargestVector(Node* head, int max,MYSTRING* input)
{
	MYSTRING ret = NULL;
	if(head == NULL)
	{
		return;
	}
	getLargestVector(head->left,max,input);
	if(generic_vector_size(head->data) == max)
	{
		string_assignment((void**)&ret,(void*) head->key);
		*input = ret;
	}  
	getLargestVector(head->right,max,input);
}
