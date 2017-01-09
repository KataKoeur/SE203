MEMORY
{
   flash (rx)  : ORIGIN = 0x00000000, LENGTH = 256K
   RAML  (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8K
   RAMH  (!rx) : ORIGIN = 0x20000000, LENGTH = 24K
}

SECTIONS
{
   .text    :  { 
                  *(.text)
                  _end_of_text = .;
               } > RAMH

   .rodata  :  { 
                  *(.rodata)
               } > RAMH

   .data    :  { 
                  _start_of_data = .;
                  *(.data)
                  _end_of_data = .;
               } > RAMH

   .bss     :  {
                  _start_of_bss = .;
                  *(.bss) *(COMMON)
                  _end_of_bss = .;
               } > RAMH
}

ENTRY(_start)

_stack = ORIGIN(RAMH);
