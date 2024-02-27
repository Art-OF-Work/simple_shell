#include "shell.h"

/**
 * take_environ - returns the string array copy of our environ
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **take_environ(line_t *line)
{
	if (!line->environ || line->env_changed)
	{
		line->environ = list_to_strings(line->env);
		line->env_changed = 0;
	}

	return (line->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @line: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(line_t *line, char *var)
{
	list_t *node = line->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			line->env_changed = delete_node_at_index(&(line->env), i);
			i = 0;
			node = line->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (line->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @line: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(line_t *line, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = line->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			line->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(line->env), buf, 0);
	free(buf);
	line->env_changed = 1;
	return (0);
}
