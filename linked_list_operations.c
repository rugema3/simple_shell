#include "shell.h"

/**
 * cleanup - Frees the memory allocated for the variable list.
 *
 * @variableHead: Pointer to the head of the variable list.
 */
void cleanup(custom_var_list_t **variableHead)
{
	custom_var_list_t *tempVariable;
	custom_var_list_t *currentVariable;

	if (variableHead != NULL)
	{
		currentVariable = *variableHead;
		for (; currentVariable != NULL; currentVariable = tempVariable)
		{
			tempVariable = currentVariable->next;
			free(currentVariable);
		}
		*variableHead = NULL;
	}
}

/**
 * append_separator - Appends a separator node at the end of the list.
 *
 * @separatorHead: Pointer to the head of the separator list.
 * @separatorChar: Separator character to be added.
 * Return: Pointer to the updated head of the separator list.
 */
custom_separator_node_t *append_separator(custom_separator_node_t
		**separatorHead, char separatorChar)
{
	custom_separator_node_t *newSeparator, *tempSeparator;

	newSeparator = malloc(sizeof(custom_separator_node_t));
	if (newSeparator == NULL)
		return (NULL);

	newSeparator->custom_character = separatorChar;
	newSeparator->next = NULL;
	tempSeparator = *separatorHead;

	if (tempSeparator == NULL)
	{
		*separatorHead = newSeparator;
	}
	else
	{
		while (tempSeparator->next != NULL)
			tempSeparator = tempSeparator->next;
		tempSeparator->next = newSeparator;
	}

	return (*separatorHead);
}

/**
 * release_separator_memory - Frees the memory allocated for
 * the separator list.
 *
 * @separatorHead: Pointer to the head of the separator list.
 */
void release_separator_memory(custom_separator_node_t **separatorHead)
{
	custom_separator_node_t *tempSeparator;
	custom_separator_node_t *currSeparator;

	if (separatorHead != NULL)
	{
		currSeparator = *separatorHead;
		while ((tempSeparator = currSeparator) != NULL)
		{
			currSeparator = currSeparator->next;
			free(tempSeparator);
		}
		*separatorHead = NULL;
	}
}

/**
 * append_line - Appends a line node at the end of the list.
 *
 * @lineHead: Pointer to the head of the line list.
 * @lineStr: Line to be added.
 * Return: Pointer to the updated head of the line list.
 */
custom_line_list_t *append_line(custom_line_list_t **lineHead, char *lineStr)
{
	custom_line_list_t *newLine, *tempLine;

	newLine = malloc(sizeof(custom_line_list_t));
	if (newLine == NULL)
		return (NULL);

	newLine->text = lineStr;
	newLine->next = NULL;
	tempLine = *lineHead;

	if (tempLine == NULL)
	{
		*lineHead = newLine;
	}
	else
	{
		while (tempLine->next != NULL)
			tempLine = tempLine->next;
		tempLine->next = newLine;
	}

	return (*lineHead);
}

/**
 * release_line_memory - Frees the memory allocated for the line list.
 *
 * @lineHead: Pointer to the head of the line list.
 */
void release_line_memory(custom_line_list_t **lineHead)
{
	custom_line_list_t *tempLine;
	custom_line_list_t *currLine;

	if (lineHead != NULL)
	{
		currLine = *lineHead;
		while ((tempLine = currLine) != NULL)
		{
			currLine = currLine->next;
			free(tempLine);
		}
		*lineHead = NULL;
	}
}

