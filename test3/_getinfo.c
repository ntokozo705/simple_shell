#include "main.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes struct
 * @info: struct
 * @add: arguments
 */

void set_info(info_t *info, char **add)
{
	int i = 0;

	info->fname = add[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 1; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		r_alias(info);
		r_vars(info);
	}
}
