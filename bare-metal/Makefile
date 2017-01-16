.PHONY: all clean

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as

CFLAGS  = -c -g -O1 -mcpu=cortex-m0plus -mthumb -std=gnu99 -Wall -Wextra -Werror
ASFLAGS = -g -mcpu=cortex-m0plus
LDFLAGS = -T ld_ram.lds -nostdlib

EXE  = main.elf
SRC  = main.c init.c led.c uart.c
ASM  = crt0.s
OBJ  = main.o init.o led.o uart.o crt0.o

all: $(EXE)

$(EXE): $(OBJ)
	$(LINK.o) clocks.o $^ $(LOADLIBES) $(LDLIBS) -o $@

startgdbserver:
	JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly

gdb: $(EXE)
	arm-none-eabi-gdb $^

objdump: $(EXE)
	arm-none-eabi-objdump -h $^

clean:
	@rm -f $(OBJ) $(EXE)
