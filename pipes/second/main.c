#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define WRITE_END 1 
#define READ_END 0

int main() {
  pid_t p;
  int left[2], right[2];
  pipe(left);
  pipe(right);
  
  if((p = fork()) == 0) {
    dup2(left[WRITE_END], STDOUT_FILENO);
    system("echo a");
    sleep(10);
  } 
  close(left[WRITE_END]);
  if(p == 0) exit(EXIT_SUCCESS);

  if((p = fork()) == 0) {
    dup2(left[READ_END], STDIN_FILENO);
    dup2(right[WRITE_END], STDOUT_FILENO);
    system("awk '{print $1\"b\"}'");
    sleep(20);
  } 
  close(left[READ_END]);
  close(right[WRITE_END]);
  if(p == 0) exit(EXIT_SUCCESS);

  if((p = fork()) == 0) {
    dup2(right[READ_END], STDIN_FILENO);
    system("awk '{print $1\"c\"}'");
    sleep(30);
  } 
  close(right[READ_END]);
  if(p == 0) exit(EXIT_SUCCESS);
  wait(NULL);
  wait(NULL);
  wait(NULL);

  return 0;
}
