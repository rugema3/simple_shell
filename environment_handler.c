#include"shell.h"

/**
 * Update_environment - updates an environment variable
 * with a new value
 *
 * @datash: data relevant (environment name and value)
 *
 * Return: 1 on success.
 */
int Update_environment(CustomShellData_t *datash)
{

	if (datash->parsed_arguments[1] == NULL ||
			datash->parsed_arguments[2] == NULL)
	{
		handle_exit_status(datash, -1);
		return (1);
	}

	change_env_variable(datash->parsed_arguments[1],
			datash->parsed_arguments[2], datash);

	return (1);
}

/**
 * erase_env_variable - deletes an environment variable
 * @datash: data relevant (environment name)
 * Return: 1 on success.
 */
int erase_env_variable(CustomShellData_t *datash)
{
	char **realloc_environ;
	char *var_entry, *name_entry;
	int i, j, k;

	if (datash->parsed_arguments[1] == NULL)
	{
		handle_exit_status(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->environment[i]; i++)
	{
		var_entry = duplicate_str(datash->environment[i]);
		name_entry = split_str(var_entry, "=");
		if (compare_strings(name_entry, datash->parsed_arguments[1]) == 0)
		{
			k = i;
		}
		free(var_entry);
	}
	if (k == -1)
	{
		handle_exit_status(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->environment[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->environment[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->environment[k]);
	free(datash->environment);
	datash->environment = realloc_environ;
	return (1);
}
