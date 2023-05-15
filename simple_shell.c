#include "shell.h"
#include <stdbool.h>
void _execute(char* prompt, char* argv[], char* envp[]);
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

	while (1 && !piped)
	{
		write(STDOUT_FILENO, buf, sizeof(buf));
		//piped = true;
		len = getline(&prompt, &promptlen, stdin);
		prompt[len - 1] = '\0';
		_execute(prompt, argv, envp);
	}	
	return (0);
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
		execve(prompt, argv, envp);
		perror(prompt);
	}
	else
		wait(&status);
}
