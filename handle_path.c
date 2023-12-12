#include "shell.h"

char *handle_path(char *pathName, char *prog)
{
	char *pathString = getEnv(pathName);
	char **arrayOfPaths;
	struct stat st;
	char *fullPath = NULL;
	int i, j;

	if (pathString == NULL)
	{
		_puts("Error: Environment variable ");
		_puts(pathName);
		_puts(" not set.");
		return (NULL);
	}

	arrayOfPaths = toknize(pathString, ":");
	free(pathString); /* is dynam. alloc'd in getEnv() */

	for (i = 0; arrayOfPaths[i] != NULL; i++)
	{
		/* Alloc. mem for fullPath */
		fullPath = malloc(_strlen(arrayOfPaths[i]) + 1 + _strlen(prog) + 1);
		if (fullPath == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		/* Build the fullPath */
		_strcpy(fullPath, arrayOfPaths[i]);
		_strcat(fullPath, "/");
		_strcat(fullPath, prog);

		if (stat(fullPath, &st) == 0)
		{
			for (j = 0; j <= i; j++)
			{
				free(arrayOfPaths[j]);
			}
			free(arrayOfPaths);
			return (fullPath);
		}
		/* Free mem. if path not found */
		free(fullPath);
	}

	return (NULL);
}
