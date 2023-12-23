#include "shell.h"

/**
 * execute_command - executes a command
 * @argv: An array of strings (tokenized command line)
 * Return: Nothing
 */
void execute_command(char **argv)
{
	char *fullPath;
	char **ptr;

	if (access(argv[0], F_OK) == 0 && access(argv[0], X_OK) == 0)
	{
		fork_and_execute(argv);
	}
	else
	{
		fullPath = _strdup(handle_path("PATH", argv[0]));
		if (fullPath == NULL)
		{
			printError("Failed to get full path");
		}
		else
		{
			if (access(fullPath, F_OK) == 0 && access(fullPath, X_OK) == 0)
			{
				/* Alloc. mem for ptr, including space for fullPath and NULL */
				ptr = malloc(sizeof(char *) * 2);
				if (ptr == NULL)
				{
					printError("malloc");
					exit(EXIT_FAILURE);
				}
				ptr[0] = fullPath;
				ptr[1] = NULL;
				fork_and_execute(ptr);
				free(ptr[0]); /* Free fullPath */
				free(ptr); /* Free ptr */
			}
			else
			{
				printError("Access denied for full path");
				free(fullPath);
			}
		}
	}
}

/**
 * fork_and_execute - executes a command in a child process
 * @argv: argument vector
 * Return: Nothing
 */
void fork_and_execute(char **argv)
{
	pid_t pid;
	int wstatus;

	pid = fork();

	if (pid == -1)
	{
		printError("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&wstatus);
	}
}
