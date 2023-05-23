#include"shell.h"
/**
 * is_digit - checks if string passed is a number
 *
 * @input_string: input string
 * Return: 1 if string is a number. 0 otherwise.
 */
int is_digit(const char *input_string)
{
	unsigned int i;

	for (i = 0; input_string[i]; i++)
	{
		if (input_string[i] < 48 || input_string[i] > 57)
			return (0);
	}
	return (1);
}
