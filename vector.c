#include "simple_shell.h"
/**
 * initializeVector - Initialize a StringVector
 * @vector: Pointer to StringVector to initialize.
 * @capacity: Initial capacity of the vector.
 *
 * Description: Allocates memory for the data and take_data arrays in the
 * StringVector, and initializes the size and capacity fields.
 * Return: void
 */
void initializeVector(StringVector* vector, size_t capacity)
{
	vector->data = (char**)malloc(capacity * sizeof(char*));
	vector->take_data = (int*)malloc(capacity * sizeof(int));
	vector->size = 0;
	vector->capacity = capacity;
}

/**
 * push_back - Add a value to the end of StringVector
 * @vector: Pointer to StringVector.
 * @value: String to add.
 *
 * Description: If the vector is full, doubles its capacity.
 * Adds a copy of @value to the end of the vector.
 * Return: void
 */
void push_back(StringVector* vector, const char* value)
{
	if (vector->size == vector->capacity)
	{
		vector->capacity *= 2;
		vector->data = (char**)_realloc(vector->data, vector->size * sizeof(char*), vector->capacity * sizeof(char*));
		vector->take_data = (int*)_realloc(vector->data, vector->size * sizeof(int), vector->capacity * sizeof(int));
	}
	vector->data[vector->size] = _strdup(value);
	vector->take_data[vector->size] = 1;
	vector->data[vector->size + 1] = NULL;
	vector->size++;
}

/**
 * free_string_vector - Free memory used by StringVector
 * @vector: Pointer to StringVector.
 *
 * Description: Frees the memory allocated for the data and take_data arrays
 * in the StringVector, and resets size and capacity to zero.
 * Return: void
 */
void free_string_vector(StringVector* vector)
{
	size_t i;

	for (i = 0; i < vector->size; ++i)
	{
		free(vector->data[i]);
	}
	free(vector->take_data);
	free(vector->data);
	vector->size = 0;
	vector->capacity = 0;
}




