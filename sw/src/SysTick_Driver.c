#include "SysTick_Driver.h"

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}

void SysTick_Wait(uint32_t delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}

uint32_t Time;
// start the stopwatch
void SysTick_Start(void){
  Time = NVIC_ST_CURRENT_R;
}
// end the stopwatch, and return elased time in bus cycles
uint32_t SysTick_Stop(void){
  return (Time-NVIC_ST_CURRENT_R)&0x00FFFFFF;
}

void SysTick_Wait1s(uint32_t delay){
  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(80000000);  // wait 1s
  }
}