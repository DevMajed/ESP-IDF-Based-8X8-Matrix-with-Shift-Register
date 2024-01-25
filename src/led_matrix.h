// led_matrix.h

#ifndef LED_MATRIX_H 
#define LED_MATRIX_H

// Headers
#include <stdint.h>

// Constants for pins
#define DATA_PIN 15 // where we send all serial data
#define CLOCK_PIN 4 // clock, at each tick, one bit shown from shift register
#define LATCH_PIN 2 // latch, when high, output pins reflect shift register

// Function prototypes
void matrixRowsVal (uint8_t value);
void matrixColsVal (uint8_t value);

#endif // LED_MATRIX_H