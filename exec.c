#include "shell.h"

/**
 * exec - execute command
 * @argv: NULL terminated array of strings
 *
 * Return: no return
 */
void exec(char **argv)
{
	if (fork() == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
			perror("");
	}
	else
	{
		wait(NULL);
		_getline();
	}
}
