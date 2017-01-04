.PHONY: all clean

EXE = prog.elf

gdb_serveur:
	JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly

gdb: $(EXE)
	arm-none-eabi-gdb $@
