CC     = cc
CFLAGS = -g -W -Wall -Werror -Wextra -Wpedantic -std=c89
CLIBS  = -lc

build: src/main.c
	$(CC) $(CFLAGS) $(CLIBS) src/main.c -o bin/main.o && ./bin/main.o

chase: bin/main.o
	valgrind -s --leak-check=full --show-leak-kinds=all ./bin/main.o

clean:
	find bin -type f -name "*.o" -delete

.PHONY: build chase clean
