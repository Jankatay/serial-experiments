emulate: boot
	qemu-system-x86_64 -drive file=$<,format=raw

boot: boot.o
	ld -emain -Ttext=0x7c00 --oformat=binary -o $@ $<

boot.o: boot.S
	as -o $@ $<

.PHONY: clean
clean: 
	rm -f boot boot.o
