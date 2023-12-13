#include "simple_shell.h"

/**
 * remove_comments - skips comments from inputline in shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: skips comments from the 'inputline' field
 * in the shell_info struct.
 *
 * Return: void
 */
void remove_comments(shell_info *info)
{
	size_t j = 0;

	for (j = 0; j < info->inputlineSize; j++)
		if (info->inputline[j] == '#' && (!j || info->inputline[j - 1] == ' '))
		{
			info->inputline[j] = '\0';
			break;
		}
	info->inputlineSize = j;
}


/**
 * adjustChain - Adjust command chain(complex command)
 * in shell_info struct based on inputline
 * @info: Pointer to shell_info struct.
 *
 * Description: Adjusts the 'separators' and 'countOfCommands' fields in the
 * shell_info struct based on the 'inputline'.
 *
 * Return: void
 */
void adjustChain(shell_info *info)
{
	size_t i = 0;

	for (i = 0; i < info->inputlineSize; i++)
	{
		if (info->inputline[i] == ';')
		{
			info->cmds.seperators[info->cmds.countOfCommands - 1] = ';';
			info->cmds.countOfCommands++;
		}
		else if (info->inputline[i] == '|' && info->inputline[i + 1] == '|')
		{
			info->cmds.seperators[info->cmds.countOfCommands - 1] = '|';
			info->cmds.countOfCommands++;
			i++;
		}
		else if (info->inputline[i] == '&' && info->inputline[i + 1] == '&')
		{
			info->cmds.seperators[info->cmds.countOfCommands - 1] = '&';
			info->cmds.countOfCommands++;
			i++;
		}
	}
}




/**
 * replace_alias - Replace command with its alias in shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: Replaces the command with its alias in the 'currentCmd' field
 * of the shell_info struct.
 *
 * Return: void
 */
void replace_alias(shell_info *info)
{

	char *tmp, *beforeTmp;

	beforeTmp = tmp = getInStringVector(&info->aliases,
						info->currentCmd->args[0]);
	while (tmp != NULL)
	{
		beforeTmp = tmp;
		tmp = getInStringVector(&info->aliases, tmp);
	}
	if (beforeTmp != NULL)
	{
		free(info->currentCmd->args[0]);
		info->currentCmd->args[0] = _strdup(beforeTmp);
	}
}

/**
 * replace_vars - Replace variables in command args
 * with their values in shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: Replaces variables in the args of
 * 'currentCmd' field of the shell_info
 * struct with their values from the 'env' field.
 *
 * Return: void
 */
void replace_vars(shell_info *info)
{
	int i = 0;
	char str[100];
	char *temp;

	for (i = 0; i < info->currentCmd->argsCount; i++)
	{
		if (info->currentCmd->args[i][0] != '$'
				|| info->currentCmd->args[i][1] == '\0')
			continue;
		if (_strcmp(info->currentCmd->args[i], "$?") == 0)
		{
			transferIntToBuffer(str, info->status);
			free(info->currentCmd->args[i]);
			info->currentCmd->args[i] = _strdup(str);
		}
		else if (_strcmp(info->currentCmd->args[i], "$$") == 0)
		{
			transferIntToBuffer(str, getpid());
			free(info->currentCmd->args[i]);
			info->currentCmd->args[i] = _strdup(str);
		}
		else
		{
			temp = getInStringVector(&info->env, &info->currentCmd->args[i][1]);
			if (temp == NULL)
			{
				free(info->currentCmd->args[i]);
				info->currentCmd->args[i] = _strdup("");
			}
			else
			{
				free(info->currentCmd->args[i]);
				info->currentCmd->args[i] = _strdup(temp);
			}
		}
	}
}



/**
 * adjustPath - Adjust the command path by
 * searching directories in the PATH variable.
 *
 * @info: Pointer to shell_info struct.
 *
 * Searches directories in the PATH variable to find the executable file
 * specified in the 'currentCmd' field of the shell_info struct.
 *
 * Return: 1 if the executable is found and the path is adjusted, 0 otherwise.
 */

int adjustPath(shell_info *info)
{
	int len = _strlen(info->currentCmd->args[0]);
	char *tmpCommandStr = malloc(len + 1);
	char *path = _strdup(getenv("PATH"));
	char *token = tokenize(path, ":");
	char *newPath;
	int newPathLen;

	_strcpy(tmpCommandStr, info->currentCmd->args[0]);
	while (token != NULL)
	{
		newPathLen = _strlen(token) + 1 + len + 1;
		newPath = malloc(newPathLen);
		if (newPath != NULL)
		{
			_strcpy(newPath, token);
			_strcat(newPath, "/");
			_strcat(newPath, tmpCommandStr);
			if (executableFile(newPath))
			{
				free(path);
				free(tmpCommandStr);
				free(info->currentCmd->args[0]); /* Free the old memory */
				info->currentCmd->args[0] = newPath;
				return (1);
			}
		free(newPath);
		}
		token = tokenize(NULL, ":");
	}
	free(path);
	free(tmpCommandStr);
	return (0);
}
