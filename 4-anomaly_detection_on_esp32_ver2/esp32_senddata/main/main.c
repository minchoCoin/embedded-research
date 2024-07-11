#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "icm20948.h"
#include "bluetooth.h"
#include "task_function.h"
static const char* TAG = "send_data";
icm20948_handle_t* mysensor;

QueueHandle_t queue_data;

icm20948_gyro_value_t bias_gyro;
icm20948_acce_value_t bias_acce;


void app_main(void){
    queue_data = xQueueCreate(500, sizeof(float *));
    if (queue_data == NULL) {
        ESP_LOGE(TAG, "Failed to create queue_data");
        return;
    }

    mysensor= my_icm20948_init();
    ESP_LOGI(TAG,"icm20948 init complete");
    my_bluetooth_init();
    ESP_LOGI(TAG,"bluetooth init complete");

    ESP_LOGI(TAG,"calibrate start. please don't move!");
    ESP_ERROR_CHECK(calibrate_gyro(*mysensor,&bias_gyro));
    ESP_ERROR_CHECK(calibrate_acce(*mysensor,&bias_acce));
    ESP_LOGI(TAG,"calibrate complete.");
    ESP_ERROR_CHECK(icm20948_set_bank(*mysensor,0));

    ESP_LOGI(TAG,"creating task start...");
    xTaskCreate(&measure_task, "measure_task",2048,NULL,4,NULL);
    ESP_LOGI(TAG,"measure task has been created");
    xTaskCreate(&bluetooth_task, "detect_task", 2048, NULL, 6, NULL);
    ESP_LOGI(TAG,"bluetooth task has been created");

    while(1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}