#include "shell.h"

/**
 * find_builtin - Finds and executes built-in commands.
 *
 * @datash: Pointer to the CustomShellData_t struct
 * containing relevant data (parsed_arguments).
 * Return: 1 on success.
 */
int find_builtin(CustomShellData_t *datash)
{
	int (*builtin)(CustomShellData_t *datash);

	if (datash->parsed_arguments[0] == NULL)
		return (1);

	builtin = find_builtin_function(datash->parsed_arguments[0]);

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
void searchEnvironmentVariable(custom_var_list_t
		**head, char *input, CustomShellData_t *data)
{
	int row, chr, j, val_len;
	char **environment;

	environment = data->environment;
	for (row = 0; environment[row]; row++)
	{
		for (j = 1, chr = 0; environment[row][chr]; chr++)
		{
			if (environment[row][chr] == '=')
			{
				val_len =  get_str_length(environment[row] + chr + 1);
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
int searchSpecialVariables(custom_var_list_t **head, char *input,
char *status, CustomShellData_t *data)
{
	int i, status_len, pid_len;

	status_len =  get_str_length(status);
	pid_len =  get_str_length(data->process_identifier);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				append(head, 2, status, status_len), i++;
			else if (input[i + 1] == '$')
				append(head, 2, data->process_identifier, pid_len), i++;
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
char *replaceStringWithVariables(custom_var_list_t **head, char *input,
		char *newInput, int newLength)
{
	custom_var_list_t *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < newLength; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->variable_length) && !(index->value_length))
			{
				newInput[i] = input[j];
				j++;
			}
			else if (index->variable_length && !(index->value_length))
				for (k = 0; k < index->variable_length; k++)
					j++;
			else
			{
				for (k = 0; k < index->value_length; k++)
				{
					newInput[i] = index->variable_value[k];
					i++;
				}
				j += (index->variable_length);
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
char *replaceVariablesInInput(char *input, CustomShellData_t *datash)
{
	custom_var_list_t *head, *index;
	char *status, *newInput;
	int originalLen, newLen;

	status = convert_int_to_string(datash->operation_status);
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
		newLen += (index->value_length - index->variable_length);
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

