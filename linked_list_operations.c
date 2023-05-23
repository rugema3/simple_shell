#include "shell.h"

/**
 * cleanup - Frees the memory allocated for the variable list.
 *
 * @variableHead: Pointer to the head of the variable list.
 */
void cleanup(r_var **variableHead)
{
	r_var *tempVariable;
	r_var *currentVariable;

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
sep_list *append_separator(sep_list **separatorHead, char separatorChar)
{
	sep_list *newSeparator, *tempSeparator;

	newSeparator = malloc(sizeof(sep_list));
	if (newSeparator == NULL)
		return (NULL);

	newSeparator->separator = separatorChar;
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
void release_separator_memory(sep_list **separatorHead)
{
	sep_list *tempSeparator;
	sep_list *currSeparator;

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
line_list *append_line(line_list **lineHead, char *lineStr)
{
	line_list *newLine, *tempLine;

	newLine = malloc(sizeof(line_list));
	if (newLine == NULL)
		return (NULL);

	newLine->line = lineStr;
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
void release_line_memory(line_list **lineHead)
{
	line_list *tempLine;
	line_list *currLine;

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

