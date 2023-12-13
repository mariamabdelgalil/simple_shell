#include "simple_shell.h"
/**
 * execute - Execute shell commands based on shell_info struct.
 * @info: Pointer to shell_info struct.
 *
 * Description: Iterates through the command list in the shell_info struct,
 * executes each command, and handles command separators.
 *
 * Return: void
 */

void execute(shell_info *info)
{
	int i;

	info->lines_count++;
	for(i = 0; i < info->cmds.countOfCommands && !info->isExit; i++)
	{
		info->currentCmd = info->cmds.commands[i];
		if (i == 0 || info->cmds.seperators[i-1] == ';')
			executeCurrentCommand(info);
		else if (info->cmds.seperators[i-1]=='&' && info->status == 0)
			executeCurrentCommand(info);
		else if (info->cmds.seperators[i-1]=='|' && info->status != 0)
			executeCurrentCommand(info);
	}
}

/**
 * executeBuiltIn - Execute built-in shell commands.
 * @info: Pointer to shell_info struct.
 *
 * Description: Checks for and executes built-in commands like exit, env, unsetenv,
 * setenv, cd, and alias based on the first arg of currentCmd
 * field of the shell_info struct.
 *
 * Return: 0 if a built-in command is executed, -1 otherwise.
 */

int executeBuiltIn(shell_info * info)
{

	if (_strcmp(info->currentCmd->args[0], "exit") == 0)
	{
		executeExit(info);
		return (0);
	}
	if (_strcmp(info->currentCmd->args[0], "env") == 0)
	{
		print_env(&info->env);
		return (0);
	}
	if (_strcmp(info->currentCmd->args[0], "unsetenv") == 0)
	{
		executeUnSetEnv(info);
		return (0);
	}
	if (_strcmp(info->currentCmd->args[0], "setenv") == 0)
	{
		executeSetEnv(info);
		return (0);
	}
	if (_strcmp(info->currentCmd->args[0], "cd") == 0)
	{
		executeCD(info);
		return (0);
	}
	if (_strcmp(info->currentCmd->args[0], "alias") == 0)
	{
		executeAlias(info);
		return (0);
	}
	return (-1);
}


/**
 * executeCurrentCommand - Execute the current command in the shell_info struct.
 * @info: Pointer to shell_info struct.
 * Description: Executes the command in the 'currentCmd' field of the shell_info struct.
 *
 * Return: void
 */

void executeCurrentCommand(shell_info * info)
{
	pid_t child_pid;
	int adjust = 0;
	const char *pathValue = getenv("PATH");
	char** envVars;

	if (info->currentCmd == NULL || info->currentCmd->args == NULL
					|| info->currentCmd->args[0] == NULL)
	return;
	replace_alias(info);
	replace_vars(info);
	if (executeBuiltIn(info) == 0)
		return;
	if (!executableFile(info->currentCmd->args[0]))
	{
		if (pathValue != NULL && _strcmp(pathValue, "") != 0)
			adjust = adjustPath(info);
		if (!adjust)
		{
			print_error(info, "not found\n");
			info->status = 127;
			_putchar(FLUSH_FLAG, STDERR_FILENO);
			return;
		}
	}
	envVars = getDuplicateOfData(&info->env);
	child_pid = fork();
	if (child_pid == -1)
		exit(EXIT_FAILURE);
	if (child_pid == 0)
	{
		execve(info->currentCmd->args[0], info->currentCmd->args, envVars);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, &info->status, 0);
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
		}
		freeDoubleCharArray(envVars);
	}
}
