#ifndef VEC
#define VEC

#include <string.h>
#include <stdlib.h>


// Reallocate pointer 'p' of 'oldsize' to 'newsize', "size" bytes each.
// If you want something faster, use realloc and memset with pointer arithmetic.
// Be warned that technique is warned by valgrind.
// Initializes new memory to 0.
// -------------------------------------------------------------------------------------------
void* recalloc(void* ptr, size_t oldsize, size_t newsize, size_t size) {
  // realloc with 0 is not c99
  if(!newsize || !size) {
    free(ptr);
    return NULL;
  }

  // ask for memory
  void* res = calloc(newsize, size);
  if(!res) return NULL;
  
  // copy over
  size_t copyBytes = (newsize < oldsize) ? newsize : oldsize; 
  res = memcpy(res, ptr, copyBytes*size);
  free(ptr);
  return res;
}


// simple resizeable array of strings.
// -------------------------------------------------------------------------------------------
struct Vec {
  void**  arr;        // array of void*
  size_t  cap;        // capacity of vector
};


// Empty out a vector v.
// -------------------------------------------------------------------------------------------
void vempty(struct Vec v) {
  if(!v.arr) return; // already empty
  for(size_t i = 0; i < v.cap; i++) {
    if(v.arr[i]) free(v.arr[i]);
  }
}


// Free the mepty vector v
// Use `vempty(struct Vec)` beforehand if needed.
// -------------------------------------------------------------------------------------------
void vfree(struct Vec v) {
  if(v.arr) free(v.arr);
}


// put a new element "elem" of byte-size "elen" to an "index"
// automatically resizes, returns 0 on memory error.
// using elem=NULL AND elen=0 frees index. But I personally just free(vec.arr[index])
// -------------------------------------------------------------------------------------------
int vset(struct Vec* vec, size_t index, void* elem, size_t elen) {
  // sanitize
  if(!vec) return 1;
  if(index > vec->cap && !elem) return 1;

  // resize 
  if(index >= vec->cap) {
    // I want NO memory overhead. I don't care about performance
    int oldcap = vec->cap;
    vec->cap = index+1; 
    vec->arr = recalloc(vec->arr, oldcap, vec->cap, sizeof(char*));
    if(!vec->arr) return 0; // memory error
  }

  // setup the memory for new element
  vec->arr[index] = recalloc(vec->arr[index], vec->arr[index]? elen : 0, elen, sizeof(char));
  if(!elem) vec->arr[index] = NULL; // it is free...
  if(!vec->arr[index]) return 0; // memory error 

  // now copy over the element
  memcpy(vec->arr[index], elem, elen); 
  return 1;
}


// linear-search a vector for string "needle"
// give byte-size of needle as "needlen"
// set returnAddress=NULL to just confirm
// returns index when found, -1 when not found, and -2 on error
// -------------------------------------------------------------------------------------------
int vfind(struct Vec hay, void* needle, size_t needlen) {
  // sanitize
  if(!hay.arr) return -2;
  if(!needlen) return -2;
  if(!needle) return -1;
  if(!hay.cap) return -1; 

  for(size_t i = 0; i < hay.cap; i++) {
    // init
    void* elem = hay.arr[i];

    // skip to match-string
    if(!elem) continue; 
    if(memcmp(elem, needle, needlen)) continue;

    // success
    return i;
  }
  
  // failure
  return -1;
}


#endif
