#include "Time_Struct.h"

void initTime(Time *time, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
}

void incrementTime(Time *time, uint8_t position){
    uint8_t incAmt = 1;
    if (position % 2 == 0) {
        incAmt = 10;
    }

    if (position < 2) {
        time->hours = (time->hours + incAmt) % 24;    
    } else if (position < 4) {
        time->minutes = (time->minutes + incAmt) % 60;
    } else if (position < 6) {
        time->seconds = (time->seconds + incAmt) % 60;
    }
}


void decrementTime(Time *time, uint8_t position){
    uint8_t incAmt = 1;
    if (position % 2 == 0) {
        incAmt = 10;
    }

    if (position < 2) {
        time->hours = modNegative(time->hours - incAmt, 24);
    } else if (position < 4) {
        time->minutes = modNegative(time->minutes - incAmt, 60);
    } else if (position < 6) {
        time->seconds = modNegative(time->seconds - incAmt, 60);
    }
}

uint8_t modNegative(int num, int mod) {
    if (num < 0) {
        return (num + mod);
    }
    return num % mod;
}

void convertTo12Hour(Time *time, Time *newTime) {
    initTime(&newTime, time->hours, time->minutes, time->seconds);
    if (newTime->hours > 12) {
        newTime->hours -= 12;
    } else if (newTime->hours == 0) {
        newTime->hours = 12;
    }
} 