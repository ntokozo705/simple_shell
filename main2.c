#include "main.h"
#include <string.h>

/**
 * main- function call
 *
 * Return: 0 Always.
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
	/*pid_t pid = fork();*/

	while (1)
	{
		my_write("S_shell$ ");
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			my_write("\n");
			break;
		}
		input[strlen(input) - 1] = '\0';
		if (strcmp(input, "exit") == 0)
		{
			break;
		}
		/**if (pid == 0)
		{
			char *args[2];
			int ret = execvp(input, args);

			args[0] = input;
			args[1] = NULL;
			
			if (ret == -1)
			{
				perror("execvp");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			int status;
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork");
		}*/
		execute_command(input);
	}
	return (0);
}
