#include "simple_shell.h"

/**
 * parseCommandInput - Parse command input and store it in the shell_info.
 * @info: Pointer to shell_info struct.
 * @commandIdx: Index of the command in the shell_info struct.
 * @inputline: Command input string.
 *
 * Description: Tokenizes the input line, initializes the current command, and
 * stores the parsed arguments in the 'currentCmd' field of the shell_info.
 * then store command in cmds.
 * Return: void
 */
void parseCommandInput(shell_info *info, int commandIdx, char *inputline)
{
	char *token;
	int index = 0, len = 0;

	len = _strlen(inputline);
	if (len && inputline[len - 1] == '\n')
		inputline[len - 1] = '\0';
	token = tokenize(inputline, " ");
	if (token != NULL)
		initCurrentCmd(info);
	while (token != NULL)
	{
		if (info->currentCmd->args[index] != NULL)
		{
			free(info->currentCmd->args[index]);
			info->currentCmd->args[index] = _strdup(token);
		}
		else
		{
			info->currentCmd->args[index] = _strdup(token);
		}
		if (info->currentCmd->args[index] == NULL)
		{
			exit(EXIT_FAILURE);
		}
		token = tokenize(NULL, " ");
		index++;
	}
	if (info->currentCmd != NULL)
	{
		info->currentCmd->argsCount = index;
		if (info->currentCmd->argsCount > info->currentCmd->argsCountMax)
			info->currentCmd->argsCountMax = info->currentCmd->argsCount;
		if (info->currentCmd->args != NULL)
			info->currentCmd->args[index] = NULL;
	}
	info->cmds.commands[commandIdx] = info->currentCmd;
	info->currentCmd = NULL;
}


/**
 * parseInput - Parse the input line and store commands in the shell_info.
 * @info: Pointer to shell_info struct.
 *
 * Description: Removes comments, adjusts command chain, initializes commands,
 * and parses the input line to store commands in the 'cmds'
 * field of the shell_info.
 *
 * Return: void
 */

void parseInput(shell_info *info)
{
	char *temp, *tokens[100];
	int tokenIdx = 0;

	remove_comments(info);
	info->cmds.countOfCommands = 1;
	adjustChain(info);
	initCommands(info);
	if (info->cmds.countOfCommands == 1)
		parseCommandInput(info, 0, info->inputline);
	else
	{
		temp = _strdup(info->inputline);
		tokens[tokenIdx] = tokenize(temp, ";&&||");
		while (tokens[tokenIdx] != NULL)
		{
			tokenIdx++;
			tokens[tokenIdx] = tokenize(NULL, ";&&||");
		}
		tokenIdx = 0;
		while (tokens[tokenIdx])
		{
			parseCommandInput(info, tokenIdx, tokens[tokenIdx]);
			tokenIdx++;
		}
		free(temp);
	}

}


