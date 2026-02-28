AS= as
LD= ld

run: main
	./$<

main: main.o
	$(LD) -o $@ $<

main.o: main.s
	$(AS) -o $@ $<

.PHONY: clean
clean:
	rm -f main.o main
