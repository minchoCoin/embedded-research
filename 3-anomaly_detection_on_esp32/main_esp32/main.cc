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
#include <cstdio>
#include "esp_log.h"
#include "driver/i2c.h"
#include "icm20948.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gatt_common_api.h"
#include "task_function.h"
#include "pitchroll.h"
#include "bluetooth.h"
#include "model.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/core/c/common.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "memory_log.h"
static const char *TAG = "icm20948";
static const char *TAGTF="tflite";

icm20948_handle_t* mysensor;

QueueHandle_t queue_data;
//QueueHandle_t queue_bluetooth;

icm20948_gyro_value_t bias_gyro;
icm20948_acce_value_t bias_acce;

const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;

constexpr int kTensorArenaSize = 30 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
tflite::MicroMutableOpResolver<11> micro_op_resolver;

int setup_model();
extern "C" void app_main(void)
{

    queue_data = xQueueCreate(300, sizeof(float *));
    //queue_bluetooth = xQueueCreate(10,sizeof(char*));
    if (queue_data == NULL) {
        ESP_LOGE(TAG, "Failed to create queue_data");
        return;
    }
    /*
    if ( queue_bluetooth == NULL){
        ESP_LOGE(TAG, "Failed to create queue_bluetooth");
        return;
    }
    */
    if(setup_model()==0){
        ESP_LOGE(TAGTF,"fail to init model");
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
    xTaskCreate(&measure_task, "measure_task",2048,NULL,6,NULL);
    ESP_LOGI(TAG,"measure task has been created");
    xTaskCreate(&detection_task, "detect_task", 4096, NULL, 4, NULL);
    ESP_LOGI("tflite","detection task has been created");
    //xTaskCreate(&bluetooth_task, "blue_task", 2048, NULL, 3, NULL); //due to the memory, delete bluetooth task and concatenate with detection task.
    
    print_heap_size_info();
    
    while(1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    
}


//https://www.freertos.org/a00118.html
//https://github.com/espressif/esp-tflite-micro/tree/master
//https://colab.research.google.com/github/tensorflow/tensorflow/blob/master/tensorflow/lite/examples/experimental_new_converter/Keras_LSTM_fusion_Codelab.ipynb?hl=pt#scrollTo=0-b0IKK2FGuO
//https://github.com/espressif/esp-tflite-micro/blob/master/examples/micro_speech/main/main_functions.cc
//https://github.com/espressif/esp-tflite-micro/blob/master/examples/hello_world/main/main_functions.cc
//https://github.com/espressif/esp-tflite-micro/issues/7
//https://esp32.com/viewtopic.php?t=23384

int setup_model(){
  
  
  //tensor_arena = (uint8_t *) heap_caps_malloc(kTensorArenaSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  
  TfLiteTensor* model_input= nullptr;
TfLiteTensor* model_output= nullptr;
    model = tflite::GetModel(model_tflite);
 //model init start
    if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf("Model provided is schema version %d not equal to supported "
                "version %d.", model->version(), TFLITE_SCHEMA_VERSION);
    return 0;
  }
  if(micro_op_resolver.AddShape()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddStridedSlice()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddPack()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddReshape()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddAdd()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddMul()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddConv2D()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddRelu()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddMaxPool2D()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddResizeNearestNeighbor()!=kTfLiteOk) return 0;
  if(micro_op_resolver.AddLogistic()!=kTfLiteOk) return 0;
  
  static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    MicroPrintf("Allocate tensor failed");
    return 0;
  }
  model_input = interpreter->input(0);

  ESP_LOGI(TAGTF,"model info: %d %d %d",model_input->dims->size, model_input->dims->data[0],model_input->dims->data[1]);
  /*
  if(model_input->dims->size != 3 || model_input->dims->data[0]!=1 || model_input->dims->data[1]!=1 || model_input->dims->data[2]!=8 || model_input->type !=kTfLiteFloat32){
    MicroPrintf("Bad input tensor parameters in model");
   return 0;
  }
  */
  if (model_input->data.f == nullptr) {
    MicroPrintf("input->data.f == nullptr");
    return 0;
  }

  if (model_input->data.data == nullptr) {
    MicroPrintf("input->data.data == nullptr ");
    return 0;
  }


if (interpreter->initialization_status() != kTfLiteOk) {
    MicroPrintf("Interpreter initialization failed");
   return 0;
}
  MicroPrintf("TensorArena size: %d", kTensorArenaSize);
  MicroPrintf("Arena used bytes: %d", interpreter->arena_used_bytes());

    //model init end
    if (interpreter->initialization_status() != kTfLiteOk) {
    MicroPrintf("Interpreter initialization failed");
    
    return 0;
    }
    return 1;
}