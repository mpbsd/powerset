CC     = cc
CFLAGS = -g -W -Wall -Wextra -Wpedantic -std=c89
CLIBS  = -lc

build:
	$(CC) $(CFLAGS) $(CLIBS) src/main.c -o bin/main.o && ./bin/main.o

chase:
	valgrind -s --leak-check=full --show-leak-kinds=all ./bin/main.o

clean:
	find bin -type f -name "*.o" -delete

.PHONY: build chase clean
