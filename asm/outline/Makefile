CC= gcc -nostdlib -nostartfiles
SFLAGS= -march=native -mtune=generic -m64

run: main
	./$< 
	echo $$?

main: main.s
	$(CC) $(SFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f main
