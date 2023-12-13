#include "simple_shell.h"


/**
 * _putchar - Write a character to a file descriptor.
 * @c: Character to write.
 * @fileDescriptor: File descriptor to write to.
 *
 * Description: Writes the character @c to the given file descriptor,
 * buffering output and flushing when necessary.
 *
 * Return: void
 */
void _putchar(const char c, int fileDescriptor)
{
	static int idxInBuffer;
	static char buffer[BUFFER_SIZE];

	if (c == FLUSH_FLAG || idxInBuffer >= BUFFER_SIZE)
	{
		write(fileDescriptor, buffer, idxInBuffer);
		idxInBuffer = 0;
	}
	if (c != FLUSH_FLAG)
		buffer[idxInBuffer++] = c;
}
/**
 * _putstr - Write a string to a file descriptor
 * @str: String to write.
 * @fileDescriptor: File descriptor to write to.
 *
 * Description: Writes the string @str to the given file descriptor.
 *
 * Return: void
 */
void _putstr(const char *str, int fileDescriptor)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i], fileDescriptor);
		i++;
	}
}

/**
 * display_prompt - Display shell prompt if input is connected to terminal
 * @ac: Argument count given to main program to detect non-interactive mode.
 *
 * Description: Displays the shell prompt if input is from the terminal.
 *
 * Return: void
 */
void display_prompt(int ac)
{
	/* input is connected to terminal */
	if (isatty(STDIN_FILENO) && ac != 2)
	{
		_putstr("#cisfun$ ", STDOUT_FILENO);
		_putchar(FLUSH_FLAG, STDOUT_FILENO);
	}
}
/**
 * print_dir - Print directory followed by a newline
 * @dir: Directory string to print.
 * @fileDescriptor: File descriptor to write to.
 *
 * Description: Prints the directory @dir followed by a newline.
 *
 * Return: void
 */
void print_dir(const char *dir, int fileDescriptor)

{
	_putstr(dir, fileDescriptor);
	_putchar('\n', fileDescriptor);
	_putchar(FLUSH_FLAG, fileDescriptor);
}
