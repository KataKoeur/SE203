//irq.c

void *vector_table[] = 
{
    // Stack and Reset Handler
    &_stack,            /* Top of stack */
    _start,             /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler,    /* SysTick hanlder */

    // KL46 External interrupts
    DMA0_IRQHandler,         /* DMA0 interrupt */
    DMA1_IRQHandler,         /* DMA1 interrupt */
    DMA2_IRQHandler,         /* DMA2 interrupt */
};
