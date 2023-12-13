#include "simple_shell.h"

/**
 * readline - Read a line from a stream.
 * @lineptr: Pointer to the buffer where the line will be stored.
 * @n: Pointer to the size of the buffer.
 * @stream: File descriptor for the stream to read from.
 *
 * Description: Reads a line from the specified stream into the buffer pointed
 * to by lineptr. If lineptr is NULL or n is 0, a new buffer is allocated.
 * The buffer is reallocated if its size is not sufficient.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t readline(char **lineptr, size_t *n, int stream) {
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index = 0, buffer_size = 0;
	size_t size = 0, old_size;
	char c;
	size_t i;

	if (!lineptr || !n)
		return -1;

	if (*lineptr == NULL || *n == 0)
	{
		*n = 256;
		*lineptr = (char *)malloc(*n);
		for(i = 0; i < *n; i++)
			(*lineptr)[i] = '\0';
	}
	while (1)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(stream, buffer, BUFFER_SIZE);
			if (buffer_size <= 0)
			{
				break;
			}
		buffer_index = 0;
		}
		c = buffer[buffer_index++];
		if (size + 1 >= *n)
		{
			old_size = *n;
			*n *= 2;
			*lineptr= (char *)_realloc(*lineptr, old_size, *n);
			for(i = old_size; i < *n; i++)
				(*lineptr)[i] = '\0';
		}
		(*lineptr)[size++] = c;

		if (c == '\n' || c == EOF)
		{
			break;
		}
	}
	if (size == 0 || c == EOF)
		return -1;
	(*lineptr)[size] = '\0';
	*n = size;
	return size;
}

/**
 * handleCtrlCSlot - Handle the Ctrl-C signal (SIGINT).
 * @signum: Signal number.
 *
 * Description: Handles the Ctrl-C signal by printing a newline character and
 * displaying the shell prompt.
 *
 * Return: void
 */

void handleCtrlCSlot(int signum)
{
	signum = signum;
	_putchar('\n', STDOUT_FILENO);
	display_prompt(1);/*it's interactive mode*/
}

/**
 * readInput - Read input from the user.
 * @info: Pointer to shell_info struct.
 *
 * Description: Reads input from the specified stream descriptor and handles
 * the SIGINT signal to interrupt the input process.
 *
 * Return: The result of the readline function.
 */

int readInput(shell_info *info)
{
	signal(SIGINT, handleCtrlCSlot);
	return readline(&info->inputline, &info->inputlineSize, info->readStream_descriptor);
}
