#include "shell.h"

/**
 * _getline - getline function
 *
 * Return: no return
 */

char *_getline()
{
	char *cmd = NULL;
	size_t n;

	printf(">>> ");
	if (getline(&cmd, &n, stdin) == -1)
	{
		free(cmd);
		exit(0);
	}
	tokenizer(cmd);

	return (cmd);
}
