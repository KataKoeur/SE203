//irq.c

#include "irq.h"

#define VTOR      (*(volatile uint32_t *)0xE000ED08)
#define NVIC_ISER (*(volatile uint32_t *)0xE000E100)
#define NVIC_ICER (*(volatile uint32_t *)0xE000E180)
#define NVIC_IPR3 (*(volatile uint32_t *)0xE000E460)
#define NVIC_IPR5 (*(volatile uint32_t *)0xE000E4a0)

#define MAKE_DEFAULT_HANDLER(x) void __attribute__((weak)) x(void) {disable_irq() while(1);}

MAKE_DEFAULT_HANDLER (NMI_Handler)
MAKE_DEFAULT_HANDLER (HardFault_Handler)
MAKE_DEFAULT_HANDLER (SVC_Handler)
MAKE_DEFAULT_HANDLER (PendSV_Handler)
MAKE_DEFAULT_HANDLER (SysTick_Handler)
MAKE_DEFAULT_HANDLER (DMA0_IRQHandler)
MAKE_DEFAULT_HANDLER (DMA1_IRQHandler)
MAKE_DEFAULT_HANDLER (DMA2_IRQHandler)
MAKE_DEFAULT_HANDLER (DMA3_IRQHandler)
MAKE_DEFAULT_HANDLER (FTFA_IRQHandler)
MAKE_DEFAULT_HANDLER (PMC_IRQHandler)
MAKE_DEFAULT_HANDLER (LLWU_IRQHandler)
MAKE_DEFAULT_HANDLER (I2C0_IRQHandler)
MAKE_DEFAULT_HANDLER (I2C1_IRQHandler)
MAKE_DEFAULT_HANDLER (SPI0_IRQHandler)
MAKE_DEFAULT_HANDLER (SPI1_IRQHandler)
MAKE_DEFAULT_HANDLER (UART0_IRQHandler)
MAKE_DEFAULT_HANDLER (UART1_IRQHandler)
MAKE_DEFAULT_HANDLER (UART2_IRQHandler)
MAKE_DEFAULT_HANDLER (ADC0_IRQHandler)
MAKE_DEFAULT_HANDLER (CMP0_IRQHandler)
MAKE_DEFAULT_HANDLER (TPM0_IRQHandler)
MAKE_DEFAULT_HANDLER (TPM1_IRQHandler)
MAKE_DEFAULT_HANDLER (TPM2_IRQHandler)
MAKE_DEFAULT_HANDLER (RTC0_IRQHandler)
MAKE_DEFAULT_HANDLER (RTC1_IRQHandler)
MAKE_DEFAULT_HANDLER (PIT_IRQHandler)
MAKE_DEFAULT_HANDLER (I2S0_IRQHandler)
MAKE_DEFAULT_HANDLER (USB_OTG_IRQHandler)
MAKE_DEFAULT_HANDLER (DAC0_IRQHandler)
MAKE_DEFAULT_HANDLER (TSI0_IRQHandler)
MAKE_DEFAULT_HANDLER (MCG_IRQHandler)
MAKE_DEFAULT_HANDLER (LPTMR0_IRQHandler)
MAKE_DEFAULT_HANDLER (SLCD_IRQHandler)
MAKE_DEFAULT_HANDLER (PORTA_IRQHandler)
MAKE_DEFAULT_HANDLER (PORTCD_IRQHandler)

extern char _stack;
void _start();

void *vector_table[] __attribute__((aligned(256))) = 
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
   USB_OTG_IRQHandler, /* - */
   DAC0_IRQHandler,    /* - */
   TSI0_IRQHandler,    /* - */
   MCG_IRQHandler,     /* - */
   LPTMR0_IRQHandler,  /* - */
   SLCD_IRQHandler,    /* - */
   PORTA_IRQHandler,   /* Pin detect (Port A) */
   PORTCD_IRQHandler   /* Pin detect (Single interrupt vector for Port C and Port D) */
};

void irq_init(void)
{
   enable_irq()
   VTOR = (uint32_t) vector_table;

   //interruptions
   irq_enable(12); //UART0
}

void irq_enable(int irq_number)
{
   NVIC_ISER = 1 << irq_number;
}

void irq_disable(int irq_number)
{
   NVIC_ICER = 1 << irq_number;
}
