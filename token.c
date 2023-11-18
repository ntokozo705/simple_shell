#include "main.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numword = 0;
	char **y;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numword++;

	if (numword == 0)
		return (NULL);
	y = malloc((1 + numword) * sizeof(char *));
	if (!y)
		return (NULL);
	for (i = 0, j = 0; j < numword; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		y[j] = malloc((k + 1) * sizeof(char));
		if (!y[j])
		{
			for (k = 0; k < j; k++)
				free(y[k]);
			free(y);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			y[j][m] = str[i++];
		y[j][m] = 0;
	}
	y[j] = NULL;
	return (y);
}

/**
 * **strtow1 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow1(char *str, char d)
{
	int i, j, k, m, numword = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numword++;
	if (numword == 0)
		return (NULL);
	ss = malloc((1 + numword) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (i = 0, j = 0; j < numword; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		ss[j] = malloc((k + 1) * sizeof(char));
		if (!ss[j])
		{
			for (k = 0; k < j; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ss[j][m] = str[i++];
		ss[j][m] = 0;
	}
	ss[j] = NULL;
	return (ss);
}
