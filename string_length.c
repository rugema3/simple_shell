#include"shell.h"
/**
 * prefix_length - gets the length of a prefix substring.
 * @str: initial segment.
 * @acceptedChars: accepted bytes.
 * Return: the number of accepted bytes.
 */
int prefix_length(char *str, char *acceptedChars)
{
	int strIndex, acceptIndex, flag;

	for (strIndex = 0; *(str + strIndex) != '\0'; strIndex++)
	{
		flag = 1;
		for (acceptIndex = 0; *(acceptedChars + acceptIndex) != '\0'; acceptIndex++)
		{
			if (*(str + strIndex) == *(acceptedChars + acceptIndex))
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	return (strIndex);
}
