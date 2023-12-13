#include "simple_shell.h"

/**
 * transferIntToBuffer - Convert an integer to a string buffer.
 * @buffer: Destination buffer to store the string representation.
 * @value: Integer value to be converted.
 *
 * Description:
 * Converts an integer to its string representation
 * and stores it in the buffer.
 *
 * Return: void
 */
void transferIntToBuffer(char *buffer, int value)
{

	int index = 0;
	int i, j, digit;
	char tmp;

	while (value != 0)
	{
		digit = value % 10;
		buffer[index++] = digit + '0';
		value /= 10;
	}

	if (index == 0)
	{
		buffer[index++] = '0';
	}

	buffer[index] = '\0';

	for (i = 0, j = index - 1; i < j; ++i, --j)
	{
		tmp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = tmp;
	}
}

/**
 * executableFile - Check if a file is executable.
 * @filePath: Path to the file.
 *
 * Description: Checks if the file at the specified path is executable.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int executableFile(char *filePath)
{
	int file = filePath && ((filePath[0] == '/')
					|| (filePath[0] == '.' && filePath[1] == '/')
						|| (filePath[0] == '.' && filePath[1] == '.' && filePath[2] == '/'));
	return (file && access(filePath, X_OK) == 0);
}

/**
 * isValidExit - Check if a string represents a valid exit code.
 * @s: String to check.
 *
 * Description:
 * Checks if the provided string represents a valid exit code.
 * Returns the exit code if valid, or -100 if not.
 *
 * Return: Exit code if valid, -100 otherwise.
 */
int isValidExit(char *s)
{

	unsigned long int res = 0;

	if (*s == '+')
		s++;
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + (*s - 48);
		else
			return (-100);
		if (res > INT_MAX)
			return (-100);
		s++;
	}
	return (res);
}
