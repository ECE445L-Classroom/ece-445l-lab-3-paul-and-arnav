#include <stdint.h>

// Struct to represent the time
typedef struct {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} Time;

// Function prototypes
void initTime(Time *time, uint8_t hours, uint8_t minutes, uint8_t seconds);
void incrementTime(Time *time, uint8_t position);
void decrementTime(Time *time, uint8_t position);
void convertTo12Hour(Time *time, Time *newTime);
