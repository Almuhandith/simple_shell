#include "shell.h"
/**
 * main - prompt
 * @argc: number of items in argv
 * @argv: NULL terminated array of strings
 *
 * Return: no return
 */

int main(__attribute__((unused))int argc, __attribute__((unused))char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	bool x = true;
	
	while (x == true)
	{
		printf("$ ");
		
		nread = getline(&line, &len, stdin);
		printf("%s", line);
		printf("exit: %ld\n", nread);
		
		if (nread == -1)
			exit(0);
		
		free(line);
	}
}
