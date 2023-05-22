#include "main.h"

/**
 * find_builtin - Finds and executes built-in commands.
 *
 * @datash: Pointer to the data_shell struct containing relevant data (args).
 * Return: 1 on success.
 */
int find_builtin(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = find_builtin_function(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));
	return (executeCommand(datash));
}
/**
 * searchEnvironmentVariable - Searches for a typed variable in the environment
 *
 * @head: Head of the linked list
 * @input: Input string
 * @data: Data structure
 * Return: void
 */
void searchEnvironmentVariable(r_var **head, char *input, data_shell *data)
{
	int row, chr, j, val_len;
	char **environment;

	environment = data->_environ;
	for (row = 0; environment[row]; row++)
	{
		for (j = 1, chr = 0; environment[row][chr]; chr++)
		{
			if (environment[row][chr] == '=')
			{
				val_len = _strlen(environment[row] + chr + 1);
				append(head, j, environment[row] + chr + 1, val_len);
				return;
			}

			if (input[j] == environment[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';' ||
				input[j] == '\n')
			break;
	}

	append(head, j, NULL, 0);
}

/**
 * searchSpecialVariables - Searches for special variables like $$ or $?
 *
 * @head: Head of the linked list
 * @input: Input string
 * @status: Last status of the shell
 * @data: Data structure
 * Return: Length of the search
 */
int searchSpecialVariables(r_var **head, char *input,
char *status, data_shell *data)
{
	int i, status_len, pid_len;

	status_len = _strlen(status);
	pid_len = _strlen(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				append(head, 2, status, status_len), i++;
			else if (input[i + 1] == '$')
				append(head, 2, data->pid, pid_len), i++;
			else if (input[i + 1] == '\n' || input[i + 1] == '\0' ||
					input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == ';')
				append(head, 0, NULL, 0);
			else
				searchEnvironmentVariable(head, input + i, data);
		}
	}

	return (i);
}

/**
 * replaceStringWithVariables - Replaces string with variables
 *
 * @head: Head of the linked list
 * @input: Input string
 * @newInput: New input string (replaced)
 * @newLength: New length of the string
 * Return: Replaced string
 */
char *replaceStringWithVariables(r_var **head, char *input,
		char *newInput, int newLength)
{
	r_var *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < newLength; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				newInput[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
				for (k = 0; k < index->len_var; k++)
					j++;
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					newInput[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			newInput[i] = input[j];
			j++;
		}
	}

	return (newInput);
}

/**
 * replaceVariablesInInput - Replaces variables in the input string
 *
 * @input: Input string
 * @datash: Data structure
 * Return: Replaced string
 */
char *replaceVariablesInInput(char *input, data_shell *datash)
{
	r_var *head, *index;
	char *status, *newInput;
	int originalLen, newLen;

	status = aux_itoa(datash->status);
	head = NULL;

	originalLen = searchSpecialVariables(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	newLen = 0;

	while (index != NULL)
	{
		newLen += (index->len_val - index->len_var);
		index = index->next;
	}

	newLen += originalLen;

	newInput = malloc(sizeof(char) * (newLen + 1));
	newInput[newLen] = '\0';

	newInput = replaceStringWithVariables(&head, input, newInput, newLen);

	free(input);
	free(status);
	cleanup(&head);

	return (newInput);
}

