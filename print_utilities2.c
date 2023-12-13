#include "simple_shell.h"

/**
 * print_no_such_file_error - Print  error message to STDERR
 * in case of ./hsh file.txt and file.txt is not found.
 * @av: Array of command-line arguments given to main function.
 *
 * Description: Prints an error message indicating that the specified file
 * cannot be opened.
 *
 * Return: void
 */
void print_no_such_file_error(char** av)
{
	_putstr(av[0], STDERR_FILENO);
	_putstr(": 0: Can't open ", STDERR_FILENO);
	_putstr(av[1], STDERR_FILENO);
	/*_putstr(": No such file", STDERR_FILENO);*/
	_putchar('\n', STDERR_FILENO);
	_putchar(FLUSH_FLAG, STDERR_FILENO);
}

/**
 * print_error - Print error message to STDERR
 * @info: Pointer to shell_info struct.
 * @message: Error string.
 *
 * Description: Prints an error message to STDERR, including information
 * from the shell_info struct.
 *
 * Return: void
 */
void print_error(shell_info *info, char *message)
{
	char str[50];

	transferIntToBuffer(str, info->lines_count);
	_putstr(info->shellProgramName, STDERR_FILENO);
	_putstr(": ", STDERR_FILENO);
	_putstr(str, STDERR_FILENO);
	_putstr(": ", STDERR_FILENO);
	_putstr(info->currentCmd->args[0], STDERR_FILENO);
	_putstr(": ", STDERR_FILENO);
	_putstr(message, STDERR_FILENO);
}

/**
 * print_one_alias - Print a single alias to the specified stream
 * @alias: Alias string.
 * @value: Alias value string.
 * @stream: File descriptor to write to.
 *
 * Description: Prints a single alias in the format "alias='value'\n"
 * to the specified file descriptor.
 *
 * Return: void
 */
void print_one_alias(const char * alias, const char *value, int stream)
{
	_putstr(alias, stream);
	_putchar('=', stream);
	_putchar('\'', stream);
	_putstr(value,  stream);
	_putstr("'\n", stream);
}


/**
 * print_env - Print environment variables to STDOUT
 * @vector: Pointer to StringVector.
 *
 * Description: Prints environment variables to STDOUT from the given
 * StringVector.
 *
 * Return: void
 */
void print_env(const StringVector* vector)
{
	size_t i;

	for (i = 0; i < vector->size; ++i)
	{
		if (vector->take_data[i])
		{
			_putstr(vector->data[i], STDOUT_FILENO);
			_putchar('\n', STDOUT_FILENO);
	        }
	}
	_putchar(FLUSH_FLAG, STDOUT_FILENO);
}

/**
 * print_alias - Print aliases to STDOUT
 * @vector: Pointer to StringVector.
 *
 * Description: Prints aliases to STDOUT from the given StringVector.
 *
 * Return: void
 */
void print_alias(const StringVector* vector)
{
	size_t i;
	const char* ptr;

	for (i = 0; i < vector->size; ++i)
	{
		if (vector->take_data[i])
		{

			for (ptr = vector->data[i]; *ptr != '='; ptr++)
				_putchar(*ptr, STDOUT_FILENO);
			_putchar('=', STDOUT_FILENO);
			_putchar('\'', STDOUT_FILENO);
			_putstr((char*)(ptr + 1),STDOUT_FILENO);
			_putstr("'\n", STDOUT_FILENO);
		}
	}
	_putchar(FLUSH_FLAG, STDOUT_FILENO);
}
