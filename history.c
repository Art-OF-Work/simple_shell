#include "shell.h"

/**
 * locate_history_file - gets the history file
 * @line: parameter struct
 *
 * Return: allocated string containg history file
 */

char *locate_history_file(line_t *line)
{
	char *buf, *dir;

	dir = _getenv(line, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_PATH_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_PATH_FILE);
	return (buf);
}

/**
 * W_history - creates a file, or appends to an existing file
 * @line: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int W_history(line_t *line)
{
	ssize_t fd;
	char *filename = locate_history_file(line);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = line->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_STOP, fd);
	close(fd);
	return (1);
}

/**
 * R_history - reads history from file
 * @line: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int R_history(line_t *line)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = locate_history_file(line);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_history_list(line, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_history_list(line, buf + last, linecount++);
	free(buf);
	line->histcount = linecount;
	while (line->histcount-- >= HIST_MAX_RAW)
		delete_node_at_index(&(line->history), 0);
	history_back_number(line);
	return (line->histcount);
}

/**
 * create_history_list - adds entry to a history linked list
 * @line: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int create_history_list(line_t *line, char *buf, int linecount)
{
	list_t *node = NULL;

	if (line->history)
		node = line->history;
	add_node_end(&node, buf, linecount);

	if (!line->history)
		line->history = node;
	return (0);
}

/**
 * history_back_number - renumbers the history linked list after changes
 * @line: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int history_back_number(line_t *line)
{
	list_t *node = line->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (line->histcount = i);
}
