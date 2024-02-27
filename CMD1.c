#include "shell.h"

/**
 * _newhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @line: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _newhistory(line_t *line)
{
	print_list(line->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @line: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(line_t *line, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(line->alias),
		get_node_index(line->alias, node_starts_with(line->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @line: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(line_t *line, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(line, str));

	unset_alias(line, str);
	return (add_node_end(&(line->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _newalias - mimics the alias builtin (man alias)
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _newalias(line_t *line)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (line->argc == 1)
	{
		node = line->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; line->argv[i]; i++)
	{
		p = _strchr(line->argv[i], '=');
		if (p)
			set_alias(line, line->argv[i]);
		else
			print_alias(node_starts_with(line->alias, line->argv[i], '='));
	}

	return (0);
}
