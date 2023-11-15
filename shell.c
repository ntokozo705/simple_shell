#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LEN 1000
#define MAX_ARGS 10
/**
 * error_handler - handles errors
 * @err: error message
 * Return: nothing
 */
void error_handler(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);

}
/**
 * display_prompt - handles errors
 * Return: 0
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * main - shell program
 * Return: 0
 */

int main(void)
{
	char input[MAX_INPUT_LEN];
	char *token;
	char *args[MAX_ARGS];
	int argCount = 0;
	pid_t pid;

	while (1)
	{
		display_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		token = strtok(input, " ");

		while (token != NULL && argCount <  MAX_ARGS - 1)
		{
			args[argCount++] = token;
			token = strtok(NULL, " ");
		}
		args[argCount] = NULL;
		pid = fork();

		if (pid == -1)
		{
			error_handler("fork");
		}
		else if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				error_handler("./shell");
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	return (0);
}
