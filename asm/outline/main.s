#PURPOSE:   Simple program that exits and returns 0 to linux kernel
#

#INPUT:     NONE
#

#OUTPUT:    Returns a status code, you can check it afterwards by typing
#
#           echo $?
#

#VARIABLES: 
#           %eax -> holds the syscall number 
#           %ebx -> holds the return status
#

.section .data

.section .text
.globl _start
_start:
  movl $1, %eax   # prepare exit
  movl $0, %ebx   # status = 0
  int $0x80       # cast
