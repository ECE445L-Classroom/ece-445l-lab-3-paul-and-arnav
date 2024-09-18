#include "Sound_Driver.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "../inc/PLL.h"
#include "../inc/Unified_Port_Init.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void ToggleFunc(void){
    PC5 = ~PC5;
}

// int main(void){
//   PLL_Init(Bus80MHz);
//   SYSCTL_RCGCGPIO_R |= 0x02;// activate port B
//   while((SYSCTL_PRGPIO_R&0x02) == 0){}; // ready?
//   GPIO_PORTB_AFSEL_R |= 0x2C;//enable alt funct on PB 2,3,5
//   GPIO_PORTB_DEN_R |= 0x2C;// configure PB 2,3,5 as SSI
//   GPIO_PORTB_PCTL_R = 0x00000000;
//   GPIO_PORTB_AMSEL_R = 0; // disable analog functionality on PC
//   GPIO_PORTE_DIR_R = 0x2C;
//   Timer0A_Init(&ToggleFunc,80000,1);
//   EnableInterrupts();
//   while(1){};
// }
