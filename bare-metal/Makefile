.PHONY: all clean

CC = arm-none-eabi-gcc

CFLAGS  = -c -g -O1 -mcpu=cortex-m0plus -mthumb
LDFLAGS = -T ld_ram.lds -nostdlib

EXE = main
SRC = main.c
OBJ = main.o

# arm-none-eabi-gcc -T ld_ram.lds main.o -o main
# arm-none-eabi-gcc -c -g -O1 -mcpu=cortex-m0plus -mthumb $^ -o $@

all: $(EXE)

$(EXE): $(OBJ)

startgdbserver:
	JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly

gdb: $(EXE)
	arm-none-eabi-gdb $^

clean:
	@rm -f $(OBJ) $(EXE)
