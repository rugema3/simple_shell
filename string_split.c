#include"shell.h"

/**
 * split_str - splits a string by some delimiter.
 * @input_string: input string.
 * @delimiter: delimiter.
 *
 * Return: string splited.
 */
char *split_str(char input_string[], const char *delimiter)
{
	static char *tokenized, *str_end;
	char *str_start;
	unsigned int i, token_flag;

	if (input_string != NULL)
	{
		if (compare_characters(input_string, delimiter))
			return (NULL);
		tokenized = input_string; /*Store first address*/
		i = get_str_length(input_string);
		str_end = &input_string[i]; /*Store last address*/
	}
	str_start = tokenized;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (token_flag = 0; *tokenized; tokenized++)
	{
		/*Breaking loop finding the next token*/
		if (tokenized != str_start)
			if (*tokenized && *(tokenized - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delimiter[i]; i++)
		{
			if (*tokenized == delimiter[i])
			{
				*tokenized = '\0';
				if (tokenized == str_start)
					str_start++;
				break;
			}
		}
		if (token_flag == 0 && *tokenized) /*Str != Delim*/
			token_flag = 1;
	}
	if (token_flag == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}
