CPP = g++ -Os -Wall -Wextra -Weffc++ -Werror
COMPRESS = gzexe

run: main
	./main

main: main.cpp
	$(CPP) -o $@ $<
	$(COMPRESS) $@
	rm $@~

.PHONY: clean
clean:
	rm -f main
