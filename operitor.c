#include "shell.h"

/**
 * Check_chain - test if current char in buffer is a chain delimeter
 * @line: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int Check_chain(line_t *line, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		line->cmd_buf_type = OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		line->cmd_buf_type = AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		line->cmd_buf_type = CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @line: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(line_t *line, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (line->cmd_buf_type == AND)
	{
		if (line->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (line->cmd_buf_type == OR)
	{
		if (!line->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * change_alias - replaces an aliases in the tokenized string
 * @line: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(line_t *line)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(line->alias, line->argv[0], '=');
		if (!node)
			return (0);
		free(line->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		line->argv[0] = p;
	}
	return (1);
}

/**
 * change_var - replaces vars in the tokenized string
 * @line: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_var(line_t *line)
{
	int i = 0;
	list_t *node;

	for (i = 0; line->argv[i]; i++)
	{
		if (line->argv[i][0] != '$' || !line->argv[i][1])
			continue;

		if (!_strcmp(line->argv[i], "$?"))
		{
			change_str(&(line->argv[i]),
				_strdup(to_number(line->status, 10, 0)));
			continue;
		}
		if (!_strcmp(line->argv[i], "$$"))
		{
			change_str(&(line->argv[i]),
				_strdup(to_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(line->env, &line->argv[i][1], '=');
		if (node)
		{
			change_str(&(line->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		change_str(&line->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * change_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
