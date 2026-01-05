.code16


# print "Hello, World!"
main: 
  #mov $msg, %si   # load "Hello, World" to si
  mov 0x0E, %ah   # syscall(?) for putchar
  LS: # for each letter in the message
  lodsb           # get a char from si
  or  $0, %al     # if it's null
  jmp halt        # then halt
  int $0x10       # otherwise call interrupt
  jmp LS          # jump to loopstart

msg: .asciz "Hello, World!"

# halt until OS shuts down
halt: hlt 

# padding and magic
.byte 0x55, 0xAA
