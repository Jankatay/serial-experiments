run: main
	./$^

main: main.o
	ld -o $@ $^

main.o: main.s
	nasm -f elf -o $@ $^

