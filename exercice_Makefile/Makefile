#################################
# 	EXERCICE MAKEFILE 	#
#################################

.PHONY: all clean


# Variables

EXE 	= hello
SOURCES	= main.c t1.c t2.c ./libs/stubs.c

CC 	= arm-none-eabi-gcc
CFLAGS	= -Wall -Werror -g -O2 -mthumb
LDLIBS	= -L/opt/mylibs


# Règles

all: $(EXE)

$(EXE): main.o t1.o t2.o stubs.o
	$(CC) $(LDLIBS) -mthumb $^ -lm -o $@

stubs.o: libs/stubs.c
	$(CC) -g -O2 -mthumb -c -o $@ $^

clean:
	@rm -f *.o *.d hello


# Dépendances

-include $(subst .c,.d,$(SOURCES))

%.d : %.c
	@$(CC) $(CFLAGS) -MM -MF $@ -MP $<
