#include"shell.h"

/**
 * reverse_string - Reverses a string.
 * @str: A pointer to the character string to be reversed.
 */
void reverse_string(char *str)
{
	/**
	 *  Initialize a counter for the length of the string, as well as two indices
	 *  for later use in the swapping process
	 */
	int str_len = 0, idx, swap_idx;

	/**
	 *  A temporary character used for swapping, and a pointer that will be
	 *  used to traverse the string
	 */
	char *str_ptr, swap_char;

	/* Determine the length of the string */
	while (str_len >= 0)
	{
		/**
		 *  If we encounter the null-terminator, we break out of the loop,
		 *  effectively giving us the length of the string
		 */
		if (str[str_len] == '\0')
			break;
		str_len++;
	}
	/* Assign the original string pointer to our string pointer */
	str_ptr = str;
	/* Iterate through the string up to its length */
	for (idx = 0; idx < (str_len - 1); idx++)
	{
		/* In each iteration, perform another iteration through the string */
		for (swap_idx = idx + 1; swap_idx > 0; swap_idx--)
		{
			/* Swap the current character with the one before it */
			swap_char = *(str_ptr + swap_idx);
			*(str_ptr + swap_idx) = *(str_ptr + (swap_idx - 1));
			*(str_ptr + (swap_idx - 1)) = swap_char;
		}
	}
}

