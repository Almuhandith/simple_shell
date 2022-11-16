#include "shell.h"

/**
 * tokenizer - parses the command line
 * @cmd: command
 *
 * Return: no return
 */

char **tokenizer(char *cmd)
{
	char *cmdcpy = NULL, *token = NULL;
	char **argv = NULL;
	int argc = 0, i = 0;
	struct stat st;

	cmdcpy = strdup(cmd);
	token = strtok(cmd, " \n");

	while (token)
		token = strtok(NULL, " \n"), argc++;

	argv = malloc(sizeof(char *) * argc);

	token = strtok(cmdcpy, " \n");
	while (token)
		argv[i++] = token, token = strtok(NULL, " \n");

	argv[i] = NULL;
	if (argv[0][0] == '/' && stat(cmd, &st) == 0)
		exec(argv);

	file_stat(argv[0], argv);

	return (argv);
}
