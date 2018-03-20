CFLAGS = -g -Wall
LDFLAGS = -lncurses

.PHONY: clean

all:
	gcc $(CFLAGS) foo.c -o foo $(LDFLAGS)

clean:
	rm -rf foo
