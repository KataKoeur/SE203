.PHONY: all startgdbserver gdb objdump clean

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
DL = $(PREFIX)ld
AS = $(PREFIX)as

CFLAGS  = -c -g -O1 -mcpu=cortex-m0plus -mthumb -std=gnu99 -Wall -Wextra -Werror
ASFLAGS = -g -mcpu=cortex-m0plus
LDFLAGS = -T ld_ram.lds -nostdlib

EXE = main.elf
OBJS = main.o init.o led.o uart.o matrix.o crt0.o
LOADLIBES = clocks.o

DEPS = $(subst .o,.d,$(OBJ))
-include $(DEPS)

all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MF $@ -MP $<

startgdbserver:
	JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly

gdb: $(EXE)
	$(PREFIX)gdb $^

objdump: $(EXE)
	$(PREFIX)objdump -h $^

clean:
	@rm -f $(DEPS) $(OBJS) $(EXE)
