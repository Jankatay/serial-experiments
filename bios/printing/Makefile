emulate: boot
	qemu-system-x86_64 -drive file=$<,format=raw

boot: boot.o
	ld --oformat=binary -o $@ $<

boot.o: boot.S
	as -o $@ $<

.PHONY: clean
clean: 
	rm -f boot boot.o
