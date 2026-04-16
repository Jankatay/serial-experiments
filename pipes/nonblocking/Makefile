CC= gcc -g

run: main
	./$<

main: main.c
	$(CC) -o $@ $<

.PHONY: clean
clean:
	rm -f main
