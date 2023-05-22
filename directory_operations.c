#include "main.h"

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
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (compare_strings(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (compare_strings("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
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

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datash);

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
	copied_pwd = _strdup(current_pwd);
	/* Create a copy of the current working directory */
	env_oldpwd = _getenv("OLDPWD", datash->_environ);
	/* Get the value of the environment variable OLDPWD */
	if (env_oldpwd == NULL)
		copied_oldpwd = copied_pwd;
	/**
	 * If OLDPWD is not set, use the current working
	 *  directory as the previous directory
	 */
	else
		copied_oldpwd = _strdup(env_oldpwd);
	/* Create a copy of the previous working directory */
	set_env("OLDPWD", copied_pwd, datash);
	/* Set the environment variable OLDPWD to the current working directory */
	if (chdir(copied_oldpwd) == -1)
		set_env("PWD", copied_pwd, datash);
	else
		set_env("PWD", copied_oldpwd, datash);
	previous_pwd = _getenv("PWD", datash->_environ);
	write(STDOUT_FILENO, previous_pwd, _strlen(previous_pwd));
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

	previous_pwd = _strdup(current_pwd);

	home_directory = _getenv("HOME", datash->_environ);

	if (home_directory == NULL)
	{
		set_env("OLDPWD", previous_pwd, datash);
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

	set_env("OLDPWD", previous_pwd, datash);
	set_env("PWD", home_directory, datash);

	free(previous_pwd);
	datash->status = 0;
}

