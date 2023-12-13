#include "simple_shell.h"

/**
 * executeExit - Execute the builtin exit command.
 * @info: Pointer to the shell_info struct.
 *
 * Return: void.
 */
void executeExit(shell_info *info)
{
	int exitNumber;

	info->exitNum = 0;
	if (info->currentCmd->args[1])
	{
		exitNumber = isValidExit(info->currentCmd->args[1]);
		if (exitNumber < 0)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_putstr(info->currentCmd->args[1], STDERR_FILENO);
			_putchar('\n', STDERR_FILENO);
		}
		else
		{
			info->isExit = 1;
			info->exitNum = exitNumber;
		}
	}
	else
	{
		info->isExit = 1;
	}
}


/**
 * executeUnSetEnv - Execute the unsetenv command.
 * @info: Pointer to the shell_info struct.
 *
 * Description:
 * Unsets environment variables specified in the command arguments.
 * Displays an error if too few arguments are provided.
 * Return: void.
 */
void executeUnSetEnv(shell_info *info)
{
	int i = 1;

	if (info->currentCmd->argsCount == 1)
	{
		_putstr("Too few arguements.\n", STDERR_FILENO);
		_putchar(FLUSH_FLAG, STDERR_FILENO);
	}
	else
	{
		for (i = 1; i < info->currentCmd->argsCount; i++)
		{
			unsetInStringVector(&info->env,info->currentCmd->args[i]);
		}
	}
}

/**
 * executeSetEnv - Execute the setenv command.
 * @info: Pointer to the shell_info struct.
 * Description:
 * Sets an environment variable to a specified value.
 * Displays an error if an incorrect number of arguments is provided.
 * Return: void.
 */
void executeSetEnv(shell_info *info)
{
	if (info->currentCmd->argsCount != 3)
	{
		_putstr("Incorrect number of arguements\n", STDERR_FILENO);
		_putchar(FLUSH_FLAG, STDERR_FILENO);
		return;
	}
	setInStringVector(&info->env, info->currentCmd->args[1], info->currentCmd->args[2]);
}
/**
 * executeCD - Change the current working directory based on command arguments.
 * @info: Pointer to shell_info struct.
 *
 * Description: Changes the working directory based on the provided command
 * arguments. Handles scenarios such as changing to the home directory, the
 * previous working directory, or a specified directory path.
 *
 * Return: void
 */
void executeCD(shell_info *info)
{
	char *currentDir, *GoToDir, currentDirBuffer[BUFFER_SIZE];
	int cd_out;

	currentDir = getcwd(currentDirBuffer, BUFFER_SIZE);
	if (!info->currentCmd->args[1])
	{
		GoToDir = getInStringVector(&info->env, "HOME");
		if (GoToDir == NULL)
		{
			GoToDir = getInStringVector(&info->env, "PWD");
			if(GoToDir == NULL)
				GoToDir = "/";
		}
		cd_out = chdir(GoToDir);
	}
	else if (_strcmp(info->currentCmd->args[1], "-") == 0)
	{
		GoToDir = getInStringVector(&info->env, "OLDPWD");
		if (GoToDir == NULL)
		{
			print_dir(currentDir, STDOUT_FILENO);
			return;
		}
		print_dir(GoToDir, STDOUT_FILENO);
		cd_out = chdir(GoToDir);
	}
	else
		cd_out = chdir(info->currentCmd->args[1]);
	if (cd_out == -1)
	{
		print_error(info, "can't cd to ");
		print_dir(info->currentCmd->args[1], STDERR_FILENO);
		info->status = 2;
	}
	else
	{
		setInStringVector(&info->env, "OLDPWD", getInStringVector(&info->env, "PWD"));
		setInStringVector(&info->env, "PWD", getcwd(currentDirBuffer, BUFFER_SIZE));
	}
}

/**
 * executeAlias - Manage shell aliases based on command arguments.
 * @info: Pointer to shell_info struct.
 *
 * Description: Handles the creation and display of shell aliases. When provided
 * with alias names and values, it creates new aliases. If only alias names are
 * provided, it displays the corresponding alias values.
 *
 * Return: void
 */
void executeAlias(shell_info *info)
{
	int i;
	char* tmp;
	char alias[BUFFER_SIZE], aliasValue[BUFFER_SIZE];
	size_t aliasLen;

	if (info->currentCmd->argsCount == 1)
	{
		print_alias(&info->aliases);
		return;
	}
	else
	{
		for (i = 1; i < info->currentCmd->argsCount; i++)
		{
			tmp = _strchr(info->currentCmd->args[i], '=');
			if (tmp != NULL)
			{
				aliasLen = tmp - info->currentCmd->args[i];
				_strncpy(alias, info->currentCmd->args[i], aliasLen);
				alias[aliasLen] = '\0';
				_strcpy(aliasValue, tmp + 1);
				setInStringVector(&info->aliases, alias, aliasValue);
			}
			else
			{
				tmp = getInStringVector(&info->aliases, info->currentCmd->args[i]);
				if (tmp != NULL)
				{
					print_one_alias(info->currentCmd->args[i], tmp, STDOUT_FILENO);
				}
			}
		}
		_putchar(FLUSH_FLAG, STDOUT_FILENO);
	}
}
