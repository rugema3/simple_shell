#include"shell.h"
/**
 * compare_strings - Function that compares two strings.
 * @str1: type str compared
 * @str2: type str compared
 * Return: Always 0.
 */
int compare_strings(char *str1, char *str2)
{
	int charIndex;

	for (charIndex = 0; str1[charIndex] == str2[charIndex]
			&& str1[charIndex]; charIndex++)
		;

	if (str1[charIndex] > str2[charIndex])
		return (1);
	if (str1[charIndex] < str2[charIndex])
		return (-1);
	return (0);
}
