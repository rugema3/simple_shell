#include "shell.h"

/**
 * duplicate_str - duplicates a str in the heap memory.
 * @input_string: Type char pointer str
 * Return: duplicated str
 */
char *duplicate_str(const char *input_string)
{
	char *new_str;
	size_t str_length;

	str_length = get_str_length(input_string);
	new_str = malloc(sizeof(char) * (str_length + 1));
	if (new_str == NULL)
		return (NULL);
	copy_memory(new_str, input_string, str_length + 1);
	return (new_str);
}
