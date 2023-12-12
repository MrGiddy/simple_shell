#include "shell.h"

/**
 * getEnv - retrieves value of an environment variable
 * @name: The name of the environment variable to retrieve
 * Return: The value of environment variable
 */
char *getEnv(char *name)
{
	char **environ2 = environ;
	int i, j;
	char *tok, *result;
	envVarNode env_variable;
	/* Declare an array of structs */
	envVarNode *array;

	if (name == NULL)
		return (NULL);

	array = malloc(lenOfArray(environ2) * sizeof(envVarNode));

	for (i = 0; i < lenOfArray(environ2); i++)
	{
		tok = strtok(environ2[i], "=");

		env_variable.key = malloc(_strlen(tok) + 1);
		if (env_variable.key == NULL)
		{
			_puts("getEnv(): malloc failed.");
			exit(EXIT_FAILURE);
		}
		_strcpy(env_variable.key, tok);

		tok = strtok(NULL,  "=");

		env_variable.value = malloc(_strlen(tok) + 1);
		if (env_variable.value == NULL)
		{
			_puts("getEnv(): malloc failed.");
			exit(EXIT_FAILURE);
		}
		_strcpy(env_variable.value, tok);

		array[i] = env_variable;
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
