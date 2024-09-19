// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is left
// PE2 is right 
// PE3 is up
// PE4 is down
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "../inc/CortexM.h"
#include "Lab3.h"

// Module Imports
#include "Global_Define.h"
#include "Switch_Driver.h"
#include "LCD_Driver.h"
#include "Interrupts_Driver.h"
#include "Sound_Driver.h"

#define home 0
#define dontRedraw 0
#define redraw 1

// ---------- Prototypes   -------------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void handleSetting(Time *timeVar, uint32_t switchReading, uint8_t *pos, uint32_t *FSMState);
void DrawTime(uint8_t timeMode, uint8_t displayMode, uint8_t colorScheme, uint8_t redrawBackground, Time *timeVar, Time *oldTime, uint8_t Menu);
void Clock_Delay1ms(uint32_t n);

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  ST7735_InitR(INITR_REDTAB);
  //Systick_Init(80000 * 1000); // 1 second
  Clock_Count_Init(80000 * 1000); // 1 second
  Switch_Init();

  //TODO: Interrupt for the alarm
    // If b0 is pressed, then the alarm will be snoozed for 5 min*
    // If b1 is pressed, then the alarm will be turned off


  //TODO: Also initialize an interrupt for the sound

  Time currTime;
  setTimeValues(&currTime, 13, 33, 55);
  Time currAlarm;
  setTimeValues(&currAlarm, 1, 0, 0);
  uint8_t timePosition = 0;
  uint32_t FSM_State = home;
  uint8_t timeMode = twelveHour;
  uint8_t displayMode = digital;
  uint8_t prevColorScheme = light;
  uint8_t colorScheme = dark;

  uint32_t prevSwitchReading = 0;

  EnableInterrupts();

  while(1){
      // write this
      uint32_t switchReading = getSwitchReading();
      if (switchReading == prevSwitchReading && switchReading != 0) {
        continue;
      }
      prevSwitchReading = switchReading;

      switch (FSM_State){
        case home:
          if (compareTimes(&currTime, &newTime) != 0) {
            DrawTime(timeMode, displayMode, colorScheme, dontRedraw, &newTime, &currTime, homeMenu);
            setTimeValues(&currTime, newTime.hours, newTime.minutes, newTime.seconds);
          }

          if (switchReading == alarmOnOff) {
            //TODO: Toggle the alarm (start the timer interrupt)
          } else if (switchReading >= 0x1 && switchReading <= 0x4) {
            FSM_State = switchReading;
          }
          break;

        case setTime:
          DrawTime(timeMode, digital, colorScheme, dontRedraw, &currTime, &currTime, setMenu);
          handleSetting(&newTime, switchReading, &timePosition, &FSM_State);
          break;

        case setAlarm:
          DrawTime(timeMode, digital, colorScheme, dontRedraw, &currAlarm, &currTime, setMenu);
          handleSetting(&currAlarm, switchReading, &timePosition, &FSM_State);
          break;

        case changeDisplayMode:
          DrawTime(timeMode, displayMode, colorScheme, dontRedraw, &newTime, &currTime, modesMenu);
          // if (compareTimes(&currTime, &newTime) != 0) {
          //   DrawTime(timeMode, displayMode, colorScheme, 0, &newTime, &currTime);
          //   setTimeValues(&currTime, newTime.hours, newTime.minutes, newTime.seconds);
          // }

          if (switchReading == changeClockMode) {
            //Change the display mode between analog and digital
            displayMode = !displayMode;
            DrawTime(timeMode, displayMode, colorScheme, redraw, &newTime, &currTime, homeMenu);
            FSM_State = home;
          } else if (switchReading == changeTimeMode) {
            //Change the display mode between regular and military time
            timeMode = !timeMode;
            FSM_State = home;
          } else if (switchReading == changeColorScheme) {
            //Change the color scheme (Dark/Light Mode)
            colorScheme = !colorScheme;
            DrawTime(timeMode, displayMode, colorScheme, redraw, &newTime, &currTime, homeMenu);
            FSM_State = home;
          }

          break;
        
        default:
          //No buttons or an invalid combination was pressed
          break;
      }

      //Debounce the switches
      Clock_Delay1ms(10);
  }
}

void DrawTime(uint8_t timeMode, uint8_t displayMode, uint8_t colorScheme, uint8_t redrawBackground, Time *timeVar, Time *oldTime, uint8_t Menu) {
  uint16_t main_color;
  uint16_t background_color;

  if (colorScheme == dark) {
    main_color = ST7735_BLUE;
    background_color = ST7735_BLACK;
  } else {
    main_color = ST7735_BLACK;
    background_color = ST7735_WHITE;
  }

  if (redrawBackground) {
    setBackGround(background_color, colorScheme, displayMode);
  }

  if (displayMode == digital) {
    DrawTimeDigital(timeVar, timeMode, main_color, background_color);
  } else {
    DrawTimeAnalog(timeVar, oldTime, main_color, background_color);
  }

  DrawMenu(Menu, main_color, background_color);
}

void handleSetting(Time *timeVar, uint32_t switchReading, uint8_t *pos, uint32_t *FSMState) {
  if (switchReading == changePos) {
    // Change the time character being changed
    // When we reach the last position go back to home state
    if (*pos == 5) {
      *pos = 0;
      *FSMState = home;
    } else {
      *pos++;
    }
  } else if (switchReading == incNum) {
    incrementTime(timeVar, *pos);
  } else if (switchReading == decNum) {
    decrementTime(timeVar, *pos);
  } 
}
