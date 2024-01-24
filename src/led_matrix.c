// Header of Led_Matrix.C
#include "led_matrix.h"

// For C/C++
#include <stdio.h>
#include <stdlib.h>

// For FreeRTOS Delay and Drivers
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "driver/gpio.h"

/*
Functions for column and row matrix operation :
1 : Initilize LATCH_PIN to 0, Input State
2 : Take 8-Bit value as an argument
3 : Pass Row/Column Data to DATA_PIN serially bit by bit by shifting MSB to LSB
4 : After each Bit, toggle SRCLK to shift data to the "Shift Register"
5 : After done of 8-Bits, they are awaiting at outputs Q0 to Q7
5 : Ttoggle LATCH_PIN to take snapshot and display all data at Q0 - Q7
*/

// Column Function
void matrixColsVal(uint8_t value) {
    // Initialize LATCH_PIN
    gpio_set_level(LATCH_PIN, 0);

    for (int i = 7; i >= 0; i--) {
        // Loop to pass column data to DATA_PIN serially
        gpio_set_level(DATA_PIN, (value >> i) & 0b00000001);
        // Toggle SRCLK to shift data to the "Shift Register"
        gpio_set_level(CLOCK_PIN, 1);
        gpio_set_level(CLOCK_PIN, 0);
    }

    // Toggle LATCH_PIN to take Snapshot and Display
    gpio_set_level(LATCH_PIN, 1);
}


// Row  Function
void matrixRowsVal (uint8_t value) {
    // Initialize LATCH_PIN
    gpio_set_level(LATCH_PIN, 0);

    for (int i = 7; i >= 0; i--) {
        // Loop to pass column data to DATA_PIN serially
        gpio_set_level(DATA_PIN, (value >> i) & 0b00000001);
        // Toggle SRCLK to shift data to the "Shift Register"
        gpio_set_level(CLOCK_PIN, 1);
        gpio_set_level(CLOCK_PIN, 0);
    }

    // Toggle LATCH_PIN to take Snapshot and Display
    gpio_set_level(LATCH_PIN, 1);
}