#include "shell.h"

/**
 * changeToParentDirectory - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */
void changeToParentDirectory(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cpsplit_str_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = duplicate_str(pwd);
	change_env_variable("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (compare_strings(".", dir) == 0)
	{
		change_env_variable("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (compare_strings("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cpsplit_str_pwd = cp_pwd;
	reverse_string(cpsplit_str_pwd);
	cpsplit_str_pwd = split_str(cpsplit_str_pwd, "/");
	if (cpsplit_str_pwd != NULL)
	{
		cpsplit_str_pwd = split_str(NULL, "\0");

		if (cpsplit_str_pwd != NULL)
			reverse_string(cpsplit_str_pwd);
	}
	if (cpsplit_str_pwd != NULL)
	{
		chdir(cpsplit_str_pwd);
		change_env_variable("PWD", cpsplit_str_pwd, datash);
	}
	else
	{
		chdir("/");
		change_env_variable("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * changeToDirectory - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void changeToDirectory(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		handle_exit_status(datash, 2);
		return;
	}

	cp_pwd = duplicate_str(pwd);
	change_env_variable("OLDPWD", cp_pwd, datash);

	cp_dir = duplicate_str(dir);
	change_env_variable("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * changeToPreviousDirectory - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void changeToPreviousDirectory(data_shell *datash)
{
	char current_pwd[PATH_MAX];
	/* Buffer to store the current working directory path */
	char *previous_pwd, *env_oldpwd, *copied_pwd, *copied_oldpwd;

	getcwd(current_pwd, sizeof(current_pwd));
	/* Get the current working directory */
	copied_pwd = duplicate_str(current_pwd);
	/* Create a copy of the current working directory */
	env_oldpwd = get_environment_variable("OLDPWD", datash->_environ);
	/* Get the value of the environment variable OLDPWD */
	if (env_oldpwd == NULL)
		copied_oldpwd = copied_pwd;
	/**
	 * If OLDPWD is not set, use the current working
	 *  directory as the previous directory
	 */
	else
		copied_oldpwd = duplicate_str(env_oldpwd);
	/* Create a copy of the previous working directory */
	change_env_variable("OLDPWD", copied_pwd, datash);
	/* Set the environment variable OLDPWD to the current working directory */
	if (chdir(copied_oldpwd) == -1)
		change_env_variable("PWD", copied_pwd, datash);
	else
		change_env_variable("PWD", copied_oldpwd, datash);
	previous_pwd = get_environment_variable("PWD", datash->_environ);
	write(STDOUT_FILENO, previous_pwd,  get_str_length(previous_pwd));
	/* Write the new current directory path */
	write(STDOUT_FILENO, "\n", 1); /* Write a new line character */
	free(copied_pwd);
	/* Free the memory allocated for the copied current working directory path */
	if (env_oldpwd)
		free(copied_oldpwd);
	/* Free the memory allocated for the copied previous working directory path */
	datash->status = 0;
	/* Update the status to indicate successful execution */
	chdir(previous_pwd);
	/* Change the directory to the updated PWD */
}

/**
 * changeDirectoryShell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int changeDirectoryShell(data_shell *datash)
{
	char *directory;
	int isHome, isHome2, isDoubleDash;

	directory = datash->args[1];

	if (directory != NULL)
	{
		isHome = compare_strings("$HOME", directory);
		isHome2 = compare_strings("~", directory);
		isDoubleDash = compare_strings("--", directory);
	}
	/**
	 *  If directory is not provided or matches "$HOME" or "~",
	 *  change directory to home directory
	 */
	if (directory == NULL || !isHome || !isHome2 || !isDoubleDash)
	{
		changeToHomeDirectory(datash);
		return (1);
	}
	/* If directory is "-", change directory to previous directory */
	if (compare_strings("-", directory) == 0)
	{
		changeToPreviousDirectory(datash);
		return (1);
	}
	/* If directory is "." or "..", change directory accordingly */
	if (compare_strings(".", directory) == 0 ||
			compare_strings("..", directory) == 0)
	{
		changeToParentDirectory(datash);
		return (1);
	}
	/* Otherwise, change directory to the specified directory */
	changeToDirectory(datash);
	return (1);
}

/**
 * changeToHomeDirectory - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void changeToHomeDirectory(data_shell *datash)
{
	char *previous_pwd; /* Stores the previous working directory */
	char *home_directory; /* Stores the home directory path */
	char current_pwd[PATH_MAX];
	/* Buffer to store the current working directory path */

	getcwd(current_pwd, sizeof(current_pwd));

	previous_pwd = duplicate_str(current_pwd);

	home_directory = get_environment_variable("HOME", datash->_environ);

	if (home_directory == NULL)
	{
		change_env_variable("OLDPWD", previous_pwd, datash);
		free(previous_pwd);
		return;
	}

	if (chdir(home_directory) == -1)
	{
		handle_exit_status(datash, 2);
		/* Display error message if unable to change directory */

		free(previous_pwd);
		return;
	}

	change_env_variable("OLDPWD", previous_pwd, datash);
	change_env_variable("PWD", home_directory, datash);

	free(previous_pwd);
	datash->status = 0;
}

