#include "main.h"

/**
 * concatenate_strings - concatenate two strings
 * @destination: char pointer the destination of the copied str
 * @source: const char pointer the source of str
 * Return: the destination
 */
char *concatenate_strings(char *destination, const char *source)
{
	int destIndex;
	int srcIndex;

	for (destIndex = 0; destination[destIndex] != '\0'; destIndex++)
		;

	for (srcIndex = 0; source[srcIndex] != '\0'; srcIndex++)
	{
		destination[destIndex] = source[srcIndex];
		destIndex++;
	}

	destination[destIndex] = '\0';
	return (destination);
} 
