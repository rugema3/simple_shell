#ifndef ENV_HANDLING_H
#define ENV_HANDLING_H

#include "shell.h"

extern char **environ;

char *build_new_entry(char *name, char *value);
void change_env_variable(char *name, char *value, data_shell *datash);
int Update_environment(data_shell *datash);
int erase_env_variable(data_shell *datash);

int compare_environment_variable_name(const char *env_name,
		const char *input_name);

char *get_environment_variable(const char *input_name, char **_environ);
int print_environment_variables(data_shell *datash);


#endif /* ENV_HANDLING_H */

