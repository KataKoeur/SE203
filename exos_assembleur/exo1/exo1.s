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
	ldr	r0, =a		@ r0 = &a
	ldr	r0, [r0]	@ r0 = a
	mov	r1, #0		@ r1 = 0, soit i = 0
loop:
	cmp	r0, r1		@ (r0 - 1), soit (a - i)
	bne	sortie		@ si (a-i == 0) alors sortir de la boucle
	bl	g		@ g();
	add	r1, #1		@ r1 = r1 +1, soit i=i+1
	b	loop		@ retour au début de la boucle
sortie:

variable:
	.word	a
@--------------------------------------------------------

@ Code généré par la commande: arm-none-eabi-gcc -Os -S exo1.c
@--------------------------------------------------------
	.size	f, .-f
	.comm	a,4,4
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 5.4.1 20160919 (release) [ARM/embedded-5-branch revision 240496]"
@--------------------------------------------------------
