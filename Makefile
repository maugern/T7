CC = gcc
LD = gcc
CFLAGS  = -Wall -W -Werror -ansi
LDFLAGS =

BIN = T7

HEADERS = $(wildcard *.h)
CFILES  = $(wildcard *.c)

OBJS = $(CFILES:.c=.o)

.PHONY: all clean mrproper docs

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

makefile.dep: $(CFILES) $(HEADERS)
	$(CC) -MM $(CFILES) > $@

docs:
	$(MAKE) -C docs

clean:
	$(RM) $(OBJS) makefile.dep

mrproper: clean
	$(RM) $(BIN)
	$(MAKE) clean -C docs

include makefile.dep

