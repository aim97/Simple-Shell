#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "internal.h"
#include "env.h"

#define INTERNAL_COMMANDS_COUNT 4

struct Internal_command {
  char* name;
  int (*exec)(int argc, char* args[]);
};

static int get_cwd() {
  char* v = (char*) malloc(sizeof (char)*1000);
  char* ret = getcwd(v, 1000);
  if (ret != NULL) {
    printf("CWD: %s\n", v);
    free(v);
    return 0;
  }
  free(v);
  return 1;
}

static int cd(int argc, char** args) {
  if (argc == 0) {
    return get_cwd();
  }
  return chdir(args[0]);
}

static int hello (int argc, char** args) {
  printf("hello again\n");
  return 0;
}


int env(int argc, char** args) {
  disp_env();
  return 0;
}

int set(int argc, char** args) {
  if (argc < 2) {
    return 1;
  }
  set_env_variable(args[0], args[1]);
  return 0;
}

static struct Internal_command internal_commands[] = {
  { "env", &env },
  { "cd", &cd },
  { "set", &set },
  { "hello", &hello }
};

int is_internal(char* command) {
  int i = 0,idx = -1;
  for (;i < INTERNAL_COMMANDS_COUNT;i++) {
    int ret = strcmp(internal_commands[i].name, command);
    if (ret == 0) {
      idx = i;
      break;
    }
  }
  return idx;
}

int run_internal_command(int code, int argc, char** argv) {
  return internal_commands[code].exec(argc, argv);
}