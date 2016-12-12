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
	ldr	r0, =a		@ r0 = &a
	ldr	r0, [r0]	@ r0 = a 	//on garde a dans r0 car on en aura besoin plus bas.
	ldr	r4, [r0]	@ r4 = *a

	ldr	r1, =b		@ r1 = &b
	ldr	r1, [r1]	@ r1 = b 	//on garde b dans r1 car on en aura besoin plus bas.
	ldr	r5, [r1]	@ r5 = *b
	
	ldr	r2, =c		@ r2 = &c
	ldr	r2, [r2]	@ r2 = c
	ldr	r2, [r2]	@ r2 = *c

	add	r4, r4, r2	@ r4 = *a + *c
	str r4, [r0]		@ *a = r4	//on utilise a conservé précedemment

	add	r5, r5, r2	@ r5 = *b + *c
	str r5, [r1]		@ *b = r5	//on utilise b conservé précedemment 

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
