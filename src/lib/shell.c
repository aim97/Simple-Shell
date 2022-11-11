#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "basic.h"
#include "env.h"
#include "internal.h"

char prompt[1000];
char cur_path[1000];

int main(int argc, char *argv[]) {
  char** command = (char**) malloc(100 * sizeof(char*));

  init_env();
  
  while (1) {
    sprintf(prompt, "%s >$ ", getcwd(cur_path, 1000));
    char* in = readline(prompt);
    int args_count = parse_command(in, command);
    if (!args_count) continue;

    // printf("Command recieved: %s, with %d args\n", command[0], args_count - 1);
    // for (; i < args_count;i++) printf("argument %d: %s\n", i, command[i]);

    int internal_code = is_internal(command[0]);
    
    if (internal_code == -1) {
      char* command_path = find_command(command[0]);
      command[0] = command_path;
      // printf("Command path %s\n", command_path);
      run_command(command);
    } else {
      // printf("Internal command %s recieved, code %d\n", command[0], internal_code);
      run_internal_command(internal_code, args_count - 1, (char**)&command[1]);
    }
  }
  return 0;
}