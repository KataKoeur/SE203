MEMORY
{
   flash_vectors (rx)  : ORIGIN = 0x00000000, LENGTH = 192
   flash_config  (rx)  : ORIGIN = 0x00000400, LENGTH = 16
   flash_program (rx)  : ORIGIN = 0x00001000, LENGTH = 254K
   RAML          (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8K
   RAMH          (!rx) : ORIGIN = 0x20000000, LENGTH = 24K
}

SECTIONS
{
   .flash_vectors : {
                       _start_of_flash_vectors_VMA = .;
                       *(.flash_vectors)
                       _end_of_flash_vectors_VMA = .;
                    } > RAMH   AT>flash_vectors
                  
   .flash_config  : {
                       *(.flash_config)
                    } > flash_config

   .text          : { 
                       _start_of_text_VMA = .;
                       *(.text)
                       _end_of_text_VMA = .;
                    } > RAMH   AT>flash_program

   .rodata        : { 
                       *(.rodata)
                    } > flash_program

   .data          : { 
                       _start_of_data_VMA = .;
                       *(.data)
                       _end_of_data_VMA = .;
                    } > RAMH   AT>flash_program
                  
   .bss           : {
                       _start_of_bss = .;
                       *(.bss) *(COMMON)
                       _end_of_bss = .;
                    } > RAMH
}

ENTRY(_start)

_stack = ORIGIN(RAMH);

_start_of_flash_vectors_LMA = LOADADDR(.flash_vectors);
_end_of_flash_vectors_LMA   = LOADADDR(.flash_vectors) + SIZEOF(.flash_vectors);
_start_of_text_LMA          = LOADADDR(.text);
_end_of_text_LMA            = LOADADDR(.text) + SIZEOF(.text);
_start_of_data_LMA          = LOADADDR(.data);
_end_of_data_LMA            = LOADADDR(.data) + SIZEOF(.data);
