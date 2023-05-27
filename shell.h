#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

void _pexit(char *prompt);
void _execute(char *prompt, char *argv[], char *envp[]);
char **_tokenize(char *prompt, char *delim);
void _printenv(void);
char *get_path(char *command);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _isWhiteSpace(const char *prompt);

#endif
