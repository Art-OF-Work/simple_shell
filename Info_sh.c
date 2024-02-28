#include "shell.h"

/**
 * clear_line - initializes line_t struct
 * @line: struct address
 */
void clear_line(line_t *line)
{
	line->arg = NULL;
	line->argv = NULL;
	line->location = NULL;
	line->argc = 0;
}

/**
 * set_line - initializes line_t struct
 * @line: struct address
 * @av: argument vector
 */
void set_line(line_t *line, char **av)
{
	int i = 0;

	line->fname = av[0];
	if (line->arg)
	{
		line->argv = strtow(line->arg, " \t");
		if (!line->argv)
		{

			line->argv = malloc(sizeof(char *) * 2);
			if (line->argv)
			{
				line->argv[0] = _strdup(line->arg);
				line->argv[1] = NULL;
			}
		}
		for (i = 0; line->argv && line->argv[i]; i++)
			;
		line->argc = i;

		change_alias(line);
		change_var(line);
	}
}

/**
 * free_line - frees line_t struct fields
 * @line: struct address
 * @all: true if freeing all fields
 */
void free_line(line_t *line, int all)
{
	ffree(line->argv);
	line->argv = NULL;
	line->location = NULL;
	if (all)
	{
		if (!line->cmd_buf)
			free(line->arg);
		if (line->env)
			free_list(&(line->env));
		if (line->history)
			free_list(&(line->history));
		if (line->alias)
			free_list(&(line->alias));
		ffree(line->environ);
			line->environ = NULL;
		bfree((void **)line->cmd_buf);
		if (line->readfd > 2)
			close(line->readfd);
		_putchar(BUF_STOP);
	}
}
