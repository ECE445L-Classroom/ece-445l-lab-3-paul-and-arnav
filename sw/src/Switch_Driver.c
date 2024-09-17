#include "Switch_Driver.h"
#include "Global_Define.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Unified_Port_Init.h"
#include "../inc/PLL.h"

void Switch_Init(void){
    // write something to initalize the GPIO that take input from the switches based on your EID as defined in the lab doc
    SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
    while((SYSCTL_PRGPIO_R & 0x00000010) == 0){};
    GPIO_PORTE_DIR_R &= ~0x07; // (d) make button PE0-2 input
    GPIO_PORTE_AFSEL_R &= ~0x07;  //     disable alt funct on PE0-2
    GPIO_PORTE_DEN_R |= 0x07;     //     enable digital I/O on PE0-2  
    GPIO_PORTE_PCTL_R &= ~0x00000FFF; // configure PE0-2 as GPIO
    GPIO_PORTE_AMSEL_R = 0;       //     disable analog functionality
}

uint32_t getSwitchReading(void){
    return PE0 + PE1 + PE2;
}

// Test main for Switch_Driver.c
// int main(void){
// 		PLL_Init(Bus80MHz); 
//     Switch_Init();
// 		uint32_t switchReading = 0;
//     while(1){
//         switchReading = getSwitchReading();
// 				uint16_t dummyVar = switchReading;
//     }
// }
