#include "simple_shell.h"


/**
 * freeInfo - Free memory allocated for shell_info struct
 * @info: Pointer to shell_info struct.
 * @envOrnot: Flag to determine whether to free
 * environment-related/aliases data.
 *
 * Description: Frees memory allocated for the shell_info struct.
 *
 * Return: void
 */
void freeInfo(shell_info *info, int envOrnot){
	int i = 0;

	if (info->inputline != NULL)
		free_buffer((void **)&(info->inputline));
	if (info->cmds.commands != NULL)
	{
		for (i = 0; i < info->cmds.countOfCommands; i++)
		{
			if (info->cmds.commands[i] != NULL)
			{
				free_cmdInternals(info->cmds.commands[i]);
				free_buffer((void **)&(info->cmds.commands[i]));
				info->cmds.commands[i] = NULL;
			}
		}
		free_buffer((void**)&(info->cmds.commands));
	}
	if(envOrnot)
	{
		free_string_vector(&info->env);
		free_string_vector(&info->aliases);
	}
}

/**
 * clearInfo - Clear fields in the shell_info struct
 * @info: Pointer to shell_info struct.
 *
 * Description: Clears specific fields in the shell_info struct.
 *
 * Return: void
 */
void clearInfo(shell_info* info)
{
	info->inputlineSize = 0;
	info->currentCmd = NULL;
	info->cmds.countOfCommands = 1;/*assume 1 command*/
}
