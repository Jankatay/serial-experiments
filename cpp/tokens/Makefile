CPP = g++ -O0 -Wall -Wextra -Weffc++ -Werror -g
COMPRESS = gzexe

run: main
	./main

main: main.cpp
	$(CPP) -o $@ $<

.PHONY: clean
clean:
	rm -f main
