#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @line: the line struct
 * @location: location to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(line_t *line, char *location)
{
	struct stat st;

	(void)line;
	if (!location || stat(location, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @locationstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *locationstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (locationstr[i] != ':')
			buf[k++] = locationstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * locate_location - locates this cmd in the PATH string
 * @line: the line struct
 * @locationstr: the PATH string
 * @cmd: the cmd to locate
 *
 * Return: full location of cmd if found or NULL
 */
char *locate_location(line_t *line, char *locationstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *location;

	if (!locationstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(line, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!locationstr[i] || locationstr[i] == ':')
		{
			location = dup_chars(locationstr, curr_pos, i);
			if (!*location)
				_strcat(location, cmd);
			else
			{
				_strcat(location, "/");
				_strcat(location, cmd);
			}
			if (is_cmd(line, location))
				return (location);
			if (!locationstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
