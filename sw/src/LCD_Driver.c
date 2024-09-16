#include "LCD_Driver.h"

void DrawNumber(int x, int y, int number, uint16_t color, uint16_t backgroundColor){
    char str[10]; //array of numbers
    sprintf(str, "%d", number);
    
    for(int i = 0; str[i] != 0; i++){
        ST7735_DrawChar((x+i * 6), y, str[i], color, backgroundColor, 1);
    }
}