#ifndef ENV_H
#define ENV_H

void init_env();

char* get_env_variable(char* );

int set_env_variable(char* , char *);

void disp_env();

char* find_command(char* command);

#endif