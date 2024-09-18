#include "Sound_Driver.h"
#include "../inc/tm4c123gh6pm.h"

#define SAMPLE_RATE 8000 // 8 kHz sample rate
#define WAVE_FREQUENCY 440 // 440 Hz (A4 note)
#define AMPLITUDE 2048 // Half of the 12-bit range (0 to 4095)

void DAC_INIT(uint16_t data) {
    SYSCTL_RCGCSSI_R |= 0x01; // activate SSI0
    SYSCTL_RCGCGPIO_R |= 0x08;// activate port D
    while((SYSCTL_PRGPIO_R&0x08) == 0){}; // ready?
    GPIO_PORTD_AFSEL_R |= 0x2C;//enable alt funct on PD 2,3,5
    GPIO_PORTD_DEN_R |= 0x2C;// configure PD 2,3,5 as SSI
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFF0F00FF)+0x00202200;
    GPIO_PORTD_AMSEL_R = 0; // disable analog functionality on PD
    SSI0_CR1_R = 0x00000000; //disable SSI, master mode                               
    SSI0_CPSR_R = 0x02;
    // 8 MHz SSIClk
    SSI0_CR0_R &= ~(0x0000FFF0); //SCR = 0, SPH = 0, SPO = 0 Freescale
    SSI0_CR0_R |= 0x0F;                                                    
    // DSS = 16-bit data
    SSI0_DR_R = data;                                                            
    // load ‘data’ into transmit FIFO
    SSI0_CR1_R |= 0x00000002;             
}

void DAC_OUT(uint16_t code){		
    while((SSI0_SR_R&0x00000002)==0){}; //SSI Transmit FIFO	Not	Full
    SSI0_DR_R =	code;	//	data	out,	no	reply
}

void delay_ms(int milliseconds);

// Test main for sound driver
// int main() {
//     // Initialize the DAC
//     DAC_INIT(0);

//     // Generate a square wave
//     while (1) {
//         // High part of the square wave
//         DAC_OUT(AMPLITUDE);
//         delay_ms(1000 / (2 * WAVE_FREQUENCY)); // Delay for half the period

//         // Low part of the square wave
//         DAC_OUT(0);
//         delay_ms(1000 / (2 * WAVE_FREQUENCY)); // Delay for half the period
//     }
// }

// Simple delay function
void delay_ms(int milliseconds) {
    for (int i = 0; i < milliseconds * 1000; i++) {
        __asm("NOP"); // No operation (just waste time)
    }
}
