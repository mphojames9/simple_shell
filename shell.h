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
/* to denote read or write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
/* to denote command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
/* to denote convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
/* 1 to denote using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
extern char **environ;
/**
* struct liststr - singly linked list format
* @num: the number field to note
* @str: a string to work with
* @next: points to the next node in the program
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;
/**
* struct passinfo - contains pseudo-arguements to integrate to a function,
* in order to allow uniform prototype for function pointer struct
* @arg: a string generated through getline containing arguements
* @argv:an array of strings generated from through arg
* @path: a string path for the on-current command
* @argc: the argument counts
* @line_count: the error counts
* @err_num: error code for exit()s
* @linecount_flag: if on count then this line of input
* @fname: the program's filename
* @env: linked-list local copy of environ
* @environ: custom-modified copy of environ from LL env
* @history: history node
* @alias: alias node
* @env_changed:this is on if environ was changed
* @status: return status of the last executedd command
* @cmd_buf: address of pointer to cmd_buf, which is on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input input
* @histcount: the history line number count counted
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
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}
/**
* struct builtin - contains a builtin string as well as related function
* @type: the builtin command flag flag
* @func: the function function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;
/* toem_shloop.c */
int hsh_int(info_t *, char **);
int builtin_finder(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
/* toem_parser.c */
int cmd_checker(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
/* loophsh_int.c */
int loophsh_int(char **);
/* toem_errors.c */
void eputs_voider(char *);
int eputchar_intiger(char);
int putfd_intiger(char c, int fd);
int putsfd_intiger(char *str, int fd);
/* toem_string.c */
int strlen_length(char *);
int strcmp_lexicogarphic(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int putchar_intiger(char);
/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);
/* toemrelocator.c */
char *_memset(char *, char, unsigned int);
void _safer(char **);
void *relocator(void *, unsigned int, unsigned int);
/* toem_memory.c */
int bsafer(void **);
/* toeminspect_atoi.c */
int interactive_inspect(info_t *);
int delim_check(char, char*);
int isalpha_inspect(int);
int inspect_atoi(char *);
/* toem_errors1.c */
int errational(char *);
void error_printer(info_t *, char *);
int direct_print(int, int);
char *convert_number(long int, int, int);
void comments_remover(char *);
/* toem_builtin.c */
int my_evacuation(info_t *);
int directory_change(info_t *);
int _assist(info_t *);
/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);
/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
/* toem_getinfo.c */
void information_clearing(info_t *);
void informantion_setting(info_t*, char **);
void information_freeing(info_t *, int);
/* toem_environ.c */
char *_getenv(info_t *, const char *);
int environ_checker(info_t *);
int selfenv_setter(info_t *);
int selfdeenv_setter(info_t *);
int env_list_populator(info_t *);
/* toem_getenv.c */
char **get_environ(info_t *);
int deenv_setter(info_t *, char *);
int env_setter(info_t *, char *, char *);
/* toem_history.c */
char *history_file_locater(info_t *info);
int history_writer(info_t *info);
int history_reader(info_t *info);
int history_builder_list(info_t *info, char *buf, int linecount);
int history_renumbered(info_t *info);
/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void list_freer(list_t **);
/* toem_lists1.c */
size_t list_len(const list_t *);
char **to_the_strings_lister(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
/* toem_vars.c */
int chain_checks(info_t *, char *, size_t *);
void chain_inspect(info_t *, char *, size_t *, size_t, size_t);
int alias_replacement(info_t *);
int vars_replacement(info_t *);
int string_replacement(char **, char *);
#endif
