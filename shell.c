#include "shell.h"

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
		free(lineptr);
		_puts("\n");
		exit(EXIT_FAILURE);
	}

	return (lineptr);
}


/**
 * printError - prints an error message
 * Return: Nothing
 */
void printError(char *str)
{
	_puts("hsh: ");
	perror(str);
}

/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	char *command;
	char *delimiter = " \t\n";
	char **argv;
	int ac, j;

	while (1)
	{
		display_prompt();

		command = read_commandline();
		if (_strcmp(command,"exit") == 0)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (command[0] == '\n')
			{
				free(command);
				continue;
			}

			argv = toknize(command, delimiter);
			if (argv == NULL)
			{
				/* Handle toknization failure */
				free(command);
				continue;
			}

			execute_command(argv);

			free(command);
			ac = lenOfArray(argv);
			for (j = 0; j < ac; j++)
                	{
				free(argv[j]);
			}
			free(argv);
			argv = NULL;
		}
	}

	exit(EXIT_SUCCESS);
}
