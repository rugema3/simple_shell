#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include"struct.h" /* where the structs used in this project are located */
#include"environment.h"

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Function prototypes */

sep_list *append_separator(sep_list **separatorHead, char separatorChar);
void release_separator_memory(sep_list **separatorHead);
line_list *append_line(line_list **lineHead, char *lineStr);
void release_line_memory(line_list **lineHead);
r_var *append(r_var **variableHead,
		int varLength, char *value, int valueLength);
void cleanup(r_var **variableHead);
char *concatenate_strings(char *destination, const char *source);
char *copy_string(char *destination, char *source);
int compare_strings(char *str1, char *str2);
char *locate_char(char *str, char searchChar);
int prefix_length(char *str, char *acceptedChars);
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int data_size);

void *resize_memory(void *old_ptr, unsigned int prev_size,
		unsigned int new_size);

char **resize_double_ptr(char **old_ptr,
		unsigned int prev_size, unsigned int new_size);

char *split_str(char input_string[], const char *delimiter);
int compare_characters(char input_string[], const char *delimiter);
int get_str_length(const char *input_string);
char *duplicate_str(const char *input_string);
int is_digit(const char *input_string);
void reverse_string(char *str);
int count_char_repetition(char *input_str, int index);
int find_syntax_errors(char *input_str, int index, char last_char);
int locate_first_char(char *input_str, int *index_ptr);
void output_syntax_error(data_shell *data_sh, char *input_str,
		int index, int bool_flag);
int validate_syntax(data_shell *data_sh, char *input_str);
char *filterComments(char *in);
void interactive_shell(data_shell *datash);
char *getLineInput(int *isEof);
char *swapCharacters(char *input, int bool);
void addSeparatorsAndCommands(sep_list **head_s,
		line_list **head_l, char *input);

void goToNextCommand(sep_list **list_s, line_list **list_l,
		data_shell *datash);

int splitAndExecuteCommands(data_shell *datash, char *input);
char **tokenizeInputString(char *input);

char *replaceVariablesInInput(char *input, data_shell *datash);

char *replaceStringWithVariables(r_var **head, char *input, char *newInput,
		int newLength);

int searchSpecialVariables(r_var **head, char *input,
		char *status, data_shell *data);

void searchEnvironmentVariable(r_var **head, char *input, data_shell *data);
void assignLine(char **lineptr, size_t *size, char *buffer, size_t length);
ssize_t readLine(char **lineptr, size_t *size, FILE *stream);
int find_builtin(data_shell *datash);
int executeCommand(data_shell *datash);
int check_command_error(char *dir, data_shell *datash);
int check_executable(data_shell *datash);
char *find_executable_path(char *cmd, char **_environ);
int check_colon_dir(char *path, int *index);
void changeToParentDirectory(data_shell *datash);
void changeToDirectory(data_shell *datash);
void changeToPreviousDirectory(data_shell *datash);
void changeToHomeDirectory(data_shell *datash);
int changeDirectoryShell(data_shell *datash);
int (*find_builtin_function(char *cmd))(data_shell *);
int terminate(data_shell *datash);
int calculate_length(int num);
char *convert_int_to_string(int num);
int convert_string_to_int(char *str);

char *concatenate_cd_error(data_shell *data_sh, char *message,
		char *error_output, char *counter_str);

char *generate_not_found_error(data_shell *data_sh);
char *generate_cd_error(data_shell *data_sh);
char *generate_error_msg(data_shell *data_sh);
char *error_get_alias(char **args);
char *generate_env_error(data_shell *data_sh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *generate_permission_error(data_shell *data_sh);
int handle_exit_status(data_shell *datash, int eval);
void prompt(int sig);
void display_env_help(void);
void display_setenv_help(void);
void display_unsetenv_help(void);
void display_general_help(void);
void display_exit_help(void);
void display_help_command(void);
void display_alias_help(void);
void display_cd_help(void);
int show_help_info(data_shell *datash);
void deallocate_data_shell(data_shell *datash);
void setup_data_shell(data_shell *datash, char **arguments);

#endif /* SHELL_H */
