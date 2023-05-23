#include "shell.h"

/**
 * swapCharacters - swaps | and & for non-printed chars
 *
 * @input: input string
 * @swap: type of swap
 * Return: swapped string
 */
char *swapCharacters(char *input, int swap)
{
	int i;

	if (swap == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * addSeparatorsAndCommands - add separators and command lines in the lists
 *
 * @separatorListHead: head of separator list
 * @commandListHead: head of command lines list
 * @input: input string
 * Return: no return
 */
void addSeparatorsAndCommands(sep_list **separatorListHead,
		line_list **commandListHead, char *input)
{
	int i;
	char *line;

	input = swapCharacters(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			append_separator(separatorListHead, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			append_separator(separatorListHead, input[i]);
			i++;
		}
	}

	line = split_str(input, ";|&");
	do {
		line = swapCharacters(line, 1);
		append_line(commandListHead, line);
		line = split_str(NULL, ";|&");
	} while (line != NULL);

}

/**
 * goToNextCommand - go to the next command line stored
 *
 * @separatorList: separator list
 * @commandList: command line list
 * @datash: data structure
 * Return: no return
 */
void goToNextCommand(sep_list **separatorList,
	line_list **commandList, data_shell *datash)
{
	int loopSeparator;
	sep_list *ls_s;
	line_list *ls_l;

	loopSeparator = 1;
	ls_s = *separatorList;
	ls_l = *commandList;

	while (ls_s != NULL && loopSeparator)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loopSeparator = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loopSeparator = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loopSeparator)
			ls_s = ls_s->next;
	}

	*separatorList = ls_s;
	*commandList = ls_l;
}

/**
 * splitAndExecuteCommands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int splitAndExecuteCommands(data_shell *datash, char *input)
{

	sep_list *separatorListHead, *separatorList;
	line_list *commandListHead, *commandList;
	int loop;

	separatorListHead = NULL;
	commandListHead = NULL;

	addSeparatorsAndCommands(&separatorListHead, &commandListHead, input);

	separatorList = separatorListHead;
	commandList = commandListHead;

	while (commandList != NULL)
	{
		datash->input = commandList->line;
		datash->args = tokenizeInputString(datash->input);
		loop = find_builtin(datash);
		free(datash->args);

		if (loop == 0)
			break;

		goToNextCommand(&separatorList, &commandList, datash);

		if (commandList != NULL)
			commandList = commandList->next;
	}

	release_separator_memory(&separatorListHead);
	release_line_memory(&commandListHead);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * tokenizeInputString - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **tokenizeInputString(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * bsize);
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = split_str(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = resize_double_ptr(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = split_str(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

