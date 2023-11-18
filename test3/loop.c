#include "main.h"

/**
 * hsh - main shell
 * @info: struct
 * @ad: arg vector
 *
 * Return: 0 success, 1 error.
 */

int hsh(info_t *info, char **ad)
{
	ssize_t r = 0;
	int built_re = 0;

	while (r != -1 && built_re != -2)
	{
		clear_info(info);
		if (interactive(info))
			puts("evr$ ");
		putchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, ad);
			built_re = find_builtin(info);
			if (built_re == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			putchar('\n');
		free_info(info, 0);
	}
	write_hist(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (built_re == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_re);
}
/**
 * find_builtin - find builtin cmd
 * @info: struct
 *
 * Return: -1 if failed, 0 if success
 */

int find_builtin(info_t *info)
{
	int i, built_in = -1;
	builtin_table builtin_t[] = {
		{"exit", myexit},
		{"help", myhelp},
		{"history", my_hist},
		{"setenv", mysetenv},
		{"unsetenv", myunsetenv},
		{"cd", mycd},
		{"alias", myalias},
		{NULL, NULL}
	};
	for (i = 0; builtin_t[i].type; i++)
		if (strcmp(info->argv[0], builtin_t[i].type) == 0)
		{
			info->line_count++;
			built_in = builtin_t[i].func(info);
			break;
		}
	return (built_in);
}

/**
 * find_cmd - find cmd in path
 * @info: struct
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->line_count == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/')
				&& is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - forks a exec thread
 * @inf: struct
 *
 * Return: void.
 */

void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}
