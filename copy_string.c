#include"shell.h"

/**
 * copy_string - Copies the string pointed to by source.
 * @destination: Type char pointer the destination of the copied str
 * @source: Type char pointer the source of str
 * Return: the destination.
 */
char *copy_string(char *destination, char *source)
{
	size_t charIndex;

	for (charIndex = 0; source[charIndex] != '\0'; charIndex++)
	{
		destination[charIndex] = source[charIndex];
	}
	destination[charIndex] = '\0';

	return (destination);
}
