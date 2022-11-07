#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BIN_PATH "./bin/"

int read_command(char* in, char** argv) {
  int argc = 0; 
  char *tmp = strtok(in, " ");
  while(tmp != NULL) {
    if (*tmp == '\"') {
      argv[argc] = tmp+1;
      tmp = strtok(NULL, "\"");
    }
    else {
      argv[argc] = tmp;
      tmp = strtok(NULL, " ");
    }
    argc += 1;
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
    int args_count = read_command(in, command);
    printf("Command recieved: %s\n", command[0]);
    char* command_path = find_command(command[0]);
    command[0] = command_path;
    run_command(command);
  }
  return 0;
}