#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

// macros
#define WRITE_END 1
#define READ_END 0

// pipes
int adm[3] = {0};
char* cmds[3] = {0};


// for handling subprocesses 
// ----------------------------------
int pshsh(int pipadm); // returns EXIT_STATUS 
int pinit();  // returns last READ_END
void pfree(); 


// send command to a pipeline
// ----------------------------------
void psend(int out, char* left, char* middle, char* right);


// send command to a pipeline
// ----------------------------------
int main() {
  // init
  int out = pinit();

  // while getting user input
  char left[1024];
  while(fgets(left, 1024, stdin)) {
    // split
    char* right = strrchr(left, '|'); *(right++) = '\0';
    char* middle = strrchr(left, '|'); *(middle++) = '\0';
    // send 
    psend(out, left, middle, right);
  }

  // exit
  pfree();
  return 0;
}


// make three piped subprocesses, 
// sets global variables adm and pip
// returns READ_END of third pipe
// ----------------------------------
int pinit() {
  // init
  int pipfd[2], pipadm[2];
  int prev = 0;
  
  // while making subprocesses
  for(int i = 0; i < 3; i++) {
    // init 
    pipe(pipadm); // parent -> child
    pipe(pipfd);  // child -> child

    // parent
    if(fork()) {
      // close unused
      close(pipadm[READ_END]); 
      close(pipfd[WRITE_END]);
      // manage the pipe variables and loop
      adm[i] = pipadm[WRITE_END];
      if(prev) close(prev);
      prev = pipfd[READ_END];
      continue;
    }

    // child, close unused 
    close(pipadm[WRITE_END]);
    close(pipfd[READ_END]);

    // setup redirection
    if(prev) { dup2(prev, STDIN_FILENO); close(prev); }
    else close(STDIN_FILENO); // first subprocess is pure output
    dup2(pipfd[WRITE_END], STDOUT_FILENO);
    close(pipfd[WRITE_END]);

    // run shell-loop-thing and exit
    int status = pshsh(pipadm[READ_END]);
    exit(status);
  }

  // finished, return third READ_END
  return prev;
}


// exit all
// ----------------------------------
void pfree() {
  // for each process
  for(int i = 0; i < 3; i++) {
    // send "exit" and wait
    write(adm[i], "exit", sizeof "exit");
    wait(NULL);
  }
}


// send command to a pipeline
// ----------------------------------
void psend(int out, char* left, char* middle, char* right) {
  // send commands
  write(adm[0], left, strnlen(left, 1024));
  write(adm[1], middle, strnlen(middle, 1024));
  write(adm[2], right, strnlen(right, 1024));

  // read output and print
  char buf[1024] = "";
  int len = read(out, buf, 1024); 
  buf[len] = '\0';
  printf("%s\n", buf);
}


// read commands from pipadm 
// executes them to output instead of STDOUT_FILENO
// returns EXIT_SUCCESS or EXIT_FAILURE
// ----------------------------------
int pshsh(int pipadm) {
  // init
  setvbuf(stdout, NULL, _IONBF, 0); // SUPPOSED SOLUTION
  char buf[1024] = "";

  // while reading from admin pipe
  while(read(pipadm, buf, 1024) > 0) {
    // execute it using system()
    if(strncmp(buf, "exit", sizeof "exit") == 0) 
      exit(EXIT_SUCCESS); // success 
    system(buf);
  }

  // pipadm failed
  return EXIT_FAILURE;
}
