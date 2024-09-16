#include "Switch_Driver.h"
#include "Global_Define.h"


void Switch_Init(void){
    // write something to initalize the GPIO that take input from the switches based on your EID as defined in the lab doc
    SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port C
    while((SYSCTL_PRGPIO_R & 0x00000020) == 0){};
    GPIO_PORTF_DIR_R &= ~0x01;    // (c) make button PF0 input
    GPIO_PORTF_DIR_R &= ~0x02; // (d) make button PF1 input
    GPIO_PORTF_DIR_R &= ~0x04; // (d) make button PF2 input
    GPIO_PORTF_AFSEL_R &= ~0x01;  //     disable alt funct on PF0
    GPIO_PORTF_AFSEL_R &= ~0x02;  //     disable alt funct on PF1
    GPIO_PORTF_AFSEL_R &= ~0x04;  //     disable alt funct on PF2
    GPIO_PORTF_DEN_R |= 0x01;     //     enable digital I/O on PF0
    GPIO_PORTF_DEN_R |= 0x02;     //     enable digital I/O on PF1
    GPIO_PORTF_DEN_R |= 0x04;     //     enable digital I/O on PF2  
    GPIO_PORTF_PCTL_R &= ~0x0000000F; // configure PF0 as GPIO
    GPIO_PORTF_PCTL_R &= ~0x000000F0; // configure PF1 as GPIO
    GPIO_PORTF_PCTL_R &= ~0x00000F00; // configure PF2 as GPIO
    GPIO_PORTF_AMSEL_R = 0;       //     disable analog functionality
}

uint32_t getSwitchReading(void){
    return (PF0 + (PF1 << 1) + (PF2 << 2));
}