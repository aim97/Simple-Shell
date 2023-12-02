#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "env.h"

#define PATH "/usr/bin/"

struct Env_variable {
  char* name;
  char* value;
};

static int variables_count = 0;
static struct Env_variable* env_variables[100];

static void add_entry (char* name, char* value) {
  env_variables[variables_count] = malloc(sizeof (struct Env_variable));
  env_variables[variables_count]->name = name;
  env_variables[variables_count]->value = value;
  variables_count++;
}

void init_env() {
  add_entry("PATH", PATH);
}

char* get_env_variable(char* name) {
  int i = 0;
  for(;i < variables_count;i++) {
    if (!strcmp(env_variables[i]->name, name)) {
      return env_variables[i]->value;
    }
  }
  return NULL;
}

int set_env_variable(char* name, char* value) {
  int i = 0;
  for(;i < variables_count;i++) {
    if (!strcmp(env_variables[i]->name, name)) {
      free(env_variables[i]->value);
      env_variables[i]->value = value;
      return 0;
    }
  }
  add_entry(name, value);
  return 0;
}

void disp_env() {
  int i = 0;
  for(;i < variables_count;i++) {
    printf("%s %s\n",env_variables[i]->name, env_variables[i]->value);
  }
}

char* find_command(char* command) {
  char* isPath = strchr(command, '/');
  char* path;
  if (isPath == NULL) {
    path = strcat(strdup(PATH), command);
  } else {
    path = command;
  }
  return path;
}