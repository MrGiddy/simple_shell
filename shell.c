#include "main.h"

/**
 * display_prompt - Displays a commandline prompt
 *
 * Return: Nothing
 */
void display_prompt(void)
{
	_puts("($) ");
}

/**
 * read_commandline - reads a commandline input
 *
 * Return: Nothing
 */
char *read_commandline(void)
{
	char *lineptr = NULL;
	size_t n;
	ssize_t ret;

	n = 0;
	ret = getline(&lineptr, &n, stdin);
	if (ret == -1)
	{
		perror("getline");
		free(lineptr);
		exit(EXIT_FAILURE);
	}

	return (lineptr);
}

/**
 * execute_command - executes a command
 * @command: A string from the commandline
 * @delimiter: Token separator(s) for command
 * Return: Nothing
 */
void execute_command(char *command, char *delimiter)
{
	pid_t pid;
	int wstatus;
	char **argv = toknize(command, delimiter);
	extern char **environ;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if ((execve(argv[0], argv, environ)) == -1)
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

/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	char *command;
	char *delimiter = " ,\t\n";

	while (1)
	{
		display_prompt();
		command = read_commandline();
		execute_command(command, delimiter);
	}

	exit(EXIT_SUCCESS);
}
