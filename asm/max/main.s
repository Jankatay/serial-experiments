# Example program to find max number in array "arr"
# clobbers ebx and eax

.section .data
arr: # first element is the length of this array. This means NOT zero-indexed
  .long 10, 56, 1, 4, 3, 55, -1, 5, 9, 12, 12

.section .text

.globl _start
_start:
  # edi -> index, ebx -> current max
  # arr[0] holds the length, so it's not 0-indexed
  movl (arr), %edi            # move length into index
  movl arr(, %edi, 4), %ebx   # move last value, 
                              # remember arr is one-indexed
  reverse_iterate: # start loop
    cmpl $1, %edi                 # exit if we reached the beginning
    jle reverse_iterate_break     #
    decl %edi                     # set index for next iteration
    mov arr(, %edi, 4), %eax      # set val to the array's value
    cmp %eax, %ebx                # continue iterating if val <= max
    jge reverse_iterate
    mov %eax, %ebx                # otherwise set the new max and loop again
    jmp reverse_iterate       
  reverse_iterate_break:

_exit: # success
  movl $1, %eax     # exit with "max" as status
  int $0x80         
