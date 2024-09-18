#include <stdint.h>
#include "Time_Struct.h"

extern Time newTime;

void Systick_Init(uint32_t period);
void Clock_Count_Init(uint32_t period);