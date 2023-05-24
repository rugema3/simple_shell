#ifndef _STRUCT_H_
#define _STRUCT_H_

#include"shell.h"

/* structs' list */

/**
 * struct CustomShellData - Structure to hold custom shell data
 * @arguments: Array of strings representing command-line arguments
 * @input_data: String representing user input or input data
 * @parsed_arguments: Array of strings representing parsed arguments
 * @operation_status: Integer representing the status or result of an operation
 * @counter_value: Integer used for counting or iteration
 * @environment: Array of strings representing environment variables
 * @process_identifier: String representing the process ID or identifier
 *
 * Description: Structure to encapsulate and store custom shell-related data.
 */
typedef struct CustomShellData
{
	char **arguments;
	char *input_data;
	char **parsed_arguments;
	int operation_status;
	int counter_value;
	char **environment;
	char *process_identifier;
} CustomShellData_t;

/**
 * struct custom_separator_node - Custom node for separator linked list
 * @custom_character: Separator character
 * @next: Pointer to the next node
 *
 * Description: Custom node structure for a linked list of separators.
 */
typedef struct custom_separator_node
{
	char custom_character;
	struct custom_separator_node *next;
} custom_separator_node_t;

/**
 * struct custom_line_list - Single linked list for storing lines
 * @text: Line of text
 * @next: Pointer to the next node
 *
 * Description: Single linked list structure for storing lines of text.
 */
typedef struct custom_line_list
{
	char *text;
	struct custom_line_list *next;
} custom_line_list_t;

/**
 * struct custom_var_list - Single linked list for storing variables
 * @variable_length: Length of the variable
 * @variable_value: Value of the variable
 * @value_length: Length of the value
 * @next: Pointer to the next node
 *
 * Description: Single linked list structure for storing variables.
 */
typedef struct custom_var_list
{
	int variable_length;
	char *variable_value;
	int value_length;
	struct custom_var_list *next;
} custom_var_list_t;

/**
 * struct custom_builtin_s - Custom Builtin struct for command arguments.
 * @command_name: The name of the custom command i.e cd, exit, env
 * @function_ptr: Pointer to the function associated with the command.
 */
typedef struct custom_builtin_s
{
	char *command_name;
	int (*function_ptr)(CustomShellData_t *datash);
} custom_builtin_t;

#endif

