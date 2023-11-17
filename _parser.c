#include "main.h"

/**
 * is_cmd - Determines command
 * @in: struct
 * @path: path of file
 *
 * Return: 1 success - Otherwise.
 */

int is_cmd(info_t *in, char *path)
{
	struct stat st;

	(void)in;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dupl_chars - duplicates char
 * @str: string
 * @start: starting index
 * @stop: ending index
 *
 * Return: New buffer pointer.
 */

char *dupl_chars(char *str, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str[i] != ',')
			buffer[k++] = str[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - finds cmd in PATH
 * @info: Info struct
 * @str:
 * string
 * @cmd: cmd o find
 *
 * Return: full path of cmd.
 */

char *find_path(info_t *info, char *str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!str)
		return (NULL);
	if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			path = dupl_chars(str, curr_pos, i);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
