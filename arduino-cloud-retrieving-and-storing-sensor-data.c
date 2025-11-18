/*
 * Course: Arduino Cloud Retrieving And Storing Sensor Data
 * Platform: Arduino
 * Author: Ashraf S A AlMadhoun
 * 
 * Description:
 * This code demonstrates the core concepts taught in the "Arduino Cloud Retrieving And Storing Sensor Data" course.
 * It provides a practical implementation that students can study, modify, and
 * use as a foundation for their own projects.
 * 
 * Learning Objectives:
 * - Understand the fundamental principles covered in this course
 * - Practice implementing the concepts with real code
 * - Build a working example that can be extended
 * 
 * Hardware Requirements:
 * - Development board (Arduino)
 * - Components as specified in CIRCUIT.md
 * - USB cable for programming
 * 
 * Pin Connections:
 * Refer to CIRCUIT.md for detailed wiring diagrams and pin assignments.
 * 
 * Usage:
 * 1. Review the code structure and comments
 * 2. Connect hardware according to CIRCUIT.md
 * 3. Upload code to your development board
 * 4. Monitor serial output for debugging
 * 
 * Course Link: https://www.udemy.com/course/arduino-cloud-retrieving-and-storing-sensor-data/
 * Repository: https://github.com/engasm89/arduino-cloud-retrieving-and-storing-sensor-data
 * 
 * Copyright (c) 2025 Ashraf S A AlMadhoun
 * Licensed under MIT License
 */

#include "freertos/FreeRTOS.h" // FreeRTOS
#include "freertos/task.h" // Tasks
#include "esp_log.h" // Logging
#include "mqtt_client.h" // MQTT client

static const char *TAG = "CLOUD"; // Tag

void app_main(void) { // Program entry point
  esp_mqtt_client_config_t cfg = { .uri = "mqtt://broker.hivemq.com" }; // Public broker URI
  esp_mqtt_client_handle_t client = esp_mqtt_client_init(&cfg); // Init client
  esp_mqtt_client_start(client); // Start client
  int value = 0; // Sensor value placeholder
  while (true) { // Loop
    char payload[32]; // Buffer
    snprintf(payload, sizeof(payload), "{\"value\": %d}", value++); // JSON payload
    esp_mqtt_client_publish(client, "/ashraf/esp32/sensor", payload, 0, 1, 0); // Publish
    ESP_LOGI(TAG, "Published: %s", payload); // Log
    vTaskDelay(pdMS_TO_TICKS(2000)); // 2s delay
    if (value % 5 == 0) { // Every 5th sample
      ESP_LOGI(TAG, "Subscribing and reading back state"); // Log
      esp_mqtt_client_subscribe(client, "/ashraf/esp32/cmd", 1); // Subscribe to commands
    } // End periodic subscribe
  } // End loop
} // End of main function

