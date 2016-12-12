.PHONY: all clean

# Variables

EXE 		= exo1
SOURCES	= exo1.c

CC 			= arm-none-eabi-gcc
CFLAGS	= -std=gnu99 -Wall -O1

# Règles

all: $(EXE)

$(EXE): exo1.o
	$(CC) $(CFLAGS) -c $^ -o $@

symbol_table: exo1.o
	arm-none-eabi-objdump -t $^

clean:
	@rm -f *.o *.d exo1
