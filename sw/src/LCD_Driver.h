#include <stdint.h>
#include "Time_Struct.h"

void DrawNumber(int x, int y, int number, uint16_t color, uint16_t backgroundColor);
void DrawTimeDigital(Time *timeVar, int timeMode, uint16_t color, uint16_t backgroundColor);
void DrawTimeAnalog(Time *timeVar, Time *prevTime, uint16_t color, uint16_t backgroundColor);
void setBackGround(uint16_t color, uint8_t displayMode);
