#include "Time_Struct.h"

uint8_t modNegative(int num, int mod);

void setTimeValues(Time *time, uint8_t hours, uint8_t minutes, uint8_t seconds) {
    time->hours = hours;
    time->minutes = minutes;
    time->seconds = seconds;
}

uint8_t compareTimes(Time *time1, Time *time2) {
    if (time1->hours != time2->hours) {
        return 1;
    } else if (time1->minutes != time2->minutes) {
        return 1;
    } else if (time1->seconds != time2->seconds) {
        return 1;
    }
    return 0;
}

void incrementTime(Time *time, uint8_t position){
    uint8_t incAmt = 1;
    if (position % 2 == 0) {
        incAmt = 10;
    }

    if (position < 2) {
        time->hours = (time->hours + incAmt) % 24;    
    } else if (position < 4) {
        uint8_t new_minutes = time->minutes + incAmt;
        time->minutes = (new_minutes) % 60;
        if (new_minutes >= 60) {
            incrementTime(time, 1);
        }
    } else if (position < 6) {
        uint8_t new_seconds = time->seconds + incAmt;
        time->seconds = (new_seconds) % 60;
        if (new_seconds >= 60) {
            incrementTime(time, 3);
        }
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
    setTimeValues(newTime, time->hours, time->minutes, time->seconds);
    if (newTime->hours > 12) {
        newTime->hours -= 12;
    } else if (newTime->hours == 0) {
        newTime->hours = 12;
    }
} 
