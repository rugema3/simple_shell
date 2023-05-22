#include "main.h"

/**
 * prompt - Handles the Ctrl+C signal in the prompt.
 *          Displays a custom message when the signal is received.
 * @sig: signal
 */
void prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 10);
}

/**
 * deallocate_data_shell - Frees the resources used by
 * the data_shell structure.
 *
 * @datash: Pointer to the data_shell structure.
 * Return: No return.
 */
void deallocate_data_shell(data_shell *datash)
{
	size_t index;

	for (index = 0; datash->_environ[index]; index++)
	{
		free(datash->_environ[index]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * setup_data_shell - Initializes the data_shell structure with default values.
 *
 * @datash: Pointer to the data_shell structure.
 * @av: Argument vector.
 * Return: No return.
 */
void setup_data_shell(data_shell *datash, char **av)
{
	size_t index;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (index = 0; environ[index]; index++)
		;

	datash->_environ = malloc(sizeof(char *) * (index + 1));

	for (index = 0; environ[index]; index++)
	{
		datash->_environ[index] = _strdup(environ[index]);
	}

	datash->_environ[index] = NULL;
	datash->pid = aux_itoa(getpid());
}
/**
 * handle_exit_status - Handles the exit status and prints
 * the corresponding error message.
 *
 * @datash: Pointer to the data_shell struct containing relevant data (args).
 * @eval: The exit status value.
 * Return: The exit status value.
 */
int handle_exit_status(data_shell *datash, int eval)
{
	char *error = NULL;

	if (eval == -1)
		error = error_env(datash);
	else if (eval == 126)
		error = error_path_126(datash);
	else if (eval == 127)
		error = error_not_found(datash);
	else if (eval == 2)
	{
		if (compare_strings("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (compare_strings("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
	}

	if (error != NULL)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}

/**
 * find_builtin_function - Finds the function associated
 * with a built-in command.
 *
 * @cmd: The name of the built-in command.
 * Return: Pointer to the corresponding function, or NULL if not found.
 */
int (*find_builtin_function(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", terminate },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", changeDirectoryShell },
		{ "help", show_help_info },
		{ NULL, NULL }	};
	int index = 0;

	while (builtin[index].name)
	{
		if (compare_strings(builtin[index].name, cmd) == 0)
			return (builtin[index].f);
		index++;
	}

	return (NULL);
}
