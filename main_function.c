#include "shell.h"

/**
 * simplesh - main shell loop
 * @line: the parameter & return line struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int simplesh(line_t *line, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_line(line);
		if (interactive(line))
			_puts("$ ");
		_eputchar(BUF_STOP);
		r = get_input(line);
		if (r != -1)
		{
			set_line(line, av);
			builtin_ret = locate_builtin(line);
			if (builtin_ret == -1)
				locate_cmd(line);
		}
		else if (interactive(line))
			_putchar('\n');
		free_line(line, 0);
	}
	W_history(line);
	free_line(line, 1);
	if (!interactive(line) && line->status)
		exit(line->status);
	if (builtin_ret == -2)
	{
		if (line->err_num == -1)
			exit(line->status);
		exit(line->err_num);
	}
	return (builtin_ret);
}

/**
 * locate_builtin - locates a builtin command
 * @line: the parameter & return line struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locate_builtin(line_t *line)
{
	int i, built_in_ret = -1;
	cmd_table builtintbl[] = {
		{"exit", _newexit},
		{"env", _newenv},
		{"help", _newhelp},
		{"history", _newhistory},
		{"setenv", _newsetenv},
		{"unsetenv", _newunsetenv},
		{"cd", _newcd},
		{"alias", _newalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(line->argv[0], builtintbl[i].type) == 0)
		{
			line->line_count++;
			built_in_ret = builtintbl[i].func(line);
			break;
		}
	return (built_in_ret);
}

/**
 * locate_cmd - locates a command in PATH
 * @line: the parameter & return line struct
 *
 * Return: void
 */
void locate_cmd(line_t *line)
{
	char *location = NULL;
	int i, k;

	line->location = line->argv[0];
	if (line->linecount_flag == 1)
	{
		line->line_count++;
		line->linecount_flag = 0;
	}
	for (i = 0, k = 0; line->arg[i]; i++)
		if (!is_delim(line->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	location = locate_location(line, _getenv(line, "PATH="), line->argv[0]);
	if (location)
	{
		line->location = location;
		fork_cmd(line);
	}
	else
	{
		if ((interactive(line) || _getenv(line, "PATH=")
			|| line->argv[0][0] == '/') && is_cmd(line, line->argv[0]))
			fork_cmd(line);
		else if (*(line->arg) != '\n')
		{
			line->status = 127;
			write_error(line, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @line: the parameter & return line struct
 *
 * Return: void
 */
void fork_cmd(line_t *line)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(line->location, line->argv, take_environ(line)) == -1)
		{
			free_line(line, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(line->status));
		if (WIFEXITED(line->status))
		{
			line->status = WEXITSTATUS(line->status);
			if (line->status == 126)
				write_error(line, "Permission denied\n");
		}
	}
}
