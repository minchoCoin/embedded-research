# anomaly detection on esp32 ver2

# dataset
get training data using [getTraining.py](https://github.com/minchoCoin/embedded-research/blob/main/4-anomaly_detection_on_esp32_ver2/raspberrypi_receivedata/getTrainingData.py) and [esp32_senddata](https://github.com/minchoCoin/embedded-research/tree/main/4-anomaly_detection_on_esp32_ver2/esp32_senddata)

# training model
training model using [anomaly_dection_model_colab.ipynb](https://github.com/minchoCoin/embedded-research/blob/main/4-anomaly_detection_on_esp32_ver2/model/anomaly_detection_model_colab.ipynb)

# install tflite on esp32
refer [esp32 tflite github readme](https://github.com/espressif/esp-tflite-micro/blob/master/README.md)

# anomaly detection
anomaly detection using [this_code](https://github.com/minchoCoin/embedded-research/tree/main/4-anomaly_detection_on_esp32_ver2/esp32_anomaly_detection)

```cpp
    while(1){
        if(xQueueReceive(queue_data,&data,portMAX_DELAY)==pdPASS){
            bool anomaly=false;

            for(int i=0;i<8;++i){
                input[seq_original++] = data[i];//input array store original gyro/acce value
            }

            minmax_scale(data);
            for(int i=0;i<8;++i){
                //model_input_buffer[seq++] = (int8_t)(data[i] / input_scale + input_zero_point);
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
                    //get output(and dequantized)
                    //output[i] = (tflite::GetTensorData<int8_t>(model_output)[i] - output_zero_point) * output_scale;
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
                ...
            }
            ...
           }
           ...
        }
        ...
    }
```

# others
model_.png is generated with [Netron](https://github.com/lutzroeder/netron)

# references
- [esp32 tflite example](https://github.com/espressif/esp-tflite-micro/blob/master/examples/micro_speech/main/main_functions.cc)