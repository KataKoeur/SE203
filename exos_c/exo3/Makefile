.PHONY: all clean

# Variables

EXE 	= exo3
SOURCES	= exo3.c

CC 	= arm-none-eabi-gcc-5.4.1
CFLAGS	= -std=gnu99 -Wall -O1

# Règles

all: $(EXE)

$(EXE): exo3.o
	$(CC) $(CFLAGS) -c $^ -o $@

symbol_table: exo3.o
	arm-none-eabi-objdump -t $^

clean:
	@rm -f *.o *.d $(EXE)
