#include"main.h"

/**
 * append_rvar_element - Appends a new node to a r_var linked list.
 * @list_head: Pointer to the head of the list.
 * @var_length: Length of the variable.
 * @val: Value of the variable.
 * @value_length: Length of the value.
 *
 * Return: Pointer to the head of the list.
 */
r_var *append_rvar_element(r_var **list_head,
		int var_length, char *val, int value_length)
{
	r_var *new_node, *temp_node;

	/* Allocating memory for the new node */
	new_node = malloc(sizeof(r_var));
	if (new_node == NULL)
		return (NULL);

	/* Initializing the new node */
	new_node->len_var = var_length;
	new_node->val = val;
	new_node->len_val = value_length;
	new_node->next = NULL;

	/* If the list is empty, make the new node as the head */
	temp_node = *list_head;
	if (temp_node == NULL)
	{
		*list_head = new_node;
	}
	else
	{
		/* Traverse to the end of the list */
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		/* Append the new node at the end of the list */
		temp_node->next = new_node;
	}

	return (*list_head);
}

/**
 * empty_rvar_list - Frees a r_var list.
 * @list_head: Pointer to the head of the list.
 *
 * Return: Nothing.
 */
void empty_rvar_list(r_var **list_head)
{
	r_var *temp_node;
	r_var *current_node;

	if (list_head != NULL)
	{
		current_node = *list_head;
		/* Traverse through the list and free each node */
		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}
		/* Set the head to NULL indicating the list is empty */
		*list_head = NULL;
	}
} 
