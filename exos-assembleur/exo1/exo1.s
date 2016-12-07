@ Code généré par la commande: arm-none-eabi-gcc -Os -S exo1.c
@--------------------------------------------------------
	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 4
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.arm
	.syntax divided
	.file	"exo1.c"
	.text
	.align	2
	.global	f
	.type	f, %function
@--------------------------------------------------------

@ Code écrit par mes soins
@--------------------------------------------------------
f:
	ldr	r0, =a		@ on charge a dans r0
	ldr	r1, =i		@ on charge i dans r1
	mov	r1, #0		@ i=0;
loop:
	cmp	r0, r1		@ a-i
	bne	sortie		@ si a-i == 0 alors sortir de la boucle
	bl	g		@ g();
	add	r1, #1		@ i=i+1;
	b	loop		@ retour au début de la boucle
sortie:
@--------------------------------------------------------

@ Code généré par la commande: arm-none-eabi-gcc -Os -S exo1.c
@--------------------------------------------------------
	.size	f, .-f
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 5.4.1 20160919 (release) [ARM/embedded-5-branch revision 240496]"
@--------------------------------------------------------
