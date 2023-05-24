#ifndef _SHELL_H_
#define _SHELL_H_
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
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
/* 1 if using system getline() */
#define USEgetline_checker 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
extern char **environ;
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
} record_m;
/**
* struct passinfo - contains pseudo-arguements to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @path: a string path for the current command
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: the program filename
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @history: the history node
* @alias: the alias node
* @env_changed: on if environ was changed
* @status: the return status of the last exec'd command
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input
* @histcount: the history line number count
*/
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
record_m *env;
record_m *history;
record_m *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}
/**
* struct builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int builtin_locator(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int cmd_checker(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int hsh_loop(char **);

void _eputs(char *);
int eputchar_chr(char);
int putfd_char(char c, int fd);
int putsfd_char(char *str, int fd);

int strlen_char(char *);
int strcmp_char(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int putchar_char(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int befree(void **);

int interactive_infor(info_t *);
int delim_check(char, char *);
int isalpha_check(int);
int atoi_check(char *);

int erratoi_check(char *);
void print_error(info_t *, char *);
int printing_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int _myevacuate(info_t *);
int cd_change(info_t *);
int _myassistance(info_t *);

int history_checker(info_t *);
int alias_checker(info_t *);

ssize_t get_input(info_t *);
int getline_checker(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *_getenv(info_t *, const char *);
int env_checker(info_t *);
int setenv_checker(info_t *);
int unsetenv_checker(info_t *);
int env_list_population(info_t *);

char **get_environ(info_t *);
int unsetenv2_checker(info_t *, char *);
int setenv2_checker(info_t *, char *, char *);

char *get_history_file(info_t *info);
int history_writer(info_t *info);
int history_reader(info_t *info);
int history_list_builder(info_t *info, char *buf, int linecount);
int history_renumber(info_t *info);

record_m *add_node(record_m **, const char *, int);
record_m *add_node_end(record_m **, const char *, int);
size_t print_list_str(const record_m *);
int node_at_index_deletion(record_m **, unsigned int);
void free_list(record_m **);

size_t list_len(const record_m *);
char **record_mo_strings(record_m *);
size_t print_list(const record_m *);
record_m *node_starts_with(record_m *, char *, char);
ssize_t get_node_index(record_m *, record_m *);

int chain_checker(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replacement(info_t *);
int replace_vars(info_t *);
int string_replacement(char **, char *);
#endif
