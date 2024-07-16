#include <stdio.h>
#include <algorithm>
#include "task_function.h"
#include "driver/i2c.h"
#include "bluetooth.h"
#include "pitchroll.h"
#include "minmaxscaler.h"
#include "task_function.h"
#include "model.h"
#include "icm20948.h"
#include "math.h"
#include "esp_log.h"
#include "memory_log.h"
#include "model.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

#define ANOMALY_THRESHOLD 1.0

extern QueueHandle_t queue_data;

static const char *TAG = "icm20948";
static const char *TAGTF="tflite";

void detection_int8_task(void *pvParameter){
    extern tflite::MicroInterpreter* interpreter;
    TfLiteTensor*model_input= interpreter->input(0);
    TfLiteTensor*model_output= interpreter->output(0);
    int8_t* model_input_buffer = tflite::GetTensorData<int8_t>(model_input);
    float* data;
    int anomaly_index=0;
    int anomaly_index_share=0;
    int anomaly_index_remain=0;
    //ESP_LOGI("detection task","detection task created");

    const float input_scale = model_input->params.scale;
    const float input_zero_point = model_input->params.zero_point;

    const float output_scale = model_output->params.scale;
    const float output_zero_point = model_output->params.zero_point;
    float input[128]; //original_value
    float input_scaled[128];
    float output[128]; //scaled ->original
    float error[128];
    char message[200];
    //SEQ_LEN=16 -->sequences_shape = (,128)
    int seq=0;
    int seq_original=0;
    while(1){
        if(xQueueReceive(queue_data,&data,portMAX_DELAY)==pdPASS){
            bool anomaly=false;

            for(int i=0;i<8;++i){
                input[seq_original++] = data[i];//input array store original gyro/acce value
            }

            minmax_scale(data);
            for(int i=0;i<8;++i){
                model_input_buffer[seq] = (int8_t)(data[i] / input_scale + input_zero_point);
                //model_input_buffer[seq] = data[i]; //model input buffer store scaled gyro/acce value
                input_scaled[seq] = data[i];
                seq++;
            }
           if(seq==128){
            seq=0;
            seq_original=0;
            TfLiteStatus invoke_status = interpreter->Invoke();
            if (invoke_status != kTfLiteOk) {
                MicroPrintf("Invoke failed");
            }
            else{
                for(int i=0;i<128;++i){
                    //get output(and dequantized)
                    output[i] = (tflite::GetTensorData<int8_t>(model_output)[i] - output_zero_point) * output_scale;
                    //output[i] = tflite::GetTensorData<float_t>(model_output)[i]; //output is scaled value
                    //calculate reconstructed_error
                    
                }
                for(int i=0;i<128;++i){
                    error[i] = fabs(input_scaled[i] - output[i]);
                    if(error[i]>ANOMALY_THRESHOLD){
                        anomaly=true;
                        anomaly_index=i;
                        break;
                    }
                }
                for(int i=0;i<128;i+=8){
                    minmax_scale_revert(output+i);
                }
                //now, output is original value.
                if(anomaly){
                    anomaly=false;
                    
                    
                    anomaly_index_share = anomaly_index/8;
                    anomaly_index_remain = anomaly_index%8;
                    sprintf(message,"anomaly detected; %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f\nanomaly_index: %d : %.5f: expected:%.5f\n",
                            input[anomaly_index_share*8+0],input[anomaly_index_share*8+1],input[anomaly_index_share*8+2],input[anomaly_index_share*8+3],input[anomaly_index_share*8+4],input[anomaly_index_share*8+5],input[anomaly_index_share*8+6],input[anomaly_index_share*8+7],
                            anomaly_index_remain ,input[anomaly_index],output[anomaly_index]);
                    ESP_LOGI(TAGTF,"%s",message);
                    send_notification((uint8_t*)message,strlen(message));
                    
                }
                
            }
           }
            
            vPortFree(data);
            data=NULL;
        }
    }
}

void detection_task(void *pvParameter){

    extern tflite::MicroInterpreter* interpreter;
    TfLiteTensor*model_input= interpreter->input(0);
    TfLiteTensor*model_output= interpreter->output(0);
    float_t* model_input_buffer = tflite::GetTensorData<float_t>(model_input);
    float* data;
    int anomaly_index=0;
    int anomaly_index_share=0;
    int anomaly_index_remain=0;
    //ESP_LOGI("detection task","detection task created");

    
    float input[128]; //original_value
    float input_scaled[128];
    float output[128]; //scaled ->original
    float error[128];
    char message[200];
    //SEQ_LEN=16 -->sequences_shape = (,128)
    int seq=0;
    int seq_original=0;
    while(1){
        if(xQueueReceive(queue_data,&data,portMAX_DELAY)==pdPASS){
            bool anomaly=false;

            for(int i=0;i<8;++i){
                input[seq_original++] = data[i];//input array store original gyro/acce value
            }

            minmax_scale(data);
            for(int i=0;i<8;++i){
                model_input_buffer[seq] = data[i]; //model input buffer store scaled gyro/acce value
                input_scaled[seq] = data[i];
                seq++;
            }
           if(seq==128){
            seq=0;
            seq_original=0;
            TfLiteStatus invoke_status = interpreter->Invoke();
            if (invoke_status != kTfLiteOk) {
                MicroPrintf("Invoke failed");
            }
            else{
                for(int i=0;i<128;++i){
                    output[i] = tflite::GetTensorData<float_t>(model_output)[i]; //output is scaled value
                    //calculate reconstructed_error
                    
                }
                for(int i=0;i<128;++i){
                    error[i] = fabs(input_scaled[i] - output[i]);
                    if(error[i]>ANOMALY_THRESHOLD){
                        anomaly=true;
                        anomaly_index=i;
                        break;
                    }
                }
                for(int i=0;i<128;i+=8){
                    minmax_scale_revert(output+i);
                }
                //now, output is original value.
                if(anomaly){
                    anomaly=false;
                    
                    
                    anomaly_index_share = anomaly_index/8;
                    anomaly_index_remain = anomaly_index%8;
                    sprintf(message,"anomaly detected; %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f\nanomaly_index: %d : %.5f: expected:%.5f\n",
                            input[anomaly_index_share*8+0],input[anomaly_index_share*8+1],input[anomaly_index_share*8+2],input[anomaly_index_share*8+3],input[anomaly_index_share*8+4],input[anomaly_index_share*8+5],input[anomaly_index_share*8+6],input[anomaly_index_share*8+7],
                            anomaly_index_remain ,input[anomaly_index],output[anomaly_index]);
                    ESP_LOGI(TAGTF,"%s",message);
                    send_notification((uint8_t*)message,strlen(message));
                    
                }
                
            }
           }
            
            vPortFree(data);
            data=NULL;
        }
    }
}

void measure_task(void *pvParameter){
    extern icm20948_gyro_value_t bias_gyro;
    extern icm20948_acce_value_t bias_acce;
    extern icm20948_handle_t* mysensor;
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
            
            float* arr = (float*)pvPortMalloc(8*sizeof(float));
            if(arr == NULL) ESP_LOGE(TAG,"memory allocation failed.");
            else{
                arr[0]=gyro_value.gyro_x; arr[1] = gyro_value.gyro_y; arr[2] = gyro_value.gyro_z; arr[3] = acce_value.acce_x; arr[4] = acce_value.acce_y; arr[5] = acce_value.acce_z;
                arr[6] = pitch; arr[7] = roll;
                if(xQueueSend(queue_data,&arr,portMAX_DELAY)!=pdTRUE){
                    vPortFree(arr);
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
