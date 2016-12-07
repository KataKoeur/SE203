@ Code généré par la commande: arm-none-eabi-gcc -Os -S exo2.c
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
	.file	"exo2.c"
	.text
	.align	2
	.global	f
	.type	f, %function
@--------------------------------------------------------

@ Code écrit par mes soins
@--------------------------------------------------------
f:
	ldr	r0, =a		@ on charge a dans r0
	mov	r0, [r0]	@ déréférencement de a dans r0
	ldr	r1, =b		@ on charge b dans r1
	mov	r1, [r1]	@ déréférencement de a dans r1
	ldr	r2, =c		@ on charge c dans r2
	mov	r2, [r2]	@ déréférencement de a dans r2

	add	r0, r0, r2	@ a = a + c ;
	str r0, [r0]		@ on sauvegarde r0 dans *a

	add	r1, r1, r2	@ b = b + c ;
	str r1, [r1]		@ on sauvegarde r1 dans *b

variable:
	.word	a
	.word	b
	.word	c
@--------------------------------------------------------

@ Code généré par la commande: arm-none-eabi-gcc -Os -S exo2.c
@--------------------------------------------------------
	.size	f, .-f
	.comm	c,4,4
	.comm	b,4,4
	.comm	a,4,4
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 5.4.1 20160919 (release) [ARM/embedded-5-branch revision 240496]"
@--------------------------------------------------------
