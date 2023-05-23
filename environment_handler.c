#include"shell.h"

/**
 * Update_environment - updates an environment variable
 * with a new value
 *
 * @datash: data relevant (environment name and value)
 *
 * Return: 1 on success.
 */
int Update_environment(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		handle_exit_status(datash, -1);
		return (1);
	}

	change_env_variable(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * erase_env_variable - deletes an environment variable
 * @datash: data relevant (environment name)
 * Return: 1 on success.
 */
int erase_env_variable(data_shell *datash)
{
	char **realloc_environ;
	char *var_entry, *name_entry;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		handle_exit_status(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_entry = duplicate_str(datash->_environ[i]);
		name_entry = split_str(var_entry, "=");
		if (compare_strings(name_entry, datash->args[1]) == 0)
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
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
