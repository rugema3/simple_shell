#include "main.h"

/**
 * display_env_help - Displays help information for the 'env' builtin command.
 */
void display_env_help(void)
{
	char *helpText = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * display_setenv_help - Displays help information
 * for the 'setenv' builtin command.
 * Return: void
 */
void display_setenv_help(void)
{
	char *helpText1 = "setenv: setenv (const char *name, ";
	char *helpText2 = "const char *value, ";
	char *helpText3 = "int replace)\n";
	char *helpText4 = "Add a new definition to the environment.\n";

	write(STDOUT_FILENO, helpText1, _strlen(helpText1));
	write(STDOUT_FILENO, helpText2, _strlen(helpText2));
	write(STDOUT_FILENO, helpText3, _strlen(helpText3));
	write(STDOUT_FILENO, helpText4, _strlen(helpText4));
}

/**
 * display_unsetenv_help - Displays help information
 * for the 'unsetenv' builtin command.
 * Return: void
 */
void display_unsetenv_help(void)
{
	char *helpText = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "Remove an entry completely from the environment.\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * display_general_help - Displays general help information for the shell.
 */
void display_general_help(void)
{
	char *helpText = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "The commands are defined internally.";
	write(STDOUT_FILENO, helpText, _strlen(helpText));
	helpText = "Type 'help' to see the list.\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "Type 'help name' to find out more about the function 'name'.\n\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "alias: alias [name=['string']]\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "exit: exit [n]\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "env: env [option] [name=value] [command [args]]\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "setenv: setenv [variable] [value]\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "unsetenv: unsetenv [variable]\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));
}

/**
 * display_exit_help - Displays help information for
 * the 'exit' builtin command.
 */
void display_exit_help(void)
{
	char *helpText = "exit: exit [n]\n";

	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "Exit the shell.\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));

	helpText = "Exits the shell with a status of N.";
	write(STDOUT_FILENO, helpText, _strlen(helpText));
	helpText = "is that of the last command executed.\n";
	write(STDOUT_FILENO, helpText, _strlen(helpText));
}

