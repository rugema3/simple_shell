#include"shell.h"

/**
 * generate_error_msg - Generates an error message for illegal numbers.
 * @data_sh: Pointer to the data structure.
 * Return: The error message string.
 */
char *generate_error_msg(data_shell *data_sh)
{
	int msg_length;
	char *error_msg;
	char *counter_str;

	/* Convert counter value to string */
	counter_str = convert_int_to_string(data_sh->counter);

	/* Calculate total length of the error message */
	msg_length =  get_str_length(data_sh->av[0]) +
		get_str_length(counter_str);
	msg_length += get_str_length(data_sh->args[0]) +
		get_str_length(data_sh->args[1]) + 23;

	/* Allocate memory for the error message */
	error_msg = malloc(sizeof(char) * (msg_length + 1));
	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	/* Construct the error message */
	copy_string(error_msg, data_sh->av[0]);
	concatenate_strings(error_msg, ": ");
	concatenate_strings(error_msg, counter_str);
	concatenate_strings(error_msg, ": ");
	concatenate_strings(error_msg, data_sh->args[0]);
	concatenate_strings(error_msg, ": number not allowed: ");
	concatenate_strings(error_msg, data_sh->args[1]);
	concatenate_strings(error_msg, "\n\0");

	/* Free the counter string after use */
	free(counter_str);

	return (error_msg);
}

/**
 * concatenate_cd_error - function that constructs
 * the error message for cd command
 *
 * @data_sh: data relevant (directory)
 * @message: message to print
 * @error_output: output message
 * @counter_str: counter lines
 * Return: error message
 */
char *concatenate_cd_error(data_shell *data_sh, char *message,
		char *error_output, char *counter_str)
{
	char *illegal_opt_flag;

	copy_string(error_output, data_sh->av[0]);
	concatenate_strings(error_output, ": ");
	concatenate_strings(error_output, counter_str);
	concatenate_strings(error_output, ": ");
	concatenate_strings(error_output, data_sh->args[0]);
	concatenate_strings(error_output, message);
	if (data_sh->args[1][0] == '-')
	{
		illegal_opt_flag = malloc(3);
		illegal_opt_flag[0] = '-';
		illegal_opt_flag[1] = data_sh->args[1][1];
		illegal_opt_flag[2] = '\0';
		concatenate_strings(error_output, illegal_opt_flag);
		free(illegal_opt_flag);
	}
	else
	{
		concatenate_strings(error_output, data_sh->args[1]);
	}

	concatenate_strings(error_output, "\n");
	concatenate_strings(error_output, "\0");
	return (error_output);
}

/**
 * generate_permission_error - Function that generates an error message
 * when there's a permission error with the path provided.
 *
 * @data_sh: data relevant (directory)
 * Return: Error message
 */
char *generate_permission_error(data_shell *data_sh)
{
	int err_msg_len;  /* Variable to store the length of the error message */
	char *line_count_str;  /* Variable to store the line count as a string */
	char *err_msg;  /* Variable to store the error message */

	/* Convert the counter to a string */
	line_count_str = convert_int_to_string(data_sh->counter);

	/* Calculate the length of the error message */
	err_msg_len = get_str_length(data_sh->av[0]) + get_str_length(line_count_str);
	err_msg_len += get_str_length(data_sh->args[0]) + 24;

	/* Allocate memory for the error message */
	err_msg = malloc(sizeof(char) * (err_msg_len + 1));
	if (err_msg == 0)  /* If the allocation fails, clean up and return NULL */
	{
		free(err_msg);
		free(line_count_str);
		return (NULL);
	}

	/* Build the error message */
	copy_string(err_msg, data_sh->av[0]);
	concatenate_strings(err_msg, ": ");
	concatenate_strings(err_msg, line_count_str);
	concatenate_strings(err_msg, ": ");
	concatenate_strings(err_msg, data_sh->args[0]);
	concatenate_strings(err_msg, ": Permission denied\n");
	concatenate_strings(err_msg, "\0");

	/* Free the line count string after use */
	free(line_count_str);

	/* Return the generated error message */
	return (err_msg);
}

/**
 * generate_cd_error - error message for cd command
 * @data_sh: data relevant (directory)
 * Return: Error message
 */
char *generate_cd_error(data_shell *data_sh)
{
	int msg_length, id_len;
	char *error_output, *counter_str, *message;

	counter_str = convert_int_to_string(data_sh->counter);
	if (data_sh->args[1][0] == '-')
	{
		message = ": Illegal option ";
		id_len = 2;
	}
	else
	{
		message = ": can't cd to ";
		id_len = get_str_length(data_sh->args[1]);
	}

	msg_length = get_str_length(data_sh->av[0]) +
		get_str_length(data_sh->args[0]);
	msg_length += get_str_length(counter_str) +
		get_str_length(message) + id_len + 5;
	error_output = malloc(sizeof(char) * (msg_length + 1));

	if (error_output == 0)
	{
		free(counter_str);
		return (NULL);
	}

	error_output =
		concatenate_cd_error(data_sh, message, error_output, counter_str);

	free(counter_str);

	return (error_output);
}

/**
 * generate_not_found_error - generic error message for command not found
 * @data_sh: data relevant (counter, arguments)
 * Return: Error message
 */
char *generate_not_found_error(data_shell *data_sh)
{
	int msg_length;
	char *error_output;
	char *counter_str;

	counter_str = convert_int_to_string(data_sh->counter);
	msg_length = get_str_length(data_sh->av[0]) + get_str_length(counter_str);
	msg_length += get_str_length(data_sh->args[0]) + 16;
	error_output = malloc(sizeof(char) * (msg_length + 1));
	if (error_output == 0)
	{
		free(error_output);
		free(counter_str);
		return (NULL);
	}
	copy_string(error_output, data_sh->av[0]);
	concatenate_strings(error_output, ": ");
	concatenate_strings(error_output, counter_str);
	concatenate_strings(error_output, ": ");
	concatenate_strings(error_output, data_sh->args[0]);
	concatenate_strings(error_output, ": not found\n");
	concatenate_strings(error_output, "\0");
	free(counter_str);
	return (error_output);
}

