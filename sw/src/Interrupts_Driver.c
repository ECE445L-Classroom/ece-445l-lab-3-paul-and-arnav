#include "Interrupts_Driver.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/SysTick.h"
#include "../inc/PLL.h"
#include "../inc/Timer0A.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

Time newTime;

void Systick_Init(uint32_t period){
  NVIC_ST_CTRL_R = 0;
  NVIC_ST_RELOAD_R = period - 1;
  NVIC_ST_CURRENT_R = 0;
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_ST_CTRL_R = 0x00000007;
}

void SysTick_Handler(void){
    
}

void Counter_Func() {
  GPIO_PORTF_DATA_R ^= 0x02; //Toggle the LED 
  incrementTime(&newTime, 5);
}

void Heartbeat_Init() {
  SYSCTL_RCGCGPIO_R |= 0x20;     // 1) activate Port F
  while((SYSCTL_PRGPIO_R & 0x20)!=0x20){}; // wait to finish activating
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;// 2a) unlock GPIO Port F Commit Register
  GPIO_PORTF_CR_R = 0x1F;        // 2b) enable commit for PF4-PF0
  GPIO_PORTF_AMSEL_R &= ~0x1F;   // 3) disable analog functionality on PF4-PF0
  GPIO_PORTF_PCTL_R = 0x00000000;// 4) configure PF0-PF4 as GPIO
  GPIO_PORTF_DIR_R = 0x0E;       // 5) make PF0 and PF4 in PF3-1 output
  GPIO_PORTF_AFSEL_R = 0;        // 6) disable alt funct on PF0 and PF4
  GPIO_PORTF_PUR_R = 0x11;       // enable weak pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;       // 7) enable digital I/O on PF0-PF4
}

void Clock_Count_Init(uint32_t period){
  setTimeValues(&newTime, 1, 0, 0);
  Heartbeat_Init();
  Timer0A_Init(&Counter_Func, period, 1);
}

// int main(void){
//   DisableInterrupts();
//   PLL_Init(Bus80MHz);
//   Systick_Init(80000 * 1000); // 1 seconds
// 	EnableInterrupts();
//   while(1){};
// }
