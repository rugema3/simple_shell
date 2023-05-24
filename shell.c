#include"shell.h"

/**
 * terminate - Exits the shell.
 *
 * @datash: Pointer to the data_shell struct containing
 * relevant data (status and args).
 * Return: 0 on success.
 */
int terminate(CustomShellData_t *datash)
{
	unsigned int exit_status = 0;
	int is_num = 0;
	int str_len = 0;
	int is_big_number = 0;

	/* Check if an exit status is provided as an argument */
	if (datash->parsed_arguments[1] != NULL)
	{
		exit_status = convert_string_to_int(datash->parsed_arguments[1]);
		is_num = is_digit(datash->parsed_arguments[1]);
		str_len =  get_str_length(datash->parsed_arguments[1]);
		is_big_number = exit_status > UINT_MAX;

		/* Validate the exit status argument */
		if (!is_num || str_len > 10 || is_big_number)
		{
			/* Display error message and set status to 2 */
			handle_exit_status(datash, 2);
			datash->operation_status = 2;
			return (1); /* Return 1 to indicate an error */
		}

		/* Set the exit status based on the provided argument */
		datash->operation_status = (exit_status % EXIT_STATUS_MOD);
	}

	return (0); /* Return 0 on success */
}

/**
 * show_help_info - Displays help messages based on the given command.
 *
 * @datash: Pointer to the data_shell struct containing
 * relevant data (args and input).
 * Return: Always returns 1.
 */
int show_help_info(CustomShellData_t *datash)
{
	if (datash->parsed_arguments[1] == 0)
		display_general_help();  /* Display general help information */
	else if (compare_strings(datash->parsed_arguments[1], "setenv") == 0)
		display_setenv_help();  /* Display help information  */
	else if (compare_strings(datash->parsed_arguments[1], "env") == 0)
		display_env_help();  /* Display help information for env command */
	else if (compare_strings(datash->parsed_arguments[1], "unsetenv") == 0)
		display_unsetenv_help();  /* Display help information for unsetenv command */
	else if (compare_strings(datash->parsed_arguments[1], "help") == 0)
		display_help_command();  /* Display help information for help command */
	else if (compare_strings(datash->parsed_arguments[1], "exit") == 0)
		display_exit_help();  /* Display help information for exit command */
	else if (compare_strings(datash->parsed_arguments[1], "cd") == 0)
		display_cd_help();  /* Display help information for cd command */
	else if (compare_strings(datash->parsed_arguments[1], "alias") == 0)
		display_alias_help();  /* Display help information for alias command */
	else
		write(STDERR_FILENO, datash->parsed_arguments[0],
		       get_str_length(datash->parsed_arguments[0]));
	/* Invalid command, display error message */

	datash->operation_status = 0;
	return (1);
}



/**
 * main - Entry point
 *
 * @ac: argument count
 * @arguments: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **arguments)
{
	CustomShellData_t datash;
	(void) ac;

	signal(SIGINT, prompt);
	setup_CustomShellData_t(&datash, arguments);
	interactive_shell(&datash);
	deallocate_CustomShellData_t(&datash);
	if (datash.operation_status < 0)
		return (255);
	return (datash.operation_status);
}
