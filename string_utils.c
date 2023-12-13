#include "simple_shell.h"

/**
 * _strcpy - Copy a string from source to destination
 * @dest: Pointer to the destination string.
 * @src:  Pointer to the source string.
 *
 * Description:
 *     This function copies the characters from the source string to the
 *     destination string, including the '\0' character.
 *
 * Return:
 *     Pointer to the destination buffer.
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strncpy - Copy up to n characters from source to destination
 * @dest: Pointer to the destination string.
 * @src:  Pointer to the source string.
 * @n:    Max number of characters to copy.
 *
 * Description:
 *     This function copies up to n characters from the source string to the
 *     destination string, including the '\0' character. If the
 *     source string is shorter than n, null characters are appended to fill
 *     the remaining space.
 *
 * Return:
 *     Pointer to the destination string.
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i++] = '\0';
	}
	return (dest);
}

/**
 * _strcat - Concatenate two strings
 * @dest: Destination buffer.
 * @src:  Source string.
 *
 * Description: Appends characters from @src to @dest, ensuring null-termination.
 * Return: Pointer to the destination buffer (@dest).
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[j] != '\0')
	{
		j++;
	}
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}


/**
 * _strncat - Concatenate up to n characters from src to dest
 * @dest: Pointer to the destination string.
 * @src:  Pointer to the source string.
 * @n:    Number of characters to concatenate.
 *
 * Description: Concatenates up to @n characters from
 * (@src) to the end of (@dest), ensuring
 * null-termination.
 *
 * Return: Pointer to the destination string.
 */
char *_strncat(char *dest, const char *src, int n)
{
	int i = 0;
	int j = 0;

	while (dest[j] != '\0')
	{
		j++;
	}
	while (i != n && src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}


/**
 * _strcmp - Compare two strings
 * @s1: First string.
 * @s2: Second string.
 *
 * Description: Compares @s1 and @s2 lexicographically.
 * Return: Integer result of the comparison.
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	for (; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (-1 * (s2[i] - s1[i]));
	}
	return (0);
}


