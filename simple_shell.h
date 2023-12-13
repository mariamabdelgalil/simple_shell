#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#define BUFFER_SIZE 2048
#define FLUSH_FLAG -1
#define MAX_ARGS 100
extern char **environ;
/**
 * struct StringVector - Structure representing a dynamic array of strings
 * @data:       Pointer to the array of strings.
 * @take_data:  Array indicating whether each element should be used or not.
 * @size:       Current number of elements in the vector.
 * @capacity:   Maximum number of elements the vector can hold without resizing.
 *
 * Description:
 *     This structure represents a dynamic array (vector) designed to hold an
 *     array of strings. It includes pointers to the string data, an array
 *     indicating whether each element should be used or not, the current size,
 *     and the capacity of the vector.
 */
typedef struct StringVector
{
	char** data;
	int* take_data;
	size_t size;
	size_t capacity;
} StringVector;
/**
 * struct SimpleCommand - Structure representing a simple command
 * @argsCount:       Number of arguments in the command.
 * @argsCountMax:    Maximum number of arguments needed to be deallocated afterwards.
 *                   (This helps in managing memory efficiently.)
 * @args:            Pointer to the array of command arguments.
 *
 * Description:
 *     This structure represents a simple command and includes information
 *     such as the number of arguments, the maximum number of arguments needed
 *     for deallocation, and a pointer to the array of command arguments.
 */
typedef struct SimpleCommand {
	int argsCount;
	int argsCountMax;
	char** args;
} Cmd;

/**
 * struct ComplexCommand - Structure representing a complex command
 * @commands:          Pointer to an array of simple commands.
 * @seperators:        Array of separators between commands (limited to 100 characters).
 * @countOfCommands:   Number of simple commands in the complex command.
 *
 * Description:
 *     This structure represents a complex command, consisting of an array of
 *     simple commands, an array of separators between commands, and the
 *     total count of simple commands in the complex command.
 */
typedef struct ComplexCommand {
	Cmd** commands;
	char seperators[100];/*assume 101 commands is the limit for now*/
	int countOfCommands;
} CmdArr;

/**
 * struct Info - Structure representing shell information
 * @env:                  Vector of strings representing environment variables.
 * @aliases:              Vector of strings representing shell aliases.
 * @inputline:            Pointer to the input line buffer.
 * @inputlineSize:        Size of the input line buffer.
 * @readStream_descriptor: File descriptor for reading input.
 * @shellProgramName:     Pointer to the shell program name.
 * @currentCmd:           Pointer to the current command (path).
 * @cmds:                 Structure representing a complex command.
 * @status:               Status code of the shell.
 * @lines_count:          Number of lines processed by the shell.
 * @isExit:               Flag indicating whether the shell should exit or not.
 * @exitNum:              Exit number for the shell.
 *
 * Description:
 *     This structure represents runtime information about a shell, including
 *     environment variables, aliases, input line buffer, file descriptor for
 *     reading input, shell program name, current command, complex command
 *     structure, status code, number of lines processed, and exit-related flags.
 */
typedef struct Info
{
	StringVector env;
	StringVector aliases;
	char *inputline;
	size_t inputlineSize;
	int readStream_descriptor;
	char *shellProgramName;
	Cmd *currentCmd;
	CmdArr cmds;
	int status;
	unsigned int lines_count;
	int isExit;
	int exitNum;
} shell_info;


/* String utils to deal with strings */
/*string_utils.c*/
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, int n);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, const char *src, int n);
int _strcmp(const char *s1, const char *s2);

/*string_utils2.c*/
int _strlen(const char *in);
size_t _strspn(const char *s, const char *accept);
size_t _strcspn(const char *str, const char *reject);

/*string_utils3.c*/
char *_strchr(char *s, char c);
char *_strdup(const char *str);
char *find_substring_start(const char *full_string, const char *substring);
char *tokenize(char *str, const char *delim);
/**************************************************************************/

/* String Vector utilities to deal with string vector*/
/*vector.c*/
void initializeVector(StringVector* vector, size_t capacity);
void push_back(StringVector* vector, const char* value);
void free_string_vector(StringVector* vector);

/*vector2.c*/
char** getDuplicateOfData(const StringVector* vector);
void unsetInStringVector(StringVector* vector, char *var);
void setInStringVector(StringVector* vector, char *var, char *value);
char* getInStringVector(StringVector* vector, char *var);
/**************************************************************************/

/* utilities to print to different streams */
/*print_utilities.c*/
void _putchar(const char c, int fileDescriptor);
void _putstr(const char *str, int fileDescriptor);
void display_prompt(int ac);
void print_dir(const char* dir, int fileDescriptor);


/*print_utilities2.c*/
void print_no_such_file_error(char** av);
void print_error(shell_info *info, char *message);
void print_one_alias(const char * alias, const char *value, int stream);
void print_env(const StringVector* vector);
void print_alias(const StringVector* vector);
/**************************************************************************/

/* module to handle freeing memory for complex data*/
/* memory_management_module.c */
void free_buffer(void **buffer);
void free_cmdInternals(Cmd * command);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void freeDoubleCharArray(char** array);
/**************************************************************************/

/* module to handle initializing and clearing of shell runtime information*/
/* information_handling_module.c */
int init(shell_info *info, int ac, char **av);
void initInfo(shell_info *info);
void initCurrentCmd(shell_info *info);
void initCommands(shell_info* info);

/*information_handling_module2.c*/
void freeInfo(shell_info *info, int envOrnot);
void clearInfo(shell_info* info);
/**************************************************************************/

/* module to help parser/executor adjust data before operating on it*/
/*fine_tune_module.c*/
/*in parsing*/
void remove_comments(shell_info* info);
void adjustChain(shell_info *info);
/*in execution*/
void replace_vars(shell_info* info);
void replace_alias(shell_info* info);
int adjustPath(shell_info *info);
/**************************************************************************/
/* other helper functions */

int executableFile(char *filePath);
void transferIntToBuffer(char *buffer, int value);
int isValidExit(char *s);
/**************************************************************************/

/*builtin_commands.c*/
void executeExit(shell_info *info);
void executeUnSetEnv(shell_info *info);
void executeSetEnv(shell_info *info);
void executeCD(shell_info*);
void executeAlias(shell_info *info);
/**************************************************************************/

/* EXECUTION UNIT*/
/* execution_module.c */
void executeCurrentCommand(shell_info * info);
int executeBuiltIn(shell_info * info);
void execute(shell_info *info);
/**************************************************************************/

/*PARSER UNIT + READER UNIT*/
/* parser_module.c */
void parseCommandInput(shell_info *info, int commandIdx, char *inputline);
void parseInput(shell_info *info);
/* read_module */
int readInput(shell_info *info);
ssize_t readline(char **lineptr, size_t *n, int stream);
void handleCtrlCSlot(int signum);
#endif /* SIMPLE_SHELL_H */
