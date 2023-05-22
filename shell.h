#ifndef SHELL_H
#define SHELL_H

/**
 * terminate - Exits the shell.
 *
 * @datash: Pointer to the data_shell struct containing
 * relevant data (status and args).
 * Return: 0 on success.
 */
int terminate(data_shell *datash)
{
	unsigned int exit_status;
	int is_digit;
	int str_len;
	int is_big_number;

	/* Check if an exit status is provided as an argument */
	if (datash->args[1] != NULL)
	{
		exit_status = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		is_big_number = exit_status > (unsigned int)INT_MAX;

		/* Validate the exit status argument */
		if (!is_digit || str_len > 10 || is_big_number)
		{
			/* Display error message and set status to 2 */
			handle_exit_status(datash, 2);
			datash->status = 2;
			return (1); /* Return 1 to indicate an error */
		}

		/* Set the exit status based on the provided argument */
		datash->status = (exit_status % 256);
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
int show_help_info(data_shell *datash)
{
	if (datash->args[1] == 0)
		display_general_help();  /* Display general help information */
	else if (_strcmp(datash->args[1], "setenv") == 0)
		display_setenv_help();  /* Display help information  */
	else if (_strcmp(datash->args[1], "env") == 0)
		display_env_help();  /* Display help information for env command */
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		display_unsetenv_help();  /* Display help information for unsetenv command */
	else if (_strcmp(datash->args[1], "help") == 0)
		display_help_command();  /* Display help information for help command */
	else if (_strcmp(datash->args[1], "exit") == 0)
		display_exit_help();  /* Display help information for exit command */
	else if (_strcmp(datash->args[1], "cd") == 0)
		display_cd_help();  /* Display help information for cd command */
	else if (_strcmp(datash->args[1], "alias") == 0)
		display_alias_help();  /* Display help information for alias command */
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));
	/* Invalid command, display error message */

	datash->status = 0;
	return (1);
}



/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, prompt);
	setup_data_shell(&datash, av);
	interactive_shell(&datash);
	deallocate_data_shell(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
#endif /* SHELL_H */
