#include "shell.h"
/**
 * main - prompt
 * @argc: number of items in argv
 * @argv: NULL terminated array of strings

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
}

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

	/* get number of arguments ==> argc */
	while (token)
		token = strtok(NULL, " \n"), argc++;

	argv = malloc(sizeof(char *) * argc);

	/* insert strings in string array */
	token = strtok(cmdcpy, " \n");
	while (token)
        argv[i++] = token, token = strtok(NULL, " \n");

	argv[i] = NULL;
    if (argv[0][0] == '/' && stat(cmd, &st) == 0)
        exec(argv);

    file_stat(argv[0], argv);
}

/
void file_stat(char *cmd, char **argv)
{
	int i = 0;
	char *token = NULL, *key = "PATH", *path = NULL;
	char **env_cpy;
	struct stat st;

	while (environ[i])
		i++;

	env_cpy = malloc(sizeof(char *) * i);
	for (i = 0; environ[i]; i++)
		env_cpy[i] = strdup(environ[i]);
	env_cpy[i] = NULL;

	i = 0;
	while (env_cpy[i])
	{
		token = strtok(env_cpy[i++], "=");
		if (strcmp(key, token) == 0)
			break;
	}
	token = strtok(NULL, "\0");
	token = strtok(token, ":");

	while (token)
	{
		path = malloc(sizeof(char) * (strlen(token) + strlen(cmd) + 1));
		strcat(path, token), strcat(path, "/"), strcat(path, cmd);
		if (stat(path, &st) == 0)
		{
			argv[0] = strdup(path);
			exec(argv);
		}
		token = strtok(NULL, ":");
	}
	perror("not found");
	_getline();
}


/**
 * exec - execute command
 * @argv: NULL terminated array of strings
 *
 * Return: no return
 */
void exec(char **argv)
{
	int i;

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