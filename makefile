CC     = cc
CLIBS  = -lc
CFLAGS = -W -Wall -Werror -Wextra -Wpedantic -std=c89

build: src/main.c
	$(CC) $(CLIBS) $(CFLAGS) src/main.c -o bin/main.o

chase: bin/main.o
	valgrind -s --leak-check=full --show-leak-kinds=all bin/main.o -n 5

clean:
	find bin -type f -name "*.o" -delete

.PHONY: build chase clean
