#include <stdint.h>
#include "Time_Struct.h"

extern Time newTime;

void Systick_Init(uint32_t period);
void SysTick_Handler(void);
