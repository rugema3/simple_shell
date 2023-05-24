#include"shell.h"

/**
 * append_rvar_element - Appends a new node to a custom_var_list_t linked list.
 * @list_head: Pointer to the head of the list.
 * @var_length: Length of the variable.
 * @variable_value: Value of the variable.
 * @value_length: Length of the value.
 *
 * Return: Pointer to the head of the list.
 */
custom_var_list_t *append_rvar_element(custom_var_list_t **list_head,
		int var_length, char *variable_value, int value_length)
{
	custom_var_list_t *new_node, *temp_node;

	/* Allocating memory for the new node */
	new_node = malloc(sizeof(custom_var_list_t));
	if (new_node == NULL)
		return (NULL);

	/* Initializing the new node */
	new_node->variable_length = var_length;
	new_node->variable_value = variable_value;
	new_node->value_length = value_length;
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
 * empty_rvar_list - Frees a custom_var_list_t list.
 * @list_head: Pointer to the head of the list.
 *
 * Return: Nothing.
 */
void empty_rvar_list(custom_var_list_t **list_head)
{
	custom_var_list_t *temp_node;
	custom_var_list_t *current_node;

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

