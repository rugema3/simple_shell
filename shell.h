#ifndef _MAIN_H_
#define _MAIN_H_

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
#include"struct.h"
#include"environment.h"

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"
#define EXIT_STATUS_MOD 256

custom_separator_node_t *append_separator
	(custom_separator_node_t **separatorHead, char separatorChar);

void release_separator_memory(custom_separator_node_t **separatorHead);

custom_line_list_t *append_line(custom_line_list_t **lineHead, char *lineStr);
void release_line_memory(custom_line_list_t **lineHead);
custom_var_list_t *append(custom_var_list_t **variableHead,
		int varLength, char *value, int valueLength);
void cleanup(custom_var_list_t **variableHead);
char *concatenate_strings(char *destination, const char *source);
char *copy_string(char *destination, char *source);
int compare_strings(char *str1, char *str2);
char *locate_char(char *str, char searchChar);
int prefix_length(char *str, char *acceptedChars);
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int data_size);

void *resize_memory(void *old_ptr, unsigned int prev_size,
		unsigned int new_size);

char **resize_double_ptr(char **old_ptr, unsigned int prev_size,
		unsigned int new_size);

char *split_str(char input_string[], const char *delimiter);
int compare_characters(char input_string[], const char *delimiter);
int get_str_length(const char *input_string);
char *duplicate_str(const char *input_string);
int is_digit(const char *input_string);
void reverse_string(char *str);
int count_char_repetition(char *input_str, int index);
int find_syntax_errors(char *input_str, int index, char last_char);
int locate_first_char(char *input_str, int *index_ptr);
void output_syntax_error(CustomShellData_t *data_sh,
		char *input_str, int index, int bool_flag);
int validate_syntax(CustomShellData_t *data_sh, char *input_str);
char *filterComments(char *in);
void interactive_shell(CustomShellData_t *datash);
char *getLineInput(int *isEof);
char *swapCharacters(char *input, int bool);

void addSeparatorsAndCommands
	(custom_separator_node_t **head_s, custom_line_list_t **head_l, char *input);

void goToNextCommand(custom_separator_node_t **list_s,
		custom_line_list_t **list_l, CustomShellData_t *datash);

int splitAndExecuteCommands(CustomShellData_t *datash, char *input);

char **tokenizeInputString(char *input);

char *replaceVariablesInInput(char *input, CustomShellData_t *datash);

char *replaceStringWithVariables(custom_var_list_t **head, char *input,
		char *newInput, int newLength);

int searchSpecialVariables(custom_var_list_t **head, char *input, char *status,
		CustomShellData_t *data);

void searchEnvironmentVariable(custom_var_list_t **head, char *input,
		CustomShellData_t *data);

void assignLine(char **lineptr, size_t *size, char *buffer, size_t length);
ssize_t readLine(char **lineptr, size_t *size, FILE *stream);
int find_builtin(CustomShellData_t *datash);
int executeCommand(CustomShellData_t *datash);
int check_command_error(char *dir, CustomShellData_t *datash);
int check_executable(CustomShellData_t *datash);
char *find_executable_path(char *cmd, char **_environ);
int check_colon_dir(char *path, int *index);
void changeToParentDirectory(CustomShellData_t *datash);
void changeToDirectory(CustomShellData_t *datash);
void changeToPreviousDirectory(CustomShellData_t *datash);
void changeToHomeDirectory(CustomShellData_t *datash);
int changeDirectoryShell(CustomShellData_t *datash);
int (*find_builtin_function(char *cmd))(CustomShellData_t *);
int terminate(CustomShellData_t *datash);
int calculate_length(int num);
char *convert_int_to_string(int num);

int convert_string_to_int(char *str);

char *concatenate_cd_error(CustomShellData_t *data_sh, char *message,
		char *error_output, char *counter_str);

char *generate_not_found_error(CustomShellData_t *data_sh);
char *generate_cd_error(CustomShellData_t *data_sh);
char *generate_error_msg(CustomShellData_t *data_sh);
char *error_get_alias(char **args);
char *generate_env_error(CustomShellData_t *data_sh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *generate_permission_error(CustomShellData_t *data_sh);
int handle_exit_status(CustomShellData_t *datash, int eval);
void prompt(int sig);
void display_env_help(void);
void display_setenv_help(void);
void display_unsetenv_help(void);
void display_general_help(void);
void display_exit_help(void);
void display_help_command(void);
void display_alias_help(void);
void display_cd_help(void);
int show_help_info(CustomShellData_t *datash);
void setup_CustomShellData_t(CustomShellData_t *datash, char **arguments);
void deallocate_CustomShellData_t(CustomShellData_t *datash);

#endif /* MAIN_H */
