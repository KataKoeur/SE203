.thumb
.global _start
.type _start, %function
_start:
   ldr r0, =_stack   @gestion pointeur de pile
   mov sp, r0

   bl init_bss       @initialisation de la bss
   bl init_memory    @recopie de la flash vers la ram
   bl main           @lancement du programme principale

_end:
   b _end
