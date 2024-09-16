#include "Sound_Driver.h"

int dac_init() {
    /**
     * Unified_Port_Init in Lab5.c calls Port_D_Init, which initializes the Port
     * D GPIOs for the appropriate alternate functionality (SSI).
     *
     * According to Table 15-1. SSI Signals in the datasheet, this corresponds
     * to SSI1. The corresponding Valvanoware register defines are at L302 and
     * L2670 in inc/tm4c123gh6pm.h. Use this in combination with the datasheet
     * or any existing code to write your driver! An example of how to
     * initialize SSI is found in L741 in inc/ST7735.c.
     */

    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R1; // Enable clock for SSI1
    while((SYSCTL_PRSSI_R & SYSCTL_PRSSI_R1) == 0){}; // Wait for SSI1 to be ready

    //Initialize Port D

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; // Enable clock for Port D
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R3) == 0){}; // Wait for Port D to be ready

    GPIO_PORTD_AFSEL_R |= 0x0B; // Enable alternate function on PD0, PD1, PD3 (clock signal, frame signal, and data transmission)
    GPIO_PORTD_DEN_R |= 0x0B;   // Enable digital I/O on PD0, PD1, PD3
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFFFF0F00) | 0x00002022; // Configure PD0, PD1, PD3 as SSI1
    GPIO_PORTD_AMSEL_R &= ~0x0B; // Disable analog functionality on PD0, PD1, PD3


    SSI1_CR1_R = 0x00000000; // Disable SSI and configure it as a primary
    SSI1_CC_R = 0x0; // Use system clock
    SSI1_CPSR_R = 0x02; // Set clock prescale divisor to 2 (for 80 MHz SSI clock)
    SSI1_CR0_R = 0x000F; // Configure SSI for Freescale SPI frame format, 16-bit data, and steady clock low
    SSI1_CR1_R |= 0x00000002; // Enable SSI

    return 0; 
}

int dac_output(uint16_t data) {
    uint16_t dac_in = (data & 0x0FFF) | 0x3000; // Only 12 bits are used for the data
    while((SSI1_SR_R & SSI_SR_TNF) == 0) {}; //Check whether the FIFO has space available to transfer more data
    SSI1_DR_R = dac_in;
    return 0;
}