#include "main.h"

/**
 * my_hist - displays history list
 * @info: struct
 *
 * Return: 0 Always.
 */

int my_hist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_aliass - sets alias to a string
 * @info: struct para
 * @str: string alias
 *
 * Return: 0 success, otherwise 1.
 */

int unset_aliass(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_nodeindex(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_liass - sets alias
 * @info: para struct
 * @str: alias string
 *
 * Return: 0 Always, 1 error.
 */

int set_aliass(info_t *info, char *str)
{
	char *p;

	p = strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_aliass(info, str));
	unset_aliass(info, str);
	return (end_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_aliass - prints an alias
 * @node: node alias
 *
 * Return: 0 Always
 */

int print_aliass(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			putchar(*a);
		putchar('\'');
		puts(p + 1);
		puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * myalias - mimics alias builtin
 * @info: struct
 *
 * Return: 0 Always.
 */

int myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_aliass(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strchr(info->argv[i], '=');
		if (p)
			set_aliass(info, info->argv[i]);
		else
			print_aliass(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
