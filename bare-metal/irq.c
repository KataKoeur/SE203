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
   DMA0_IRQHandler,    /* DMA0 interrupt */
   DMA1_IRQHandler,    /* DMA1 interrupt */
   DMA2_IRQHandler,    /* DMA2 interrupt */
   DMA3_IRQHandler,    /* DMA3 interrupt */
   0,                  /* Reserved */
   FTFA_IRQHandler,    /* Commande complete and read collision */
   PMC_IRQHandler,     /* Low-voltage detect, low-voltage warning */
   LLWU_IRQHandler,    /* Low Leakage Wakeup */
   I2C0_IRQHandler,    /* - */
   I2C1_IRQHandler,    /* - */
   0,                  /* Reserved */
   SPI0_IRQHandler,    /* Single interrupt vector for all sources */
   SPI1_IRQHandler,    /* Single interrupt vector for all sources */
   UART0_IRQHandler,   /* Status and error */
   UART1_IRQHandler,   /* Status and error */
   UART2_IRQHandler,   /* Status and error */
   ADC0_IRQHandler,    /* - */
   CMP0_IRQHandler,    /* - */
   TPM0_IRQHandler,    /* - */
   TPM1_IRQHandler,    /* - */
   TPM2_IRQHandler,    /* - */
   RTC0_IRQHandler,    /* Alarm interrupt */
   RTC1_IRQHandler,    /* Seconds interrupt */
   PIT_IRQHandler,     /* Single interrupt vector for all channels */
   I2S0_IRQHandler,    /* Single interrupt vector for all sources */
   USB OTG_IRQHandler, /* - */
   DAC0_IRQHandler,    /* - */
   TSI0_IRQHandler,    /* - */
   MCG_IRQHandler,     /* - */
   LPTMR0_IRQHandler,  /* - */
   SLCD_IRQHandler,    /* - */
   PORTA_IRQHandler,   /* Pin detect (Port A) */
   PORTCD_IRQHandler,  /* Pin detect (Single interrupt vector for Port C and Port D) */
};
