#include "main.h"

/**
 * input_buff - buffers chained
 * @info: para struct
 * @buff: address of buffer
 * @len: length
 *
 * Return: read bytes.
 */

ssize_t input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = get_line(buff, &len_p, stdin);
#else
		r = get_line(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				((*buff)[r - 1] == '\n')
				{
					(*buff)[r - 1] = '\0';
					r--;
				}
				info->linecount_flag = 1;
				remove_comments(*buff);
				build_hist(info, *buff, info->histcount++);
				{
					*len = r;
					info->cmd_buf = buff;
				}
			}
		}
	}
	return (r);
}
/**
 * get_input - gets a line minus the new line
 * @info: struct
 *
 * Return: read bytes.
 */

ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *p;

	putchar(BUF_FLUSH);
	r = input_buff(info, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;
		check_chain(info, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buffer_type = CMD_NORM;
		}
		*buff_p = p;
		return (strlen(p));
	}
	*buff_p = buff;
	return (r);
}

/**
 * getline - Gets next line arg
 * @info: struct para
 * @ptr: buffer pointer
 * @length: size of ptr
 *
 * Return: s
 */

int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buff + i, k - i);
	else
		strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - blocks Ctrl-C
 * @sig_num: signal number
 *
 * Return; void.
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	puts("\n");
	puts("$ ");
	putchar(BUF_FLUSH);
}
