#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * linegetter - prints "$ ", wait for the user to enter a command
 * main - prints it on the next line
 * Return: always 0.
 */

int main(void)
{
	ssize_t n_read = 0;
	char *lineptr = NULL;
	size_t n = 0;

	write(1, "$ ", 2);

	n_read = getline(&lineptr, &n, stdin);

	printf("%s\n", lineptr);

	return (0);
}
