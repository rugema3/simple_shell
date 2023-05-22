#include "main.h"

/**
 * filterComments - deletes comments from the input
 *
 * @input: input string
 * Return: input without comments
 */
char *filterComments(char *input)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, i, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * interactive_shell - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: void
 */
void interactive_shell(data_shell *datash)
{
	int iterate, isEof;
	char *input;

	iterate = 1;
	while (iterate == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = getLineInput(&isEof);
		if (isEof != -1)
		{
			input = filterComments(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replaceVariablesInInput(input, datash);
			iterate = splitAndExecuteCommands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			iterate = 0;
			free(input);
		}
	}
}

/**
 * getLineInput - reads the input string.
 *
 * @isEof: return value of getline function
 * Return: input string
 */
char *getLineInput(int *isEof)
{
	char *input = NULL;
	size_t bufferSize = 0;

	*isEof = getline(&input, &bufferSize, stdin);

	return (input);
}
/**
 * assignLine - assigns the line variable for getLine
 * @lineptr: Buffer that stores the input string
 * @size: Size of lineptr
 * @buffer: String that is being copied to line
 * @length: Length of buffer
 */
void assignLine(char **lineptr, size_t *size, char *buffer, size_t length)
{
	if (*lineptr == NULL)
	{
		if (length > BUFSIZE)
			*size = length;
		else
			*size = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*size < length)
	{
		if (length > BUFSIZE)
			*size = length;
		else
			*size = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		copy_string(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * readLine - Reads input from stream
 * @lineptr: Buffer that stores the input
 * @size: Size of lineptr
 * @stream: Stream to read from
 * Return: The number of bytes read
 */
ssize_t readLine(char **lineptr, size_t *size, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == NULL)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	assignLine(lineptr, size, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}


