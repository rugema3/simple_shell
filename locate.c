#include"main.h"

/**
 * locate_char - locates a character in a string,
 * @str: string.
 * @searchChar: character.
 * Return: the pointer to the first occurrence of the character searchChar.
 */
char *locate_char(char *str, char searchChar)
{
	unsigned int charIndex = 0;

	for (; *(str + charIndex) != '\0'; charIndex++)
		if (*(str + charIndex) == searchChar)
			return (str + charIndex);
	if (*(str + charIndex) == searchChar)
		return (str + charIndex);
	return ('\0');
} 
