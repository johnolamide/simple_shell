#include "shell.h"

char *get_path(char *command);

/**
 * execute - executes the argument inputed
 * @prompt: the argument it takes in
 * @argv: an array of argument
 * Return: void
 */

void execute(char *prompt, char *argv[])
{
	int cont;
	char *input_command = NULL;
	pid_t pid = fork();

	if (pid == 0)
	{
		input_command = get_path(prompt);

		execve(input_command, argv, NULL);
		perror(prompt);
	}
	else
		wait(&cont);
}

/**
 * main - handles path of a file
 * @argc: number of arguments
 * @argv: array of argument
 * Return: an integer
 */

int main(int argc, char *argv[])
{
	size_t promptlen = 0;
	char *prompt  = NULL;
	ssize_t len;

	(void)argc;

	while (1)
	{
		printf("$ ");

		len = getline(&prompt, &promptlen, stdin);
		strtok(prompt, "\n");

		if (len == -1)
			return (-1);

		execute(prompt, argv);
	}

	free(prompt);

	return (0);
}

/**
 * get_path - gets or fetches the PATH of a file
 * @command: the PATH to be found
 * Return: an array of string.
 */

char *get_path(char *command)
{
	char *path, *path_copy;
	int commandlength;
	char *path_token;
	int dir_length;
	char *file_path;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		commandlength = strlen(command);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			dir_length = strlen(path_token);
			file_path = malloc(commandlength + dir_length + 2);

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);

		if (stat(command, &buffer) == 0)
			return (command);

		return (NULL);
	}
	return (NULL);
}
