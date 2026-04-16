CC= gcc -g

all: main
	./$^

main: main.c
	$(CC) -o $@ $< -static

.PHONY: clean
clean:
	rm -f main
