#include"shell.h"

/**
 * find_syntax_errors - finds syntax errors
 *
 * @input_str: input string
 * @index: index
 * @last_char: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int find_syntax_errors(char *input_str, int index, char last_char)
{
	int count;

	count = 0;
	if (*input_str == '\0')
		return (0);

	switch (*input_str)
	{
		case ' ':
		case '\t':
			return (find_syntax_errors(input_str + 1, index + 1, last_char));
		case ';':
			if (last_char == '|' || last_char == '&' || last_char == ';')
				return (index);
			break;
		case '|':
			if (last_char == ';' || last_char == '&')
				return (index);
			if (last_char == '|')
			{
				count = count_char_repetition(input_str, 0);
				if (count == 0 || count > 1)
					return (index);
			}
			break;
		case '&':
			if (last_char == ';' || last_char == '|')
				return (index);
			if (last_char == '&')
			{
				count = count_char_repetition(input_str, 0);
				if (count == 0 || count > 1)
					return (index);
			}
			break;
		default:
			break;
	}

	return (find_syntax_errors(input_str + 1, index + 1, *input_str));
}

/**
 * output_syntax_error - prints when a syntax error is found
 * @data_sh: data structure
 * @input_str: input string
 * @index: index of the error
 * @bool_flag: to control msg error
 * Return: no return
 */
void output_syntax_error(CustomShellData_t *data_sh, char *input_str,
		int index, int bool_flag)
{
	char *syntax_msg, *syntax_msg2, *syntax_msg3, *error_msg, *counter_str;
	int length;

	syntax_msg2 = ": Syntax error: \"";
	syntax_msg3 = "\" unexpected\n";
	counter_str = convert_int_to_string(data_sh->counter_value);
	length = get_str_length(data_sh->arguments[0]) + get_str_length(counter_str);
	length += get_str_length(syntax_msg2) + get_str_length(syntax_msg3) + 2;
	switch (input_str[index])
	{
		case ';':
			syntax_msg = (bool_flag == 0 && input_str[index + 1] == ';') ||
				(bool_flag == 1 && input_str[index - 1] == ';') ? ";;" : ";";
			break;
		case '|':
			syntax_msg = "||";
			break;
		case '&':
			syntax_msg = "&&";
			break;
		default:
			break;
	}
	length += get_str_length(syntax_msg);
	error_msg = malloc(sizeof(char) * (length + 1));
	if (error_msg == NULL)
	{
		free(counter_str);
		return;
	}
	copy_string(error_msg, data_sh->arguments[0]);
	concatenate_strings(error_msg, ": ");
	concatenate_strings(error_msg, counter_str);
	concatenate_strings(error_msg, syntax_msg2);
	concatenate_strings(error_msg, syntax_msg);
	concatenate_strings(error_msg, syntax_msg3);
	concatenate_strings(error_msg, "\0");
	write(STDERR_FILENO, error_msg, length);
	free(error_msg);
	free(counter_str);
}

/**
 * count_char_repetition - counts the repetitions of a char
 *
 * @input_str: input string
 * @index: index
 * Return: repetitions
 */
int count_char_repetition(char *input_str, int index)
{
	if (*(input_str - 1) == *input_str)
		return (count_char_repetition(input_str - 1, index + 1));

	return (index);
}


/**
 * locate_first_char - finds index of the first char
 *
 * @input_str: input string
 * @index_ptr: index
 * Return: 1 if there is an error. 0 in other case.
 */
int locate_first_char(char *input_str, int *index_ptr)
{

	for (*index_ptr = 0; input_str[*index_ptr]; *index_ptr += 1)
	{
		if (input_str[*index_ptr] == ' ' || input_str[*index_ptr] == '\t')
			continue;

		if (input_str[*index_ptr] == ';' || input_str[*index_ptr] == '|' ||
				input_str[*index_ptr] == '&')
			return (-1);

		break;
	}

	return (0);
}


/**
 * validate_syntax - intermediate function to
 * find and print a syntax error
 *
 * @data_sh: data structure
 * @input_str: input string
 * Return: 1 if there is an error. 0 in other case
 */
int validate_syntax(CustomShellData_t *data_sh, char *input_str)
{
	int begin_index = 0;
	int first_char_index = 0;
	int error_index = 0;

	first_char_index = locate_first_char(input_str, &begin_index);
	if (first_char_index == -1)
	{
		output_syntax_error(data_sh, input_str, begin_index, 0);
		return (1);
	}

	error_index = find_syntax_errors(input_str + begin_index, 0,
			*(input_str + begin_index));
	if (error_index != 0)
	{
		output_syntax_error(data_sh, input_str, begin_index + error_index, 1);
		return (1);
	}

	return (0);
}
