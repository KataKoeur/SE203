//irq.h

#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

#define enable_irq()  asm ("cpsie i");
#define disable_irq() asm ("cpsid i");

void irq_init(void);
void irq_enable(int irq_number);
void irq_disable(int irq_number);

#endif

