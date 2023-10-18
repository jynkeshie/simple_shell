#ifndef HEADER_FILE_H
#define HEADER_FILE_H

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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
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
} list_t;

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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 * struct built_in - contains a built_in string and related function
 * @type: the built_in command flag
 * @func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

void print_prompt(void);

int hsh(info_t *, char **);
int builtin_command(info_t *);
void command_path(info_t *);
void fork_command(info_t *);

int file_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *locate_path(info_t *, char *, char *);

int loophsh(char **);

void show_error_msg(char *);
int _write_char_to_stderr(char);
int _write_to_fd(char c, int fd);
int _write_string_to_fd(char *str, int fd);

int string_len(char *);
int string_cmp(char *, char *);
char *needle_starts(const char *, const char *);
char *string_conc(char *, char *);

char *string_cpy(char *, char *);
char *string_dpl(const char *);
void string_puts(char *);
int write_char(char);

char *copy_string(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_char(char *, char);

char **tokenize_string(char *, char *);
char **split_string(char *, char);

char *fill_memory(char *, char, unsigned int);
void free_string(char **);
void *resize_memory_block(void *, unsigned int, unsigned int);

int free_pointer(void **);

int interactive_mode(info_t *);
int char_delim(char, char *);
int char_alpha(int);
int conv_str_int(char *);

int string_to_int(char *);
void print_error(info_t *, char *);
int print_dec(int, int);
char *converts_number(long int, int, int);
void erase_comments(char *);

int _shellexit(info_t *);
int _changedir(info_t *);
int _seehelp(info_t *);

int _allhistory(info_t *);
int _myalias(info_t *);

ssize_t get_line_input(info_t *);
int get_input_line(info_t *, char **, size_t *);
void blockCtrlC(int);

void clear_info(info_t *);
void initialize_info(info_t *, char **);
void free_info(info_t *, int);

char *_environment_variable(info_t *, const char *);
int _listenv(info_t *);
int _setenvironment(info_t *);
int _unsetenvironment(info_t *);
int initialize_env(info_t *);

char **copy_env_strings(info_t *);
int remove_env_variable(info_t *, char *);
int add_env_variable(info_t *, char *, char *);

char *see_file_history(info_t *info);
int save_history_to_file(info_t *info);
int load_history_from_file(info_t *info);
int add_history_entry(info_t *info, char *buf, int linecount);
int update_history_line_numbers(info_t *info);

list_t *prepend_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t output_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void clear_list(list_t **);

size_t count_nodes(const list_t *);
char **list_to_strings(list_t *);
size_t show_list(const list_t *);
list_t *find_node_with_prefix(list_t *, char *, char);
ssize_t retrieve_node_index(list_t *, list_t *);

int char_del(info_t *, char *, size_t *);
void monitor_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_string(info_t *);
int replace_vars_string(info_t *);
int replace_data_string(char **, char *);

#endif

