#include "shell.h"

/**
 * append - Append a variable node at the end of the list.
 *
 * @variableHead: Pointer to the head of the variable list.
 * @varLength: Length of the variable.
 * @value: Value of the variable.
 * @valueLength: Length of the value.
 *
 * Return: Pointer to the updated head of the variable list.
 */
custom_var_list_t *append(custom_var_list_t **variableHead, int varLength,
		char *value, int valueLength)
{
	custom_var_list_t *newVariable, *tempVariable;

	newVariable = malloc(sizeof(custom_var_list_t));
	if (newVariable == NULL)
		return (NULL);

	newVariable->variable_length = varLength;
	newVariable->variable_value = value;
	newVariable->value_length = valueLength;

	newVariable->next = NULL;
	tempVariable = *variableHead;

	if (tempVariable == NULL)
	{
		*variableHead = newVariable;
	}
	else
	{
		for (; tempVariable->next != NULL; tempVariable = tempVariable->next)
		{
			/* Iterate to the next node */
		}

		tempVariable->next = newVariable;
	}

	return (*variableHead);
}

/**
 * display_help_command - Displays help information for
 * the 'help' builtin command.
 * Return: void
 */
void display_help_command(void)
{
	char *helpText = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
	helpText = "\tDisplay information about builtin commands.\n";
	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
	helpText = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
}

/**
 * display_alias_help - Displays help information for the
 * 'alias' builtin command.
 * Return: void
 */
void display_alias_help(void)
{
	char *helpText = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
	helpText = "\tDefine or display aliases.\n";
	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
}

/**
 * display_cd_help - Displays help information for the 'cd' builtin command.
 * Return: void
 */
void display_cd_help(void)
{
	char *helpText = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
	helpText = "\tChange the shell working directory.\n";
	write(STDOUT_FILENO, helpText,  get_str_length(helpText));
}

