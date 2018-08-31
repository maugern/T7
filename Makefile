CC = gcc
LD = gcc
CFLAGS  = -Wall -W -Werror -ansi
LDFLAGS =
VFLAGS  = --quiet --tool=memcheck --leak-check=full --error-exitcode=1 --track-origins=yes

BIN = T7

HEADERS = $(wildcard *.h)
CFILES  = $(wildcard *.c)

OBJS = $(CFILES:.c=.o)

.PHONY: all clean mrproper docs memcheck

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

makefile.dep: $(CFILES) $(HEADERS)
	$(CC) -MM $(CFILES) > $@

docs:
	$(MAKE) -C docs

memcheck: $(BIN)
	@valgrind $(VFLAGS) ./$(BIN)
	@echo "Memory check passed"

clean:
	$(RM) $(OBJS) makefile.dep

mrproper: clean
	$(RM) $(BIN)
	$(MAKE) clean -C docs

include makefile.dep

