#include "shell.h"
/**
 * _getline - reads a line from a stream and stores it in a buffer
 * @lineptr: pointer to the buffer
 * @n: pointer to the size of the buffer
 * @stream: stream to read from
 * Return: number of characters read, or -1 on error or end-of-file
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char buffer[BUFFER_SIZE];
	size_t total = 0;
	size_t len;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = BUFFER_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (fgets(buffer, BUFFER_SIZE, stream))
	{
		len = strlen(buffer);
		if (total + len + 1 > *n)
		{
			char *tmp;
			*n = total + len + 1;
			tmp = realloc(*lineptr, *n);
			if (tmp == NULL)
				return (-1);
			*lineptr = tmp;
		}
		strcpy(*lineptr + total, buffer);
		total += len;
		if ((*lineptr)[total - 1] == '\n')
			break;
	}

	if (total == 0)
		return (-1);

	(*lineptr)[total] = '\0';
	return (total);
}

/**
 * _printenv - print the environment variables
 * Return: void
 */
void _printenv(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * _isWhiteSpace - check for whitespace prompt
 * @prompt: string prompt
 * Return: returns 1 if all is whitespace
 */
int _isWhiteSpace(const char *prompt)
{
	while (*prompt)
	{
		if (!isspace(*prompt))
			return (0);
		prompt++;
	}
	return (1);
}
