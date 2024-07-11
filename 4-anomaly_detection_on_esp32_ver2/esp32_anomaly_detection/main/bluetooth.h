#ifndef MY_BLUETOOTH_H
#define MY_BLUETOOTH_H

#include "bluetooth.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "driver/uart.h"
#include "string.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gatt_common_api.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

 uint8_t find_char_and_desr_index(uint16_t handle);

 bool store_wr_buffer(esp_ble_gatts_cb_param_t *p_data);

 void free_write_buffer(void);

 void print_write_buffer(void);

void uart_task(void *pvParameters);

 void spp_uart_init(void);

#ifdef SUPPORT_HEARTBEAT
void spp_heartbeat_task(void * arg);
#endif

void spp_cmd_task(void * arg);

 void spp_task_init(void);

 void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

 void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);


 esp_err_t send_notification(uint8_t *data, uint16_t len);


 void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

 void my_bluetooth_init();

 #endif