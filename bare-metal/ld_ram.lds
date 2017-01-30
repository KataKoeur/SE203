MEMORY
{
   vector_table (rx)  : ORIGIN = 0x00000000, LENGTH = 192
   flash_config (rx)  : ORIGIN = 0x00000400, LENGTH = 16
   flash        (rx)  : ORIGIN = 0x00001000, LENGTH = 254K
   RAML         (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8K
   RAMH         (!rx) : ORIGIN = 0x20000000, LENGTH = 24K
}

SECTIONS
{
   .vector_table : {
                      *(.vector_table)
                   } > vector_table

   .flash_config : {
                      *(.flash_config)
                   } > flash_config

   .text         : { 
                      *(.text)
                      _end_of_text = .;
                   } > flash
                 
   .rodata       : { 
                      *(.rodata)
                   } > flash
                 
   .data         : { 
                      _start_of_data = .;
                      *(.data)
                      _end_of_data = .;
                   } > flash
                 
   .bss          : {
                      _start_of_bss = .;
                      *(.bss) *(COMMON)
                      _end_of_bss = .;
                   } > RAMH
}

ENTRY(_start)

_stack = ORIGIN(RAMH);
