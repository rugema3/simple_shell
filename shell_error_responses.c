#include"shell.h"

/**
 * generate_env_error - Function that generates an error message when
 * there's an error in adding or removing from the environment.
 *
 * @data_sh: data relevant (directory)
 * Return: Error message
 */
char *generate_env_error(CustomShellData_t *data_sh)
{
	int err_msg_len;  /* Variable to store the length of the error message */
	char *err_msg;  /* Variable to store the error message */
	char *line_count_str;  /* Variable to store the line count as a string */
	char *error_description;  /* Variable to store the description of the error */

	/* Convert the counter to a string */
	line_count_str = convert_int_to_string(data_sh->counter_value);

	/* Set the error description */
	error_description = ": Unable to add/remove from environment\n";

	/* Calculate the length of the error message */
	err_msg_len = get_str_length(data_sh->arguments[0]) +
		get_str_length(line_count_str);
	err_msg_len += get_str_length(data_sh->parsed_arguments[0]) +
		get_str_length(error_description) + 4;

	/* Allocate memory for the error message */
	err_msg = malloc(sizeof(char) * (err_msg_len + 1));
	if (err_msg == 0)  /* If the allocation fails, clean up and return NULL */
	{
		free(err_msg);
		free(line_count_str);
		return (NULL);
	}

	/* Build the error message */
	copy_string(err_msg, data_sh->arguments[0]);
	concatenate_strings(err_msg, ": ");
	concatenate_strings(err_msg, line_count_str);
	concatenate_strings(err_msg, ": ");
	concatenate_strings(err_msg, data_sh->parsed_arguments[0]);
	concatenate_strings(err_msg, error_description);
	concatenate_strings(err_msg, "\0");

	/* Free the line count string after use */
	free(line_count_str);

	/* Return the generated error message */
	return (err_msg);
}

