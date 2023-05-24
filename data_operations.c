#include "shell.h"

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
 * deallocate_CustomShellData_t - Frees the resources used by
 * the CustomShellData_t structure.
 *
 * @datash: Pointer to the CustomShellData_t structure.
 * Return: No return.
 */
void deallocate_CustomShellData_t(CustomShellData_t *datash)
{
	size_t index;

	for (index = 0; datash->environment[index]; index++)
	{
		free(datash->environment[index]);
	}

	free(datash->environment);
	free(datash->process_identifier);
}

/**
 * setup_CustomShellData_t - Initializes the CustomShellData_t
 * structure with default values.
 *
 * @datash: Pointer to the CustomShellData_t structure.
 * @arguments: Argument vector.
 * Return: No return.
 */
void setup_CustomShellData_t(CustomShellData_t *datash, char **arguments)
{
	size_t index;

	datash->arguments = arguments;
	datash->input_data = NULL;
	datash->parsed_arguments = NULL;
	datash->operation_status = 0;
	datash->counter_value = 1;

	for (index = 0; environ[index]; index++)
		;

	datash->environment = malloc(sizeof(char *) * (index + 1));

	for (index = 0; environ[index]; index++)
	{
		datash->environment[index] = duplicate_str(environ[index]);
	}

	datash->environment[index] = NULL;
	datash->process_identifier = convert_int_to_string(getpid());
}
/**
 * handle_exit_status - Handles the exit status and prints
 * the corresponding error message.
 *
 * @datash: Pointer to the CustomShellData_t struct
 * containing relevant data (args).
 * @eval: The exit status value.
 * Return: The exit status value.
 */
int handle_exit_status(CustomShellData_t *datash, int eval)
{
	char *error = NULL;

	if (eval == -1)
		error = generate_env_error(datash);
	else if (eval == 126)
		error = generate_permission_error(datash);
	else if (eval == 127)
		error = generate_not_found_error(datash);
	else if (eval == 2)
	{
		if (compare_strings("exit", datash->parsed_arguments[0]) == 0)
			error = generate_error_msg(datash);
		else if (compare_strings("cd", datash->parsed_arguments[0]) == 0)
			error = generate_cd_error(datash);
	}

	if (error != NULL)
	{
		write(STDERR_FILENO, error,  get_str_length(error));
		free(error);
	}

	datash->operation_status = eval;
	return (eval);
}

/**
 * find_builtin_function - Finds the function associated
 * with a built-in command.
 *
 * @cmd: The name of the built-in command.
 * Return: Pointer to the corresponding function, or NULL if not found.
 */
int (*find_builtin_function(char *cmd))(CustomShellData_t *)
{
	custom_builtin_t builtin[] = {
		{ "env", print_environment_variables },
		{ "exit", terminate },
		{ "setenv", Update_environment },
		{ "unsetenv", erase_env_variable },
		{ "cd", changeDirectoryShell },
		{ "help", show_help_info },
		{ NULL, NULL }	};
	int index = 0;

	while (builtin[index].command_name)
	{
		if (compare_strings(builtin[index].command_name, cmd) == 0)
			return (builtin[index].function_ptr);
		index++;
	}

	return (NULL);
}

