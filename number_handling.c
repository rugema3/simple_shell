#include "shell.h"

/**
 * calculate_length - Get the length of a number.
 * @num: type int number.
 * Return: Length of a number.
 */
int calculate_length(int num)
{
	unsigned int temp_num;
	int length = 1;

	if (num < 0)
	{
		length++;
		temp_num = num * -1;
	}
	else
	{
		temp_num = num;
	}
	while (temp_num > 9)
	{
		length++;
		temp_num = temp_num / 10;
	}

	return (length);
}

/**
 * convert_int_to_string - function converts int to string.
 * @num: type int number
 * Return: String.
 */
char *convert_int_to_string(int num)
{
	unsigned int temp_num;
	int length = calculate_length(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (num < 0)
	{
		temp_num = num * -1;
		buffer[0] = '-';
	}
	else
	{
		temp_num = num;
	}

	length--;
	do {
		*(buffer + length) = (temp_num % 10) + '0';
		temp_num = temp_num / 10;
		length--;
	}
	while (temp_num > 0)
		;
	return (buffer);
}

/**
 * convert_string_to_int - converts a string to an integer.
 * @str: input string.
 * Return: integer.
 */
int convert_string_to_int(char *str)
{
	unsigned int index = 0, len = 0, output = 0, sign = 1, multiplier = 1, i;

	while (*(str + index) != '\0')
	{
		if (len > 0 && (*(str + index) < '0' || *(str + index) > '9'))
			break;

		if (*(str + index) == '-')
			sign *= -1;

		if ((*(str + index) >= '0') && (*(str + index) <= '9'))
		{
			if (len > 0)
				multiplier *= 10;
			len++;
		}
		index++;
	}

	for (i = index - len; i < index; i++)
	{
		output = output + ((*(str + i) - 48) * multiplier);
		multiplier /= 10;
	}
	return (output * sign);
}

