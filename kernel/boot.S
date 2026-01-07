.set ALIGN, 1
.set MEMINFO, 2
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
.stack_top:

.section .text
.global main
.type main, @function

main:
  mov $stack_top, %esp
  call kernel
  cli
  halt: hlt
  jmp halt

.size main, . - main

