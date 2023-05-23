#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char** environ;

void _execute(char* prompt, char* argv[], char* envp[]);
char** _tokenize(char* prompt, char* delim);
void _printenv(void);
char *get_path(char *command);

#endif
