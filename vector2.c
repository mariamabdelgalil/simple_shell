#include "simple_shell.h"

/**
 * getDuplicateOfData - Get a duplicate of non-null data from StringVector
 * @vector: Pointer to StringVector.
 *
 * Description: Creates and returns a duplicate array of non-null data
 * from the StringVector.
 *
 * Return: Pointer to the duplicate array.
 */
char** getDuplicateOfData(const StringVector* vector)
{
	size_t count = 0, i = 0;
	char** duplicate;

	while (i < vector->size)
	{
		if(vector->take_data[i])
			count++;
		i++;
	}
	duplicate = (char**)malloc((count + 1) * sizeof(char*));
	if (duplicate == NULL)
	{
		exit(EXIT_FAILURE);
	}
	count = 0;
	for (i = 0; i < vector->size; i++)
	{
		if(vector->take_data[i] == 0)
			continue;
		duplicate[count] = _strdup(vector->data[i]);
		if (duplicate[count] == NULL)
			exit(EXIT_FAILURE);
		count++;
	}

	duplicate[count] = NULL;
	return (duplicate);
}

/**
 * unsetInStringVector - Unset a variable in StringVector
 * @vector: Pointer to StringVector.
 * @var: Variable to unset.
 *
 * Description: Sets take_data to 0 for elements in the StringVector
 * where @var is found after an equals sign.
 * Return: void
 */
void unsetInStringVector(StringVector* vector, char *var)
{
	size_t i;
	char* ptr;

	for (i = 0; i < vector->size; ++i)
	{
		if (vector->take_data[i])
		{
			ptr = find_substring_start(vector->data[i], var);
			if (ptr && *ptr == '=')
			{
				vector->take_data[i] = 0;
			}
		}
	}
}

/**
 * setInStringVector - Set a variable in StringVector
 * @vector: Pointer to StringVector.
 * @var: Variable to set.
 * @value: Value to assign to the variable.
 *
 * Description: If the variable exists, updates its value; otherwise, adds
 * a new variable to the StringVector.
 *
 * Return: void
 */
void setInStringVector(StringVector* vector, char *var, char *value)
{
	int len = _strlen(var) + _strlen(value) + 2;
	char *tempEnv = (char*)malloc(len);
	char* ptr = NULL;
	size_t i = 0;

	_strcpy(tempEnv, var);
	_strcat(tempEnv, "=");
	_strcat(tempEnv, value);

	for (i = 0; i < vector->size; ++i)
	{
		ptr = find_substring_start(vector->data[i], var);
		if (ptr && *ptr == '=')
		{
			free(vector->data[i]);
			vector->data[i] = tempEnv;
			vector->take_data[i] = 1;
			return;
		}
	}
	push_back(vector, tempEnv);
	free(tempEnv);
}

/**
 * getInStringVector - Get the value of a variable in StringVector
 * @vector: Pointer to StringVector.
 * @var: Variable to retrieve.
 *
 * Description: Searches for the variable @var in the StringVector and
 * returns its value if found, or NULL if not found.
 *
 * Return: Pointer to the value of @var, or NULL if not found.
 */
char* getInStringVector(StringVector* vector, char *var)
{

	char* ptr = NULL;
	size_t i = 0;

	for (i = 0; i < vector->size; ++i)
	{
		if (vector->take_data[i] == 0)
			continue;
		ptr = find_substring_start(vector->data[i], var);
		if (ptr && *ptr == '=')
		{
			ptr++;
			return (ptr);
		}
	}
	return (NULL);
}
