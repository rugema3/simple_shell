#ifndef ENV_HANDLING_H
#define ENV_HANDLING_H

#include "shell.h"

extern char **environ;

char *build_new_entry(char *name, char *value);

void change_env_variable(char *name, char *value,
		CustomShellData_t *datash);

int Update_environment(CustomShellData_t *datash);

int erase_env_variable(CustomShellData_t *datash);

int compare_environment_variable_name(const char *env_name,
		const char *input_name);

char *get_environment_variable(const char *input_name, char **_environ);

int print_environment_variables(CustomShellData_t *datash);


#endif /* ENV_HANDLING_H */

