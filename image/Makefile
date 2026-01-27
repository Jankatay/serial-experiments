AS= as
LD= ld

main.png: main.o
	$(LD) --oformat=binary -e0 -o $@ $<

main.o: main.s
	$(AS) -o $@ $<

.PHONY: clean
clean:
	rm -f main main.o
