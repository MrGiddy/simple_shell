#include "shell.h"

/**
 * getEnv - retrieves value of an environment variable
 * @name: The name of the environment variable to retrieve
 * Return: The value of environment variable
 */
char *getEnv(char *name)
{
	char **environ2 = environ;
	int i;
	char *tok, *result = NULL;
	/* Declare an array of structs */
	envVarNode *array;

	if (name == NULL)
		return (NULL);

	array = malloc(lenOfArray(environ2) * sizeof(envVarNode));

	for (i = 0; i < lenOfArray(environ2); i++)
	{
		tok = strtok(environ2[i], "=");

		array[i].key = malloc(_strlen(tok) + 1);
		if (array[i].key == NULL)
		{
			_puts("getEnv(): malloc failed.");
		}
		_strcpy(array[i].key, tok);

		tok = strtok(NULL,  "=");

		array[i].value = malloc(_strlen(tok) + 1);
		if (array[i].value == NULL)
		{
			_puts("getEnv(): malloc failed.");
		}
		_strcpy(array[i].value, tok);
	}

	for (i = 0; i < lenOfArray(environ2); i++)
	{
		if (_strcmp(array[i].key, name) == 0)
		{
			result = _strdup(array[i].value);
			break;
		}
	}

	for (i = 0; i < lenOfArray(environ2); i++)
	{
		free(array[i].key);
		free(array[i].value);
	}
	free(array);
	return (result);
}
