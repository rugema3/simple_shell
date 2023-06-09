#include "shell.h"

/**
 * check_colon_dir - Checks if ":" is in the current directory.
 *
 * @path: Pointer to a character array representing the path.
 * @index: Pointer to an integer representing the index.
 *
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int check_colon_dir(char *path, int *index)
{
	for (; path[*index] != ':' && path[*index]; (*index)++)
		;

	if (path[*index])
		(*index)++;

	return (path[*index] == ':');
}
/**
 * find_executable_path - Locates the path of a command.
 *
 * @cmd: Command name
 * @_environ: Environment variable
 * Return: Location of the command.
 */
char *find_executable_path(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = get_environment_variable("PATH", _environ);
	if (path)
	{
		ptr_path = duplicate_str(path);
		len_cmd =  get_str_length(cmd);
		token_path = split_str(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (check_colon_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir =  get_str_length(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			copy_string(dir, token_path);
			concatenate_strings(dir, "/");
			concatenate_strings(dir, cmd);
			concatenate_strings(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = split_str(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * check_executable - Determines if a command is an executable.
 *
 * @datash: Data structure
 * Return: 0 if it is not an executable, other number if it is.
 */
int check_executable(CustomShellData_t *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->parsed_arguments[0];
	for (i = 0; input[i]; i++)
	{
		switch (input[i])
		{
			case '.':
				if (input[i + 1] == '.')
					return (0);
				if (input[i + 1] == '/')
					continue;
				else
					break;
			case '/':
				if (i != 0)
				{
					if (input[i + 1] == '.')
						continue;
					i++;
					break;
				}
			default:
				break;
		}
		break;
	}
	if (i == 0)
		return (0);
	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	handle_exit_status(datash, 127);
	return (-1);
}

/**
 * check_command_error - Verifies if the user has
 * permissions to access the command.
 *
 * @dir: Destination directory
 * @datash: Data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_command_error(char *dir, CustomShellData_t *datash)
{
	if (dir == NULL)
	{
		handle_exit_status(datash, 127);
		return (1);
	}

	if (compare_strings(datash->parsed_arguments[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			handle_exit_status(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->parsed_arguments[0], X_OK) == -1)
		{
			handle_exit_status(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * executeCommand - Executes command lines.
 *
 * @datash: Data structure containing relevant data (args and input)
 * Return: 1 on success.
 */
int executeCommand(CustomShellData_t *datash)
{
	pid_t pd, wpd;
	int state, exec;
	char *dir;
	(void) wpd;

	exec = check_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = find_executable_path(datash->parsed_arguments[0], datash->environment);
		if (check_command_error(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = find_executable_path(datash->parsed_arguments[0],
					datash->environment);
		else
			dir = datash->parsed_arguments[0];
		execve(dir + exec, datash->parsed_arguments, datash->environment);
	}
	else if (pd < 0)
	{
		perror(datash->arguments[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	datash->operation_status = state / 256;
	return (1);
}

