AS= as
<<<<<<< HEAD
LD= ld

main.png: main.o
	$(LD) --oformat=binary -e0 -o $@ $<
=======
LD= ld -T linker.ld

main : main.o
	$(LD) -e0 --oformat=binary -o $@ $<
>>>>>>> f47b2cc (messing around with image formats)

main.o: main.s
	$(AS) -o $@ $<

.PHONY: clean
clean:
	rm -f main main.o
