LDLIBS = -lncurses
CFLAGS = -Wall
EXEC := flext

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.h)

all: $(EXEC)

$(EXEC): $(OBJS)
	gcc $(OBJS) $(LDLIBS) -o $(EXEC)

%.o: %.c
	gcc $(CLFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)