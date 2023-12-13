#include "simple_shell.h"

/**
 * freeDoubleCharArray - Free a double char array (array of strings)
 * @array: Double char array to free.
 *
 * Description: Frees each string in the double char array and then frees
 * the array itself.
 *
 * Return: void
 */
void freeDoubleCharArray(char** array)
{
	int i;

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}
	free(array);
}

/**
 * free_buffer - Free allocated buffer
 * @buffer: Pointer to the buffer to free.
 *
 * Description: Frees the allocated buffer and sets the buffer
 * pointer to NULL.
 *
 * Return: void
 */
void free_buffer(void **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}
/**
 * free_cmdInternals - Free memory allocated for command internals
 * @command: Pointer to the Cmd struct.
 *
 * Description: Frees memory allocated for the arguments in the Cmd struct.
 *
 * Return: void
 */
void free_cmdInternals(Cmd * command)
{
	int i;

	if (command->args != NULL)
	{
		for (i = 0; i < command->argsCountMax; i++)
		{
			if (command->args[i] != NULL)
			{
				free(command->args[i]);
				command->args[i] = NULL;
			}
		}
		free(command->args);
		command->args = NULL;
	}
}


/**
 * _realloc - Reallocate memory block
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Size of the old memory block.
 * @new_size: Size of the new memory block.
 *
 * Description: Reallocates a memory block. If @ptr is NULL, works like malloc.
 * If @new_size is 0, works like free. If reallocation fails, the original block
 * is unchanged.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
