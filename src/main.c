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

void app_main() {
    // Set the log level for the TAG to ESP_LOG_DEBUG
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGE(TAG, "This is an error");
    ESP_LOGW(TAG, "This is a warning");
    ESP_LOGI(TAG, "This is an info");
    ESP_LOGD(TAG, "This is a debug");
    ESP_LOGV(TAG, "This is a verbose");



}