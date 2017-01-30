.thumb
.global _start
.type _start, %function
_start:
   ldr r0, =_stack   @gestion pointeur de pile
   mov sp, r0

   bl init_memory    @initialisation de la memoire
   bl init_bss       @initialisation de la bss
   bl main           @lancement du programme principale

_end:
   b _end
