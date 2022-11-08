#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BIN_PATH "./bin/"

int parse_command(char* in, char** argv) {
  int argc = 0, reader_idx = 0, writer_idx, len = strlen(in);
  char stop_at;
  while(reader_idx < len) {
    while(in[reader_idx] == ' ') ++reader_idx; // skip spaces
    if (in[reader_idx] == '\"') {
      stop_at = '\"';
      reader_idx++;
    } else stop_at = ' ';

    char* tmp = (char*) malloc(sizeof(char) * 100);
    writer_idx = 0;
    
    while(reader_idx < len && in[reader_idx] != stop_at) {
      tmp[writer_idx++] = in[reader_idx++];
    }
    if (stop_at == '\"') ++reader_idx;
    tmp[writer_idx] = '\0';
    argv[argc] = tmp;
    argc += 1;

    // skip trailing spaces
    while(in[reader_idx] == ' ') ++reader_idx; // skip spaces
  }

  return argc;
}

char* find_command(char* command) {
  char* isPath = strchr(command, '/');
  char* path;
  if (isPath == NULL) {
    path = strcat(strdup(BIN_PATH), command);
  } else {
    path = command;
  }
  return path;
}

int run_command(char** args) {
  int rc = fork();
  if (rc == 0) {
    execvp(args[0], args);  // runs word count
  }
  wait(NULL);
}

int main(int argc, char *argv[]) {
  while (1) {
    char* in = readline(">$ ");
    char** command = (char**) malloc(100 * sizeof(char*));
    int args_count = parse_command(in, command);
    printf("Command recieved: %s, with %d args\n", command[0], args_count - 1);
    int i = 0;
    for (; i < args_count;i++) printf("argument %d: %s\n", i, command[i]);
    char* command_path = find_command(command[0]);
    command[0] = command_path;
    run_command(command);
  }
  return 0;
}