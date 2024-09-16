#include <stdint.h>

/**
 * TODO: THIS
 * @brief Design your driver here! There are two things your driver needs to do:
 *
 * 1. Initialize SPI for your specific hardware (see page 965 on the TM4C
 *    datasheet).
 * 2. Accept a digital value (from 0 to (2^12 - 1)) and output a 16-bit data
 *    word via SPI that will be sent to the chip (see page 12 on the TLV5618
 *    datasheet).
 * 
 * Provided are two possible function declarations. You may modify this based on
 * your implementation and API design.
 */


/**
 * @brief dac_init initializes SPI at pins <TODO: STATE PINS HERE> to
 *        communicate with the TLV5618 12-bit SPI DAC.
 * 
 * @return int 0 if initialization was successful or a positive integer if an
 *         error occurred. <TODO: LIST ERROR CODES AND POSSIBLE ERROR EVENTS>
 */
int dac_init();

/**
 * @brief dac_output tells the DAC to output a specified voltage.
 * 
 * @param data 12-bit data value representing the voltage that should be output
 *        to the TLV5618.
 * @return int 0 if initialization was successful or a positive integer if an
 *         error occurred. <TODO: LIST ERROR CODES AND POSSIBLE ERROR EVENTS>
 */
int dac_output(uint16_t data);
