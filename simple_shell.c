#include "shell.h"
/**
 * main - shell entry function
 * @argc: argument count
 * @argv: argument vector
 * @envp: emvironment variables
 * Return: 0 for SUCCESS
 */
int main(int argc, char *argv[], char *envp[])
{
	char buf[] = "($) ";
	char *prompt = NULL;
	size_t promptlen = 0;
	ssize_t len;
	bool piped = false;
	char **tokens;
	char *delim = " ";
	int i;

	(void) argc;
	(void) argv;
	while (!piped)
	{
		if (isatty(STDIN_FILENO) == 0)
			piped = true;
		else
			write(STDOUT_FILENO, buf, sizeof(buf));
		len = _getline(&prompt, &promptlen, STDIN_FILENO);
		if (len == -1)
			exit(0);
		if (len > 0 && prompt != NULL)
		{
			if (strcmp(prompt, "exit\n") == 0)
			{
				free(prompt);
				exit(EXIT_SUCCESS);
			}
			if (prompt[len - 1] == '\n')
				prompt[len - 1] = '\0';
			tokens = _tokenize(prompt, delim);
			_execute(tokens[0], tokens, envp);
			for (i = 0; tokens[i] != NULL; i++)
				free(tokens[i]);
			free(tokens);
			prompt = NULL;
		}
	}
	if (prompt != NULL)
		free(prompt);
	return (0);
}

/**
 * _tokenize - breaks strings to tokens
 * @prompt: pointer to string
 * @delim: string delimiter
 * Return: pointer to array of strings
 */
char **_tokenize(char *prompt, char *delim)
{
	char **tokens;
	int count = 0;
	int i = 0;
	char *temp = strdup(prompt);
	char *t = strtok(temp, delim);

	while (t != NULL)
	{
		count++;
		t = strtok(NULL, delim);
	}
	free(temp);

	tokens = malloc((count + 1) * sizeof(char *));
	t = strtok(prompt, delim);
	while (t != NULL)
	{
		tokens[i] = strdup(t);
		i++;
		t = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * _execute - executes shell commands
 * @prompt: pointer to string command
 * @argv: argument vector
 * @envp: environment variables
 * Return: void
 */
void _execute(char *prompt, char *argv[], char *envp[])
{
	int status;
	char *inputCommand = NULL;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (strcmp(prompt, "env") == 0)
		{
			_printenv();
			exit(EXIT_SUCCESS);
		}
		inputCommand = get_path(prompt);
		execve(inputCommand, argv, envp);
		perror(inputCommand);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
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
 * get_path - gets or fetches the PATH of a file
 * @command: the PATH to be found
 * Return: an array of string.
 */
char *get_path(char *command)
{
	char *path_copy;
	int commandlength;
	char *path_token;
	int dir_length;
	char *file_path;
	struct stat buffer;
	char *path = getenv("PATH");

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
