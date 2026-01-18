#include <stdio.h>
#include <time.h>
#include "vec.h"

int main() {
  // setup rng and init array
  srand(time(NULL));

  // randomly place 10 elements to the vector from 0-999
  struct Vec v = {};
  for(int i = 0; i < 10; i++) {
    // setup the random values
    long index = random()%1000;
    long val = random();
    // print debug message if no memory error while setting
    if(!vset(&v, index, &val, sizeof val)) continue;
    fprintf(stderr, "Setting %ld -> %ld\n", index, val);
  }
  fprintf(stderr, "----------------------------------------------\n");
  
  // for each value in the vector
  for(size_t i = 0; i < v.cap; i++) {
    // ensure it's valid and print
    int* elem = v.arr[i];
    if(elem) fprintf(stderr, "Getting %d -> %d\n", i, *elem); 
  }

  // free and exit
  vempty(v);
  vfree(v);
  return 0;
}
