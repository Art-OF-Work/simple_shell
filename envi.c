#include "shell.h"

/**
 * _newenv - prints the current environment
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _newenv(line_t *line)
{
	print_list_str(line->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @line: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(line_t *line, const char *name)
{
	list_t *node = line->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _newsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @line: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _newsetenv(line_t *line)
{
	if (line->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(line, line->argv[1], line->argv[2]))
		return (0);
	return (1);
}

/**
 * _newunsetenv - Remove an environment variable
 * @line: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _newunsetenv(line_t *line)
{
	int i;

	if (line->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= line->argc; i++)
		_unsetenv(line, line->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(line_t *line)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	line->env = node;
	return (0);
}
