#include "shell.h"
/**
 * _getline - replica of the getline function
 * @lineptr: string pointer
 * @n: string length
 * @fd: file descriptor
 * Return: length of string
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_size, buffer_index;
	char *line = NULL;
	ssize_t line_size = 0, bytes_read;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr != NULL)
	{
		line = *lineptr;
		line_size = *n;
	}
	while (1)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			buffer_index = 0;
			if (buffer_size <= 0)
				break;
		}
		if (line_size < 2)
		{
			line_size = BUFFER_SIZE;
			line = realloc(line, line_size);
			if (line == NULL)
				return (-1);
		}
		bytes_read = 0;
		while (buffer_index < buffer_size && bytes_read < line_size - 1)
		{
			line[bytes_read++] = buffer[buffer_index++];
			if (line[bytes_read - 1] == '\n')
				break;
		}
		if (bytes_read >= line_size - 1 && line[bytes_read - 1] != '\n')
		{
			line_size *= 2;
			line = realloc(line, line_size);
			if (line == NULL)
				return (-1);
		}
		else
			break;
	}
	if (bytes_read == 0)
	{
		free(line);
		*lineptr = NULL;
		*n = 0;
		return (-1);
	}
	line[bytes_read] = '\0';
	*lineptr = line;
	*n = line_size;
	return (bytes_read);
}
