#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>

extern char **environ;

char **tokenizer(char *cmd);
void exec(char **argv);
void file_stat(char *cmd, char **argv);
char *_getline();

#endif
