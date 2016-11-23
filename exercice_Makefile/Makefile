#################################
# 	EXERCICE MAKEFILE 	#
#################################

.PHONY: all clean


# Variables

EXE 	= hello
SOURCES	= main.c t1.c t2.c ./libs/stubs.c
HEADERS = main.h t1.h t2.h

CC 	= arm-none-eabi-gcc
CFLAGS	= -Wall -Werror -g -O2 -mthumb
LDLIBS	= -L/opt/mylibs


# Règles

all: $(EXE)

$(EXE): main.o t1.o t2.o stubs.o
	$(CC) $(LDLIBS) -mthumb main.o t1.o t2.o stubs.o -lm -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ main.c

t1.o: t1.c t1.o
	$(CC) $(CFLAGS) -c -o $@ t1.c

t2.o: t2.c t2.o
	$(CC) $(CFLAGS) -c -o $@ t2.c

stubs.o: libs/stubs.c
	$(CC) -g -O2 -mthumb -c -o $@ $^

clean:
	@rm -f *.o


# Dépendances

-include $(subst .c,.d,$(SOURCES))

%.d : %.c
	@$(CC) $(CFLAGS) -MM -MF $@ -MP $<
