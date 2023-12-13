#include "simple_shell.h"

/**
 * init - Initialize shell_info struct and
 * open input file if provided
 * @info: Pointer to shell_info struct.
 * @ac: Number of command line arguments.
 * @av: Array of command line arguments.
 *
 * Description: Initializes the shell_info struct,
 * opens the input file if
 * provided, and sets the shell program name.
 *
 * Return: 0 on success, EXIT_FAILURE on failure.
 */
int init(shell_info *info, int ac, char **av)
{
	int file_descriptor = STDIN_FILENO;

	if (ac == 2)
	{
		file_descriptor = open(av[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_no_such_file_error(av);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
	}
	initInfo(info);
	if (ac == 2)
		info->readStream_descriptor = file_descriptor;
	info->shellProgramName = av[0];
	return (0);
}

/**
 * initInfo - Initialize shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: Initializes fields in the shell_info struct and copies
 * environment variables to the 'env' vector.
 *
 * Return: void
 */
void initInfo(shell_info *info)
{

	extern char **environ;
	int envVarCount = 0;

	info->currentCmd = NULL;
	info->inputline = NULL;
	info->inputlineSize = 0;
	info->readStream_descriptor = STDIN_FILENO;
	info->shellProgramName = NULL;
	info->status = 0;
	info->lines_count = 0;
	info->isExit = 0;
	info->cmds.commands = NULL;
	info->cmds.countOfCommands = 0;

	initializeVector(&info->env, 100);
	while (environ[envVarCount] != NULL) {
		push_back(&info->env, environ[envVarCount]);
		envVarCount++;
	}
	initializeVector(&info->aliases, 100);
}


/**
 * initCurrentCmd - Initialize currentCmd in shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: Initializes the currentCmd field in the shell_info struct.
 *
 * Return: void
 */
void initCurrentCmd(shell_info *info)
{
	int i = 0;

	info->currentCmd = malloc(sizeof(Cmd));
	info->currentCmd->args = malloc((MAX_ARGS + 1) * sizeof(char *));
	for (i = 0; i <= MAX_ARGS; i++)
		info->currentCmd->args[i] = NULL;
	info->currentCmd->argsCount = 0;
	info->currentCmd->argsCountMax = 0;
}
/**
 * initCommands - Initialize commands in shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: Initializes the commands field in the shell_info struct.
 *
 * Return: void
 */
void initCommands(shell_info* info)
{
	int i = 0;

	info->cmds.commands = malloc(sizeof(Cmd*) * info->cmds.countOfCommands);
	for (; i < info->cmds.countOfCommands; i++)
		info->cmds.commands[i] = NULL;
}


