.section .data
cat: .ascii "meow\n" 
.equ len, .-cat

.section .text

.globl _start
_start:
  movl $4, %eax
  movl $1, %ebx
  movl $cat, %ecx
  movl $len, %edx
  int $0x80
  movl $1, %eax
  xorl %ebx, %ebx
  int $0x80
