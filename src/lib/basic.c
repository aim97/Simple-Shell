#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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
  argv[argc] = NULL;

  return argc;
}

int run_command(char** args) {
  int rc = fork();
  if (rc == 0) {
    execvp(args[0], args);  // runs word count
  }
  wait(NULL);
}
