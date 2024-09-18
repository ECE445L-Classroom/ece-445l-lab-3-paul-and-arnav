#include "LCD_Driver.h"
#include <stdint.h>
#include <stdio.h>
#include "../inc/PLL.h"
#include "../inc/ST7735.h"
#include "../inc/CortexM.h"
#include "Time_Struct.h"

void DrawNumber(int x, int y, int number, uint16_t color, uint16_t backgroundColor){
    char str[10]; //array of numbers
    sprintf(str, "%d", number);
    //setCursor(0,0);
    for(int i = 0; str[i] != 0; i++){
        ST7735_DrawChar((x+i * 6), y, str[i], color, backgroundColor, 1);
    }
}

void DrawTimeDigital(Time *timeVar, uint16_t color, uint16_t backgroundColor){
    char str[10]; //array of numbers

    if (timeVar->hours < 10) {
        sprintf(str, "0%d:", timeVar->hours);
    } else {
        sprintf(str, "%d:", timeVar->hours);
    }

    if (timeVar->minutes < 10) {
        sprintf(str, "%s0%d:", str, timeVar->minutes);
    } else {
        sprintf(str, "%s%d:", str, timeVar->minutes);
    }

    if (timeVar->seconds < 10) {
        sprintf(str, "%s0%d", str, timeVar->seconds);
    } else {
        sprintf(str, "%s%d", str, timeVar->seconds);
    }

    ST7735_SetCursor(0,0);
    for(int i = 0; str[i] != 0; i++){
        ST7735_DrawCharS(7 + (i * 15), 15, str[i], color, backgroundColor, 2);
    }
}

void DrawTimeAnalog(){
    
}


int main(void) {
    PLL_Init(Bus80MHz);    // bus clock at 80 MHz
    ST7735_InitR(INITR_REDTAB);

    Time time;
    setTimeValues(&time, 23, 58, 15);

    while(1) {
        DrawTimeDigital(&time, ST7735_BLUE, ST7735_BLACK);
        incrementTime(&time, 5);
        Clock_Delay1ms(50);
    }

    //DrawNumber(10,10,7,ST7735_BLUE,ST7735_BLACK);
    //ST7735_FillScreen(ST7735_RED);
}
