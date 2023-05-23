#include "shell.h"

/**
 * build_new_entry - builds a new environment or alias entry
 * @name: name (environment or alias)
 * @value: value (environment or alias)
 *
 * Return: new environment or alias entry.
 */
char *build_new_entry(char *name, char *value)
{
	char *new_entry;
	int name_length, value_length, entry_length;

	name_length = get_str_length(name);
	value_length = get_str_length(value);
	entry_length = name_length + value_length + 2;
	new_entry = malloc(sizeof(char) * entry_length);
	copy_string(new_entry, name);
	concatenate_strings(new_entry, "=");
	concatenate_strings(new_entry, value);
	concatenate_strings(new_entry, "\0");

	return (new_entry);
}

/**
 * change_env_variable - changes the value of an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void change_env_variable(char *name, char *value, data_shell *datash)
{
	int i = 0;
	char *var_entry, *name_entry;

	while (datash->_environ[i])
	{
		var_entry = duplicate_str(datash->_environ[i]);
		name_entry = split_str(var_entry, "=");
		if (compare_strings(name_entry, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = build_new_entry(name_entry, value);
			free(var_entry);
			return;
		}
		free(var_entry);
		i++;
	}

	datash->_environ = resize_double_ptr(datash->_environ, i,
			sizeof(char *) * (i + 2));
	datash->_environ[i] = build_new_entry(name, value);
	datash->_environ[i + 1] = NULL;
}
/**
 * compare_environment_variable_name - compares env variables names
 * with the name passed.
 * @env_name: name of the environment variable
 * @input_name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_environment_variable_name(const char *env_name,
		const char *input_name)
{
	int outer_loop_index = 0;

	while (env_name[outer_loop_index] != '=')
	{
		if (env_name[outer_loop_index] != input_name[outer_loop_index])
		{
			return (0);
		}
		outer_loop_index++;
	}

	return (outer_loop_index + 1);
}

/**
 * get_environment_variable - get an environment variable
 * @input_name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *get_environment_variable(const char *input_name, char **_environ)
{
	char *environment_pointer;
	int outer_loop_index = 0, move = 0;

	/* Initialize environment_pointer value */
	environment_pointer = NULL;

	/* Compare all environment variables */
	/* environ is declared in the header file */
	while (_environ[outer_loop_index])
	{
		/* If input_name and env are equal */
		move = compare_environment_variable_name
			(_environ[outer_loop_index], input_name);
		if (move)
		{
			environment_pointer = _environ[outer_loop_index];
			break;
		}
		outer_loop_index++;
	}

	return (environment_pointer + move);
}

/**
 * print_environment_variables - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int print_environment_variables(data_shell *datash)
{
	int outer_loop_index = 0, inner_loop_index = 0;

	while (datash->_environ[outer_loop_index])
	{
		inner_loop_index = 0;
		while (datash->_environ[outer_loop_index][inner_loop_index])
		{
			inner_loop_index++;
		}

		write(STDOUT_FILENO, datash->_environ[outer_loop_index], inner_loop_index);
		write(STDOUT_FILENO, "\n", 1);
		outer_loop_index++;
	}
	datash->status = 0;

	return (1);
}

