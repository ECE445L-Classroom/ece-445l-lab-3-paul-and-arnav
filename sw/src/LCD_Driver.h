#include <stdint.h>
#include "Time_Struct.h"

void DrawTimeDigital(Time *timeVar, int timeMode, uint16_t color, uint16_t backgroundColor);
void DrawTimeAnalog(Time *timeVar, Time *prevTime, uint16_t color, uint16_t backgroundColor);
void setBackGround(uint16_t color, uint8_t colorScheme, uint8_t displayMode);
void DrawMenu(uint8_t Menu, uint16_t color, uint16_t backgroundColor);
