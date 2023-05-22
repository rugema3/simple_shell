#include "main.h"

/**
 * copy_memory - Copies information between void pointers.
 * @dest_ptr: Destination pointer.
 * @src_ptr: Source pointer.
 * @data_size: Size of the data to copy.
 *
 * Return: No return.
 */
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int data_size)
{
	char *source = (char *)src_ptr;
	char *destination = (char *)dest_ptr;
	unsigned int i;

	for (i = 0; i < data_size; i++)
		destination[i] = source[i];
}

/**
 * resize_memory - Reallocates a memory block.
 * @old_ptr: Pointer to the memory previously allocated.
 * @prev_size: Size, in bytes, of the allocated space of old_ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: old_ptr.
 * If new_size == prev_size, returns old_ptr without changes.
 * If malloc fails, returns NULL.
 */
void *resize_memory(void *old_ptr, unsigned int prev_size,
		unsigned int new_size)
{
	void *new_ptr;

	if (old_ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}

	if (new_size == prev_size)
		return (old_ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < prev_size)
		copy_memory(new_ptr, old_ptr, new_size);
	else
		copy_memory(new_ptr, old_ptr, prev_size);

	free(old_ptr);
	return (new_ptr);
}

/**
 * resize_double_ptr - Reallocates a memory block of a double pointer.
 * @old_ptr: Double pointer to the memory previously allocated.
 * @prev_size: Size, in bytes, of the allocated space of old_ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: old_ptr.
 * If new_size == prev_size, returns old_ptr without changes.
 * If malloc fails, returns NULL.
 */
char **resize_double_ptr(char **old_ptr, unsigned int prev_size,
		unsigned int new_size)
{
	char **new_ptr;
	unsigned int i;

	if (old_ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == prev_size)
		return (old_ptr);

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (i = 0; i < prev_size; i++)
		new_ptr[i] = old_ptr[i];

	free(old_ptr);

	return (new_ptr);
}
