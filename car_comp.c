#include"shell.h"
/**
 * compare_characters - compare chars of strings
 * @input_string: input string.
 * @delimiter: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int compare_characters(char input_string[], const char *delimiter)
{
	unsigned int i, j, match_count;

	for (i = 0, match_count = 0; input_string[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (input_string[i] == delimiter[j])
			{
				match_count++;
				break;
			}
		}
	}
	if (i == match_count)
		return (1);
	return (0);
}
