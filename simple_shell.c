#include "shell.h"
/**
 *
 */
int main(int argc, char *argv[], char *envp[])
{
	char buf[] = "$ ";
	char* prompt = NULL;
	size_t promptlen = 0;
	ssize_t len;
	bool piped = false;
	char** tokens;
	char* delim = " ";
	int i;

	while (!piped)
	{
		if (isatty(STDIN_FILENO) == 0)
			piped = true;
		else
			write(STDOUT_FILENO, buf, sizeof(buf));
		len = getline(&prompt, &promptlen, stdin);
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
			if (tokens == NULL)
				break;
			_execute(tokens[0], tokens, envp);
			for (i = 0; tokens[i] != NULL; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			prompt = NULL;
		}
	}
	if (prompt != NULL)
		free(prompt);
	return (0);
}

/**
 *
 */
char** _tokenize(char* prompt, char* delim)
{
	char** tokens;
	int count = 0;
	int i = 0;
	char* temp = strdup(prompt);
	char* t = strtok(temp, delim);
	while (t != NULL)
	{
		count++;
		t = strtok(NULL, delim);
	}
	free(temp);

	tokens = malloc((count + 1) * sizeof(char*));
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
 *
 */
void _execute(char* prompt, char* argv[], char* envp[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (strcmp(prompt, "env") == 0)
		{
			_printenv();
			exit(EXIT_SUCCESS);
		}
		execve(prompt, argv, envp);
		perror(prompt);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status);
}

/**
 *
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
