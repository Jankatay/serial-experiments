main: main.hs 
	ghc -o $@ $<
	strip $@
	upx --lzma --overlay=strip --all-methods $@

lazuri: lazuri.hs 
	ghc -o $@ $<
	strip $@
	upx --lzma --overlay=strip --all-methods $@

.PHONY: clean
clean:
	rm -f main main.o main.hi
