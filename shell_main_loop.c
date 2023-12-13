#include "simple_shell.h"
/**
 * main - Entry point for the simple shell program.
 * @ac: Number of command-line arguments.
 * @av: Array of command-line argument strings.
 *
 * Description: The main function initializes the shell, enters a loop to
 * read and execute commands until an exit condition is met, and then frees
 * allocated resources before exiting. It also handles displaying prompts,
 * reading user input, parsing commands, and executing them using the
 * provided functions and structures.
 *
 * Return: 0 on successful execution, or an exit status in case of an error.
 */
int main(int ac, char **av)
{
	int read = 0;
	shell_info shellInfo;

	if (init(&shellInfo, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (read != -1 && shellInfo.isExit == 0)
	{
		clearInfo(&shellInfo);
		display_prompt(ac);
		/* readInput */
		read = readInput(&shellInfo);
		if (read == -1)
		{
			if (shellInfo.status == 0)
				_putchar(FLUSH_FLAG, STDOUT_FILENO);
			else
				_putchar(FLUSH_FLAG, STDERR_FILENO);
			break;
		}
		parseInput(&shellInfo);

		execute(&shellInfo);
		freeInfo(&shellInfo, 0);
	}
	freeInfo(&shellInfo, 1);
	if (!isatty(STDIN_FILENO) && shellInfo.status)
		exit(shellInfo.status);
	if (shellInfo.isExit)
	{
		if (shellInfo.status)
			exit(shellInfo.status);
		else
			exit(shellInfo.exitNum);
	}
	return (0);
}
