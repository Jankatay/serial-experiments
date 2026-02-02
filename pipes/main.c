// unix
#include <unistd.h>
#include <sys/wait.h>

// standard
#include <stdlib.h>
#include <stdio.h>


char** vectorize(char* mem, char seperator, size_t* len);
void pipeline(size_t vlen; char* vbuf[vlen], size_t vlen);


// it's like recursion but through pipes
//------------------------------------------------
int main() {
  char str[] = "echo a | awk '{print $1\"b\"}' | awk '{print $1\"c\"}'";
  size_t len = 0;
  char** vec = vectorize(str, '|', &len);
  if(fork() == 0) {
    pipeline(vec, len);
    free(vec);
    exit(EXIT_SUCCESS);
  }
  wait(NULL);
  free(vec);
  return 0;
}


// recursively fork to pipe multiple commands
void pipeline(size_t vlen; char* vbuf[vlen], size_t vlen) {
  for(int i = vlen-1; i >= 0; i--) {
    // pipe
    int pipfd[2];
    pipe(pipfd);
    char* cmd = vbuf[i];

    // child
    if(fork() == 0) {
      dup2(pipfd[1], STDOUT_FILENO);
      continue;
    }

    // parent
    wait(NULL);
    close(pipfd[1]);
    dup2(pipfd[0], STDIN_FILENO);
    system(cmd);
    break;
  }
}

// seperate a null-terminated memory segment into multiple smaller ones
// WARNING : makes pointers to str[N], do NOT free str
// if len is not NULL it will hold the length
// also res[len] will be NULL too
// returns NULL on error.
// free res[0] done
//------------------------------------------------
char** vectorize(char* mem, char seperator, size_t* len) {
  // sanitize
  size_t vlen = -1;
  if(!mem || !seperator) return NULL;
  while(*mem == seperator) mem++;
  if(!*mem) return NULL;
  if(!len) len = &vlen;
  *len = 1;
  
  // calculate
  for(char* data = mem; *data; data++) {
    if(*data == seperator) (*len)++;
  }

  // allocate
  char** res = (char**)malloc((1+*len)*sizeof(void*));
  *len = 0;
  res[(*len)++] = mem;

  // point the pointers
  for(char* data = mem; *data; data++) {
    if(*data != seperator) continue;
    *data = '\0';
    res[(*len)++] = data+1;
  }

  // finish
  res[(*len)] = NULL;
  return res;
}
