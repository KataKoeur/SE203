//irq.h

#ifndef IRQ_H
#define IRQ_H

#define enable_irq()  asm ("cpsie i");
#define disable_irq() asm ("cpsid i");

void irq_init(void);

#endif

