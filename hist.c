#include "main.h"

/**
 * get_history - Get history file
 * @info: struct parameter
 *
 * Return: allocated string history file.
 */

char *get_hist(info_t *info)
{
	char *buffer, *dir;

	dir = get_env(info, "home=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (strlen(dir) + strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	strcpy(buffer, dir);
	strcat(buffer, "/");
	strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_hist - Create or append a file
 * @info: struct parameter
 *
 * Return: 1 success, 0 otherwise
 */

int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = get_hist(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_hist - Reads the history file
 * @info: struct
 *
 * Return: 1 success, 0 failed
 */
int read_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_hist(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_hist(info, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_nodeindex(&(info->history), 0);
	number_hist(info);
	return (info->histcount);
}
/**
 * build_hist - Adds entry to a linked list
 * @info: struct
 * @buffer: buffer
 * @linecount: line count history
 * Return: 0 Always.
 */

int build_hist(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	end_node(&node, buffer, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * number_hist - remember history linked list
 * @info: struct
 *
 * Return: new history count.
 */

int number_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
