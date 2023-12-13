#include "simple_shell.h"

/**
 * _strchr - Locate the first occurrence of a character in a string
 * @s: String to search.
 * @c: Character to locate.
 *
 * Description: Returns a pointer to the first occurrence of
 * the character @c
 * in the string @s, or NULL if not found.
 *
 * Return: Pointer to @c in @s or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (&s[i]);
		}
		i++;
	}
	if (s[i] == c)
	{
		return (&s[i]);
	}
	return (NULL);
}

/**
 * _strdup - Duplicate a string
 * @str: String to duplicate.
 *
 * Description: Returns a pointer to a newly allocated space
 * in memory containing
 * a copy of the string @str, or NULL if memory allocation fails.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */
char *_strdup(const char *str)
{
	char *array;
	unsigned int i = 0;
	unsigned int size;

	if (str == NULL)
		return (NULL);
	size = _strlen(str);
	array = (char *) malloc(sizeof(char) * (size + 1));
	if (array == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		array[i] = str[i];
	}
	array[i] = '\0';
	return (array);
}

/**
 * find_substring_start - Find the starting position of a substring in a string
 * @full_string: Full string.
 * @substring: Substring to find.
 *
 * Description: Returns the starting position of @substring in @full_string,
 * or NULL if not found.
 *
 * Return: Pointer to @substring start or NULL if not found.
 */
char *find_substring_start(const char *full_string, const char *substring)
{
	for (; *substring != '\0'; substring++, full_string++)
		if (*substring != *full_string)
			return (NULL);
	return ((char *)full_string);
}

/**
 * tokenize - Tokenize a string using a delimiter
 * @str: String to tokenize.
 * @delim: Delimiter used for tokenization.
 *
 * Description:
 *     Tokenizes the string @str using the specified delimiter @delim.
 *     Maintains state between calls to continue tokenization.
 *
 * Return:
 *     Pointer to the next token, or NULL if no more tokens are present.
 */
char *tokenize(char *str, const char *delim)
{
	static char *lastToken;
	char *tokenStart, *tokenEnd;

	if (str != NULL)
	{
		lastToken = str;
	}
	else
	{
		if (lastToken == NULL)
			return (NULL);
	}
	tokenStart = lastToken + _strspn(lastToken, delim);
	if (*tokenStart == '\0')
	{
		lastToken = NULL;
		return (NULL);
	}
	tokenEnd = tokenStart + _strcspn(tokenStart, delim);
	if (*tokenEnd != '\0')
	{
		*tokenEnd = '\0';
		lastToken = tokenEnd + 1;
	}
	else
	{
		lastToken = (NULL);
	}
	return (tokenStart);
}


