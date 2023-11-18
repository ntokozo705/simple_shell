#include "main.h"

/**
 * get_envir - returns the string copy of environment
 * @info: struct arguments
 *
 * Return: 0 Always.
 */

char **get_envir(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * unset_env - Remove environment variable
 * @info: struct arg
 *
 * Return: 1 success, 0 failled.
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_nodeindex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env - New enviroment
 * @info: struct arg
 * @var: string env
 * @value: string env value
 *
 * Return: 0 Always.
 */

int set_env(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buffer = malloc(strlen(var) + strlen(value) + 2);
	if (!buffer)
		return (1);
	strcpy(buffer, var);
	strcat(buffer, "=");
	strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	end_node(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
