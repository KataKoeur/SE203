.thumb
.global _start
_start:
   ldr r0, =_stack   @gestion pointeur de pile
   mov r13, r0

   bl init_bss       @initialisation de la bss
   bl main           @lancement du programme principale
