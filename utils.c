#include "main.h"

/**
 * _strlen - Computes length of a string
 * @str: A string
 * Return: Length of str
 */
int _strlen(char *str)
{
	int len_str;

	len_str = 0;
	while (*str)
	{
		len_str++;
		str++;
	}

	return (len_str);
}

/**
 * _puts - print a string to stdout
 * @str: A string
 * Return: An integer, no. of bytes printed
 */
int _puts(char *str)
{
	ssize_t bytesWritten;

	bytesWritten = write(STDOUT_FILENO, str, _strlen(str));

	return (bytesWritten);
}

/**
 * _strdup - copies a string into a new memory block
 * @str: The string to copy
 * Return: A pointer to a copy of str in new memory block
 */
char *_strdup(char *str)
{
	char *ptr;
	int count;

	if (!str)
	{
		return (NULL);
	}

	ptr = malloc((_strlen(str) + 1) * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}

	count = 0;
	while (str[count] != '\0')
	{
		ptr[count] = str[count];
		count++;
	}
	ptr[count] = '\0';

	return (ptr);
}

/**
 * toknize - splits a string into tokens
 * @command: The string to tokenize
 * @delimiter: A string of delimiter(s)
 * Return: A pointer to array of strings
 */
char **toknize(char *command, char *delimiter)
{
	char *copyOfCommand, *copyOfCommand2, *tok;
	char **argv;
	int numToks, i, j;

	copyOfCommand = _strdup(command);
	tok = strtok(copyOfCommand, delimiter);
	for (numToks = 0; tok != NULL; numToks++)
		tok = strtok(NULL, delimiter);

	argv = malloc(numToks * sizeof(char *));
	if (argv == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	copyOfCommand2 = _strdup(command);
	tok = strtok(copyOfCommand2, delimiter);
	i = 0;
	while (tok != NULL)
	{
		argv[i] = malloc((_strlen(tok) + 1) * sizeof(char));
		if (argv[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(argv[j]);
			}
			free(argv);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		_strcpy(argv[i], tok);
		tok = strtok(NULL, delimiter);
		i++;
	}
	argv[i] = NULL;
	free(copyOfCommand);
	free(copyOfCommand2);
	return (argv);
}

/**
 * _strcpy - Copies a string to a pre-allocated buffer
 * @dest: A pre-allocated buffer
 * @src: The input string
 * Return: A pointer to dest, where src is copied
 */
char *_strcpy(char *dest, char *src)
{
	int len_src;

	for (len_src = 0; src[len_src] != '\0'; len_src++)
	{
		dest[len_src] = src[len_src];
	}
	dest[len_src] = '\0';

	return (dest);
}
