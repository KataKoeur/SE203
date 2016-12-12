.PHONY: all clean

# Variables

EXE 	= exo2
SOURCES	= exo2.c

CC 	= gcc
CFLAGS	= -std=gnu99 -Wall -O1

# Règles

all: $(EXE)

$(EXE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

symbol_table: $(EXE)
	objdump -t $^

clean:
	@rm -f *.o *.d $(EXE)
