/* i2c - Simple example

   Simple I2C example that shows how to initialize I2C
   as well as reading and writing from and to registers for a sensor connected over I2C.

   The sensor used in this example is a MPU9250 inertial measurement unit.

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "icm20948.h"
#include "bluetooth.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gatt_common_api.h"
static const char *TAG = "icm20948";


void app_main(void)
{
    uint8_t data[2];
    /*I2C and icm20948 setting start*/
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    //select bank
    icm20948_handle_t* sensor = icm20948_create(I2C_NUM_0,ICM20948_SENSOR_ADDR);
    ESP_ERROR_CHECK(icm20948_reset(*sensor));
    ESP_ERROR_CHECK(icm20948_get_deviceid(*sensor,&data[0]));

    ESP_LOGI(TAG,"WHO_AM_I = %X",data[0]);

    icm20948_acce_value_t acce_value;
    icm20948_gyro_value_t gyro_value;
    ESP_ERROR_CHECK(icm20948_wake_up(*sensor));
    ESP_ERROR_CHECK(icm20948_set_acce_dlpf(*sensor,ICM20948_DLPF_OFF));
    ESP_ERROR_CHECK(icm20948_set_acce_fs(*sensor,ACCE_FS_2G));
    ESP_ERROR_CHECK(icm20948_set_gyro_dlpf(*sensor,ICM20948_DLPF_OFF));
    ESP_ERROR_CHECK(icm20948_set_gyro_fs(*sensor,GYRO_FS_250DPS));

    /*I2C and icm20948 setting end*/

    /*bluetooth setting start*/
   esp_err_t ret;
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    // Initialize NVS
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(GATTS_TABLE_TAG, "%s init bluetooth", __func__);

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name(ret));
        return;
    }
    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name(ret));
        return;
    }

    esp_ble_gatts_register_callback(gatts_event_handler);
    esp_ble_gap_register_callback(gap_event_handler);
    esp_ble_gatts_app_register(ESP_SPP_APP_ID);

    spp_task_init();

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(GATTS_TABLE_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }

    /*bluetooth setting end*/
    
    
    while(1){
        ESP_ERROR_CHECK(icm20948_get_gyro(*sensor, &gyro_value));
        ESP_ERROR_CHECK(icm20948_get_acce(*sensor, &acce_value));

        uint8_t gyro_info[100];
        uint8_t acce_info[100];

        sprintf((char*)gyro_info,"GYRO(X,Y,Z): %.2f,%.2f,%.2f\n",gyro_value.gyro_x,gyro_value.gyro_y,gyro_value.gyro_z);
        sprintf((char*)acce_info,"ACCE(X,Y,Z): %.2f,%.2f,%.2f\n",acce_value.acce_x,acce_value.acce_y,acce_value.acce_z);

        ESP_LOGI(TAG,"GYRO(X,Y,Z): %.2f,%.2f,%.2f",gyro_value.gyro_x,gyro_value.gyro_y,gyro_value.gyro_z);
        ESP_LOGI(TAG,"ACCE(X,Y,Z): %.2f,%.2f,%.2f",acce_value.acce_x,acce_value.acce_y,acce_value.acce_z);

        ESP_ERROR_CHECK(send_notification(gyro_info,strlen((char*)gyro_info)));
        ESP_ERROR_CHECK(send_notification(acce_info,strlen((char*)acce_info)));

        vTaskDelay(configTICK_RATE_HZ);
    }
    
    /* delete icm20948*/
    icm20948_delete(sensor);
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(TAG, "I2C unitialized successfully");
}
