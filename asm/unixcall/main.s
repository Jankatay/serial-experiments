; variables
section .data
  msg db "Hello, World", 0xA
  len equ $-msg


; code
section .text
global _start


; otherwise you would have to push eax manually too
; macroing that makes it hard to calculate stack pointer later
align 4
krnl:
  int 0x80
  ret


; entry point
_start:
  mov eax, 4                     ; SYS_write
  push dword len                 ; string's length
  push dword msg                 ; the string
  push dword 1                   ; fileno for STDOUT 
  call krnl
  
  mov eax, 1                     ; SYS_exit
  push dword 0                   ; exit code
  call krnl
