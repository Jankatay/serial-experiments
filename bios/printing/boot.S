.code16
.global main

# _start
xor %ax, %ax
mov %ax, %ds
cld
cli
call main

# data
msg: .asciz "Hello, World!\n"


# print "Hello, World!"
main: 
  mov $msg, %bx
  call printz
  jmp exit

# print zero-terminated string at %bx
printz:
  mov $0xE, %ah      # print a char on interrupt
  LPRINTS:           # while printing
  movb (%bx), %al    # move a byte from address in $bx to $al
  or %al, %al        # check if $al is 0
  jz LPRINTE         # jump to print loop end on NULL
  int $0x10          # print $al onto the screen
  inc %bx            # bx++
  jmp LPRINTS        # jump to print loop start
  LPRINTE:           # end printing
  ret                # return
  

# halt until OS shuts down
exit: hlt 

# padding and magic
. = 510
.byte 0x55, 0xAA
