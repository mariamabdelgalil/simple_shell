#include "simple_shell.h"
/**
 * _strlen - Calculate the length of a string
 * @in: Pointer to the input string.
 *
 * Description: Computes the length of the string pointed to by @in.
 * Return: Length of the string.
 */
int _strlen(const char *in)
{
	int cnt = 0;

	while (*in != '\0')
	{
		cnt++;
		in++;
	}
	return (cnt);
}

/**
 * _strspn - Get length of initial segment with only characters from accept
 * @s: Input string.
 * @accept: Set of characters to accept.
 *
 * Description: Returns the length of the initial segment of @s
 * containing only characters from @accept.
 * Return: Length of the initial segment.
 */
size_t _strspn(const char *s, const char *accept)
{
	size_t i, j;
	int stillValid = 1;

	i = 0;
	while (s[i] != '\0')
	{
		stillValid = 0;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				stillValid = 1;
				break;
			}
		}
		if (!stillValid)
			break;
		i++;
	}
	return (i);
}
/**
 * _strcspn - Get length of initial segment not containing chars from reject
 * @str: Input string.
 * @reject: Set of characters to reject.
 *
 * Description: Computes the length of the initial segment of @str
 * without characters from @reject.
 * Return: Length of the initial segment.
 */
size_t _strcspn(const char *str, const char *reject)
{
	size_t i, j;

	for (i = 0; str[i] != '\0'; i++)
	{
		for (j = 0; reject[j] != '\0'; j++)
		{
			if (str[i] == reject[j])
			{
				return (i);
			}
		}
	}
	return (i);
}

