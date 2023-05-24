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

	(void) argc;
	while (!piped)
	{
		if (isatty(STDIN_FILENO) == 0)
			piped = true;
		else
			write(STDOUT_FILENO, buf, sizeof(buf));
		len = getline(&prompt, &promptlen, stdin);
		if (len == -1)
			return (-1);
		if (len > 0 && prompt != NULL)
		{
			if (prompt[len - 1] == '\n')
				prompt[len - 1] = '\0';
			_execute(prompt, argv, envp);
			prompt = NULL;
		}
	}
	if (prompt != NULL)
		free(prompt);
	return (0);
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
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(prompt, argv, envp);
		perror(prompt);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
}

