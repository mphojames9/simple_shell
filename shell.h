#ifndef _SHELL_H_
#define _SHELL_H_
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USEgetline_checker 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

extern char **environ;
/**
* struct liststr - singly linked list
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} record_m;
/**
* @env: copy of environ for linked list local
* @env: copy of environ for linked list local
* @environ: modified copy of environ from LL env
* @history: history node
* @alias: alias node
* @env_changed: if environ
* @status:last exec'd command return status
* @cmd_buf: cmd_buf, on if chaining address of pointer
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: read line input
* @histcount: history line num count
* @line_count: mistake count
* @err_num: the mistake code for exit()s
* @linecount_flag: line of input
* @fname: program filename
* struct passinfo - have pseudo-arguements that pases the function
* @arg: a string
* @argv:an strings created from arg
* @path: current command string paff
* @argc: argument count
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
char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}
/**
* struct builtin - contains a builtin string and related function
* struct builtin - have a builtin string and related function
* @type: command flag
* @func: function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

size_t list_len(const record_m *);
char **record_mo_strings(record_m *);
size_t print_list(const record_m *);
record_m *node_starts_with(record_m *, char *, char);
ssize_t get_node_index(record_m *, record_m *);

record_m *add_node(record_m **, const char *, int);
record_m *add_node_end(record_m **, const char *, int);
size_t print_list_str(const record_m *);
int node_at_index_deletion(record_m **, unsigned int);
void free_list(record_m **);

int hsh(info_t *, char **);
int builtin_locator(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

char **get_environ(info_t *);
int unsetenv2_checker(info_t *, char *);
int setenv2_checker(info_t *, char *, char *);

int cmd_checker(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

char *get_history_file(info_t *info);
int history_writer(info_t *info);
int history_reader(info_t *info);
int history_list_builder(info_t *info, char *buf, int linecount);
int history_renumber(info_t *info);

int hsh_loop(char **);

void _eputs(char *);
int eputchar_chr(char);
int putfd_char(char c, int fd);
int putsfd_char(char *str, int fd);

int strlen_char(char *);
int strcmp_char(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

int chain_checker(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replacement(info_t *);
int replace_vars(info_t *);
int string_replacement(char **, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int putchar_char(char);

char *_getenv(info_t *, const char *);
int env_checker(info_t *);
int setenv_checker(info_t *);
int unsetenv_checker(info_t *);
int env_list_population(info_t *);

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
#endif
