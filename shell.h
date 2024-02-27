#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define MAX_BUF_SIZE 1024
#define BUF_STOP -1

/* for command chaining */
#define NORM	0
#define OR		1
#define AND		2
#define CHAIN	3

/* for to_number() */
#define TO_LOWERCASE	1
#define TO_UNSIGNED	2

/* 1 if using system getline() */
#define GETLINE 0
#define STRTOK 0

#define HIST_PATH_FILE	".simple_shell_history"

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passline - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@location: a string location for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passline
{
	char *arg;
	char **argv;
	char *location;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} line_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


#define HIST_MAX_RAW	4096

extern char **environ;


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(line_t *);
} cmd_table;


/* main_function.c */
int simplesh(line_t *, char **);
int locate_builtin(line_t *);
void locate_cmd(line_t *);
void fork_cmd(line_t *);

/* File_location.c */
int is_cmd(line_t *, char *);
char *dup_chars(char *, int, int);
char *locate_location(line_t *, char *, char *);

/* err_str.c: */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* str_file2.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* str_file3.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* helper.c */
int interactive(line_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* helper1.c */
int _erratoi(char *);
void write_error(line_t *, char *);
int write_dicemal(int, int);
char *to_number(long int, int, int);
void rm_comments(char *);

/* str_file.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* str_file1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* CMD.c */
int _newexit(line_t *);
int _newcd(line_t *);
int _newhelp(line_t *);

/* Getline.c */
ssize_t get_input(line_t *);
int _getline(line_t *, char **, size_t *);
void sigintHandler(int);

/* Line_sh.c */
void clear_line(line_t *);
void set_line(line_t *, char **);
void free_line(line_t *, int);

/* CMD1.c */
int _newhistory(line_t *);
int _newalias(line_t *);

/* envi.c */
char *_getenv(line_t *, const char *);
int _newenv(line_t *);
int _newsetenv(line_t *);
int _newunsetenv(line_t *);
int populate_env_list(line_t *);

/* envi1.c */
char **take_environ(line_t *);
int _unsetenv(line_t *, char *);
int _setenv(line_t *, char *, char *);

/* history.c */
char *locate_history_file(line_t *line);
int W_history(line_t *line);
int R_history(line_t *line);
int create_history_list(line_t *line, char *buf, int linecount);
int history_back_number(line_t *line);

/* Linkdlist.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* operitor.c */
int Check_chain(line_t *, char *, size_t *);
void check_chain(line_t *, char *, size_t *, size_t, size_t);
int change_alias(line_t *);
int change_var(line_t *);
int change_str(char **, char *);

/* Linkdlist1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif
