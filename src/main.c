/*
    Project: ESP-IDF Based 8X8 Matrix LED with Shift Register
    URL: https://github.com/DevMajed/ESP-IDF-Based-8X8-Matrix-with-Shift-Register.git
    Author: Majed Alharbi [ Majed Dev ]

    DISCLAIMER
    1. While I have thoroughly tested and approved my code, please use it at your own risk.
    2. You might come across some recurring comments in my code. I include them to ensure that readers
    can understand how everything works, even if they haven't seen my other projects. I apologize for any redundancy.
    3. The purpose of these codes is to facilitate an understanding of how the ESP-IDF framework works,
    especially since I struggled to learn it due to the lack of available resources.
    4. I consistently adopt a Code Modular Design approach for all my projects. This enhances readability, maintainability,
    and reusability. Be sure to explore other source files and headers to gain a complete understanding of the project.

    LICENSE
    Users are free to utilize, modify, or reproduce the code and its derivatives.
*/


// Header of Led_Matrix.C
#include "led_matrix.h"

// For C/C++
#include <stdio.h>
#include <stdlib.h>

// For Logging
#include "esp_log.h"
static const char *TAG = "MAIN";

// For FreeRTOS Delay and Drivers
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "driver/gpio.h"


// Array holding the data ( numbers and letters ) 0-9 and A-F
const uint8_t data [] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // " "
    0x00, 0x00, 0x01, 0x7F, 0x21, 0x00, 0x00, 0x00, // "1"
    0x00, 0x00, 0x31, 0x49, 0x45, 0x23, 0x00, 0x00, // "2"
    0x00, 0x00, 0x36, 0x49, 0x49, 0x22, 0x00, 0x00, // "3"
    0x00, 0x00, 0x02, 0x7F, 0x32, 0x0E, 0x00, 0x00, // "4"
    0x00, 0x00, 0x46, 0x49, 0x49, 0x79, 0x00, 0x00, // "5"
    0x00, 0x00, 0x3C, 0x4A, 0x49, 0x3E, 0x00, 0x00, // "6"
    0x00, 0x00, 0x70, 0x48, 0x4E, 0x60, 0x00, 0x00, // "7"
    0x00, 0x00, 0x2E, 0x51, 0x51, 0x2E, 0x00, 0x00, // "8"
    0x00, 0x00, 0x3E, 0x49, 0x49, 0x32, 0x00, 0x00, // "9"
    0x00, 0x00, 0x3E, 0x41, 0x41, 0x3E, 0x00, 0x00, // "0"
    0x00, 0x00, 0x3F, 0x44, 0x44, 0x3F, 0x00, 0x00, // "A"
    0x00, 0x00, 0x36, 0x49, 0x49, 0x7F, 0x00, 0x00, // "B"
    0x00, 0x00, 0x22, 0x41, 0x41, 0x3E, 0x00, 0x00, // "C"
    0x00, 0x00, 0x3E, 0x41, 0x41, 0x7F, 0x00, 0x00, // "D"
    0x00, 0x00, 0x41, 0x49, 0x49, 0x7F, 0x00, 0x00, // "E"
    0x00, 0x00, 0x40, 0x48, 0x48, 0x7F, 0x00, 0x00 // "F"
};


// Array holding the data for smiling face
const uint8_t smillingFace [] = {
    0x1C, 0x22, 0x51, 0x45, 0x45, 0x51, 0x22, 0x14
};


// Function to initilize Hardware
static void init_hw(void) {
    // An instance of the structure type gpio_config_t to configure GPIO Pins
    gpio_config_t io_conf = {
        // Bitmask to know what pins we are using in ESP32
        .pin_bit_mask = (1ULL << LATCH_PIN) | (1ULL << CLOCK_PIN) | (1ULL << DATA_PIN),
        // Set GPIO pins specified above to operate as an output (To Shift Register)
        .mode = GPIO_MODE_OUTPUT,
        // No interrupts needed
        .intr_type = GPIO_INTR_DISABLE,
        // No pull-up/pull-down needed
        .pull_up_en = 0,
        .pull_down_en = 0,
    };

    // Calling config function by passing the address of the io_conf struct to set GPIO
    gpio_config(&io_conf);
}


void loop () {
// Display Smiling Face
for (int i = 0; i < 50; i++) {
    // Initilizing Column data to first Bit to be synchronized with row operation
    int cols = 0x01;
    // Printing smiling face row data
    for (int j = 0; j  < 8; j++){
        // calling row function for each row of smiling face
        matrixRowsVal (smillingFace[j]);
        // scanning columns one by one ( ~ because of common anode LED configtraion)
        matrixColsVal (~cols);
        // Little dellay before the next row / column
        vTaskDelay (10 / portTICK_PERIOD_MS);
        // Shifting cols to move to the next column bit
        cols = cols << 1;
    }
}


// Display numbres-letters 0-9 and A-F, 128 bytes of data.
for (int i = 0; i < 128; i++) {
    // Initilizing Column data to first Bit to be synchronized with row operation
    int cols = 0x01;
    // Display 8 bytes of data ( a number or a letter ) then the next ...etc
    for ( int j = i; j < 8 + i; j ++) {
        // row data of the number or letter
        matrixRowsVal (data[j]);
        // scanning columns one by one ( ~ because of common anode LED configtraion)
        matrixColsVal (~cols);
        // Little dellay before the next row / column
        vTaskDelay (10/portTICK_PERIOD_MS);
         // Shifting cols to move to the next column bit
        cols = cols << 1;
    }
}
// end of loop function
}


void app_main() {
    // Set the log level for the TAG to ESP_LOG_DEBUG
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGE(TAG, "This is an error");
    ESP_LOGW(TAG, "This is a warning");
    ESP_LOGI(TAG, "This is an info");
    ESP_LOGD(TAG, "This is a debug");
    ESP_LOGV(TAG, "This is a verbose");

    // initlize hardware and setup GPIO
    init_hw();

    // interate forever through the loop function
    while (1) {
        // calling the loop function
        loop();
    }
}