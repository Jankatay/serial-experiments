CC= gcc
CFLAGS= -Os -Wall -Wextra -Werror 
IFLAGS= `pkg-config --cflags sdl3`
LFLAGS= `pkg-config --libs sdl3`

main: main.c 
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $< $(LFLAGS) 

.PHONY: clean
clean:
	rm -f main
