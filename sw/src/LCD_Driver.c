#include "LCD_Driver.h"
#include <stdint.h>
#include <stdio.h>
#include "../inc/PLL.h"
#include "../inc/ST7735.h"

void DrawNumber(int x, int y, int number, uint16_t color, uint16_t backgroundColor){
    char str[10]; //array of numbers
    sprintf(str, "%d", number);
    //setCursor(0,0);
    for(int i = 0; str[i] != 0; i++){
        ST7735_DrawChar((x+i * 6), y, str[i], color, backgroundColor, 1);
    }
}


// int main(void) {
//     PLL_Init(Bus80MHz);    // bus clock at 80 MHz
//     ST7735_InitR(INITR_REDTAB);
//     DrawNumber(10,10,7,ST7735_BLUE,ST7735_BLACK);
//     //ST7735_FillScreen(ST7735_RED);
// }
