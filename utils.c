#include "shell.h"

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
	char *copyOfCommand, *tok;
	char **argv;
	int numToks, i, j;

	copyOfCommand = _strdup(command);
	tok = strtok(copyOfCommand, delimiter);

	/* Count non-empty tokens */
	for (numToks = 0; tok != NULL; numToks++)
	{
		if (_strlen(tok) > 0)
		{
			tok = strtok(NULL, delimiter);
		}
		else
		{
			/* Move to next tok if tok is empty */
			tok = strtok(NULL, delimiter);
			numToks--;
		}
	}

	if (numToks > 0)
	{
		argv = malloc((numToks + 1) * sizeof(char *));
		if (argv == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		free(copyOfCommand);
		copyOfCommand = _strdup(command);
		tok = strtok(copyOfCommand, delimiter);
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
		return (argv);
	}
	free(copyOfCommand);
	return (NULL);
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

/**
 * lenOfArray - Computes length of NULL-terminated array of strings
 * @array: An array of strings
 * Return: Length of array, NULL not counted
 */
int lenOfArray(char **array)
{
	int len;

	for (len = 0; array[len] != NULL; len++)
		;

	return (len);
}

/**
 * _strcmp - checks the equality of two strings
 * @string: A null-terminated string
 * @string2: A null-terminated string
 * Return: 0 if equal, +ve if s1 > s2, -ve if s1 < s2
 */
int _strcmp(char *string, char *string2)
{
	while (*string && *string2)
	{
		if (*string -  *string2 != 0)
		{
			return (*string - *string2);
		}
		string++;
		string2++;
	}

	return (0);
}

/**
 * _strcat - joins a string to another
 * @dest: A pointer to the initial string
 * @src: A pointer to the string to concatenate
 * Return: A pointer to the concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int i, lenDest, lenSrc;

	for (lenDest = 0; dest[lenDest] != '\0'; lenDest++)
		;

	for (lenSrc = 0; src[lenSrc] != '\0'; lenSrc++)
		;

	for (i = 0; i < lenSrc; i++)
	{
		dest[lenDest] = src[i];
		lenDest++;
	}
	dest[lenDest] = '\0';
	return (dest);
}

/**
 * freeArrayOfStrings - frees a dynamically allocaed array of strings
 * @array: an array of strings
 * @lenArray: Length of aray
 * Return: Nothing
 */
void freeArrayOfStrings(char **array)
{
	int i;

	if (array == NULL)
		return;

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}

	free(array);
}
