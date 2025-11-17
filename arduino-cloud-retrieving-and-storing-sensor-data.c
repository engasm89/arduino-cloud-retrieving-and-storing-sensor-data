#include "freertos/FreeRTOS.h" // FreeRTOS
#include "freertos/task.h" // Tasks
#include "esp_log.h" // Logging
#include "mqtt_client.h" // MQTT client

static const char *TAG = "CLOUD"; // Tag

void app_main(void) { // Entry
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
  } // End loop
} // End app_main

