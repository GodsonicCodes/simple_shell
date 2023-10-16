/* Shell.h*/

#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <fcntl.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>



/* This is for read/write buffers */
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024


/* This is for command chaining */
#define CMD_NORM	0
#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_OR		1

extern char **environ;
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

/* This is for convert_number() */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* We use 1 if using system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0





/**
 * @next: points to the next node
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 */



typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;



/**
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 */


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
    char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int argc;
	unsigned int line_count;
	int err_num;
	int status;
    int linecount_flag;
	int env_changed;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;



#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}



/**
 * 
 *@type: is the builtin command flag.
 *@func: is the function.
 *struct builtin - this contains a builtin string and related function.
 */


typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;




/* For toem_shloop.c */
int hsh(info_t *, char **);
void fork_cmd(info_t *);
int find_builtin(info_t *);
void find_cmd(info_t *);


/* For toem_parser.c */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);



/* For toem_errors.c */
int _putfd(char c, int fd);
int _eputchar(char);
int _putsfd(char *str, int fd);
void _eputs(char *);


/* For toem_string.c */
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);



/* For toem_string1.c */
char *_strdup(const char *);
char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);



/* For toem_exits.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);



/* For toem_realloc.c */
void ffree(char **);
void *_realloc(void *ptr, unsigned int new_size);
char *_memset(char *, char, unsigned int);



/* For toem_atoi.c */
int interactive(info_t *);
int _isalpha(int);
int _atoi(char *);
int is_delim(char, char *);



/* For toem_errors1.c */
void print_error(info_t *, char *);
int _erratoi(char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
int print_d(int, int);



/* For toem_builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);



/* For toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);



/* For toem_getline.c */
void sigintHandler(int);
ssize_t _getline(info_t *, char **, size_t *);
ssize_t read_buf(info_t *info, char *buf, size_t *len);
ssize_t get_input(info_t *);


/* For toem_getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);



/* For toem_environ.c */
int _myenv(info_t *);
char *_getenv(info_t *, const char *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);



/* For toem_getenv.c */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);



/* For toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int read_history(info_t *info);



/* For toem_lists.c */
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);


/* For toem_lists1.c */
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
size_t list_len(const list_t *);


/* For toem_vars.c */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int replace_alias(info_t *);

/* For toem_memory.c */
int bfree(void **);

/* For toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* For loophsh.c */
int loophsh(char **);


#endif
