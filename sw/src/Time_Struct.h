#include <stdint.h>

#ifndef TIME_STRUCT_H
#define TIME_STRUCT_H
// Struct to represent the time
typedef struct {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} Time;

// Function prototypes
void setTimeValues(Time *time, uint8_t hours, uint8_t minutes, uint8_t seconds);
uint8_t compareTimes(Time *time1, Time *time2);
void incrementTime(Time *time, uint8_t position);
void decrementTime(Time *time, uint8_t position);
void convertTo12Hour(Time *time, Time *newTime);

#endif
