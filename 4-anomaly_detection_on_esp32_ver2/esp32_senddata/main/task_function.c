#include "task_function.h"
#include "icm20948.h"
#include "pitchroll.h"
#include "bluetooth.h"
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
static const char* TAG = "task";
extern QueueHandle_t queue_data;
void measure_task(void *pvParameter){
    
    extern icm20948_gyro_value_t bias_gyro;
    extern icm20948_acce_value_t bias_acce;
    extern icm20948_handle_t* mysensor;
    extern bool enable_data_ntf; //warning: read only
    static icm20948_acce_value_t acce_value;
    static icm20948_gyro_value_t gyro_value;
    
    uint8_t int_status=0x00;
    static float pitch;
    static float roll;

    //ESP_LOGI("measure_task","measure_task has been created");
    while(1){
        ESP_ERROR_CHECK(icm20948_read(*mysensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
        if(int_status&0x01){
            ESP_ERROR_CHECK(icm20948_get_gyro(*mysensor, &gyro_value));
            ESP_ERROR_CHECK(icm20948_get_acce(*mysensor, &acce_value));
            int_status=0x00;
            //print time,gyro_x,gyro_y,gyro_z,acce_x,acce_y,acce_z
            //sprintf((char*)infoString,"%llu,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f",(int64_t)now.tv_sec * 1000000L + (int64_t)now.tv_usec,gyro_value.gyro_x - bias_gyro.gyro_x,gyro_value.gyro_y - bias_gyro.gyro_y,gyro_value.gyro_z - bias_gyro.gyro_z,acce_value.acce_x - bias_acce.acce_x,acce_value.acce_y- bias_acce.acce_y,acce_value.acce_z- bias_acce.acce_z);
            gyro_value.gyro_x -=bias_gyro.gyro_x;
            gyro_value.gyro_y -=bias_gyro.gyro_y;
            gyro_value.gyro_z -=bias_gyro.gyro_z;

            acce_value.acce_x -=bias_acce.acce_x;
            acce_value.acce_y -=bias_acce.acce_y;
            acce_value.acce_z -=bias_acce.acce_z;

            pitch = get_pitch(acce_value.acce_x,acce_value.acce_y,acce_value.acce_z);
            roll = get_roll(acce_value.acce_x,acce_value.acce_y,acce_value.acce_z);
            
            if(enable_data_ntf){
                float* arr = (float*)pvPortMalloc(8*sizeof(float));
                if(arr == NULL) ESP_LOGE(TAG,"memory allocation failed.");
                else{
                    arr[0]=gyro_value.gyro_x; arr[1] = gyro_value.gyro_y; arr[2] = gyro_value.gyro_z; arr[3] = acce_value.acce_x; arr[4] = acce_value.acce_y; arr[5] = acce_value.acce_z;
                    arr[6] = pitch; arr[7] = roll;
                    if(xQueueSend(queue_data,&arr,portMAX_DELAY)!=pdTRUE){
                        vPortFree(arr);
                    }
                }
            }
            

            ESP_ERROR_CHECK(icm20948_write(*mysensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    /* delete icm20948*/
    icm20948_delete(mysensor);
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(TAG, "I2C unitialized successfully");
}

void bluetooth_task(void *pvParameter){
    uint8_t infoString[200];
    float* data;
    while(1){
        if(xQueueReceive(queue_data,&data,portMAX_DELAY)==pdPASS){
            sprintf((char*)infoString,"%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%5f,%5f",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
            send_notification(infoString,strlen((char*)infoString));
            vPortFree(data);
        }
    }
    
}