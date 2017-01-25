.PHONY: all startgdbserver gdb objdump clean

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
DL = $(PREFIX)ld
AS = $(PREFIX)as

TARGET_ARCH = -mcpu=cortex-m0plus -mthumb
CFLAGS  = -c -g -O1 -std=gnu99 -Wall -Wextra -Werror
ASFLAGS = -g -mcpu=cortex-m0plus
LDFLAGS = -T ld_ram.lds -nostdlib

EXE = main.elf
OBJS = main.o init.o led.o uart.o matrix.o irq.o buttons.o image.o flash.o crt0.o
LOADLIBES = clocks.o

DEPS = $(subst .o,.d,$(OBJS))

all: $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

image.o: image.raw
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B arm $^ $@

-include $(DEPS)
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
