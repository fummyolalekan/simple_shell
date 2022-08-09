#include "main.h"

/**
 * main - simple shell file that can run commands with their full path,
 * without any argument.
 * @ac: argument count
 * @av: argument list
 *
 * Return: 0 on success.
 */

int main(int ac, char *av[])
{
	char *lineptr = NULL;
	size_t n = 0;
	int n_read = 0;
	const char *delim = " ";
	int count = 0;
	char **words = NULL;
	pid_t pid;
	int status;
	int loop = 1;

	while (loop)
	{
		write(1, "#cisfun$ ", 9);

		n_read = getline(&lineptr, &n, stdin);
		lineptr[n_read - 1] = '\0';

		words = tokenize(lineptr, delim, &count);

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			free(lineptr);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execve(words[0], &words[0], NULL) == -1)
			{
				perror("Error");
				free(lineptr);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}

	free(lineptr);
	return (0);
}

/**
 * tokenize - splits a string and returns an array of each
 * token/word of the string
 * @text - string to tokenize
 * @delim - delimiter(s) - can handle multiple delimiters
 * @count - buffer to hold number of tokens returned by functions
 * Return:  array of strings/tokens. Free allocated memory after use!
 */

char **tokenize(char *text, const char *delim, int *count)
{
	char **words;
	int i;
	int j;
	int count_delim = 1;

	i = 0;
	while (text[i])
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (text[i] == delim[j])
				count_delim++;
		}
		i++;
	}

	words = malloc(sizeof(char *) * count_delim);

	if (words == NULL)
	{
		printf("Malloc Failed!\n");
		exit(99);
	}

	words[0] = strtok(text, delim);
	for (i = 1; i < count_delim; i++)
	{
		words[i] = strtok(NULL, delim);
	}

	i = 0;
	count_delim = 0;
	while (words[i] != NULL)
	{
		count_delim++;
		i++;
	}

	*count = count_delim - 1;
	return (words);
}
