# anomaly detection on esp32 ver2

# dataset
get training data using [getTraining.py](https://github.com/minchoCoin/embedded-research/blob/main/4-anomaly_detection_on_esp32_ver2/raspberrypi_receivedata/getTrainingData.py) and [esp32_senddata](https://github.com/minchoCoin/embedded-research/tree/main/4-anomaly_detection_on_esp32_ver2/esp32_senddata)

# training model
training model using [anomaly_dection_model_colab.ipynb](https://github.com/minchoCoin/embedded-research/blob/main/4-anomaly_detection_on_esp32_ver2/model/anomaly_detection_model_colab.ipynb)

# install tflite on esp32
refer [esp32 tflite github readme](https://github.com/espressif/esp-tflite-micro/blob/master/README.md)

# video
[![Video Label](http://img.youtube.com/vi/oD-Kjb7j69U/0.jpg)](https://youtu.be/oD-Kjb7j69U)

[![Video Label](http://img.youtube.com/vi/o0k4yUBxlqs/0.jpg)](https://youtu.be/o0k4yUBxlqs)

# output example

## if anomaly detected...
```
I (14665) tflite: anomaly detected; (Gyro x value), (Gyro y value), (Gyro z value), (Accel x value), (Accel y value), (Accel z value), (pitch), (roll value)
anomaly_index: (index of anomaly value) : (anomaly value): expected:(expected value of anomaly index)
```
> **_NOTE:_**
> index of anomaly value:
> - 0: Gyro x
> - 1: Gyro y
> - 2: Gyro z
> - 3: Accel x
> - 4: Accel y
> - 5: Accel z
> - 6: pitch
> - 7: roll


example:
```
I (14665) tflite: anomaly detected; 14.02489, 155.73207, -90.38718, 1.15053, -0.28279, 0.04502, -0.24083, 1.32687
anomaly_index: 1 : 155.73207: expected:14.06686
```

## entire output example
```
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:7172
load:0x40078000,len:15540
load:0x40080400,len:4
ho 8 tail 4 room 4
load:0x40080404,len:3904
entry 0x40080640
I (30) boot: ESP-IDF v5.2.1 2nd stage bootloader
I (31) boot: compile time Jun 19 2024 15:00:35
I (31) boot: Multicore bootloader
I (35) boot: chip revision: v1.0
I (38) boot.esp32: SPI Speed      : 40MHz
I (43) boot.esp32: SPI Mode       : DIO
I (48) boot.esp32: SPI Flash Size : 2MB
I (52) boot: Enabling RNG early entropy source...
I (58) boot: Partition Table:
I (61) boot: ## Label            Usage          Type ST Offset   Length
I (69) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (76) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (83) boot:  2 factory          factory app      00 00 00010000 00100000
I (91) boot: End of partition table
I (95) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=2bd90h (179600) map
I (165) esp_image: segment 1: paddr=0003bdb8 vaddr=3ffbdb60 size=04260h ( 16992) load
I (172) esp_image: segment 2: paddr=00040020 vaddr=400d0020 size=a30d0h (667856) map
I (401) esp_image: segment 3: paddr=000e30f8 vaddr=3ffc1dc0 size=007dch (  2012) load
I (402) esp_image: segment 4: paddr=000e38dc vaddr=40080000 size=1a608h (108040) load
I (462) boot: Loaded app from partition at offset 0x10000
I (462) boot: Disabling RNG early entropy source...
I (474) cpu_start: Multicore app
I (483) cpu_start: Pro cpu start user code
I (483) cpu_start: cpu freq: 160000000 Hz
I (483) cpu_start: Application information:
I (486) cpu_start: Project name:     esp32_anomaly
I (491) cpu_start: App version:      1
I (496) cpu_start: Compile time:     Jun 24 2024 11:00:29
I (502) cpu_start: ELF file SHA256:  a462188ac...
I (507) cpu_start: ESP-IDF:          v5.2.1
I (512) cpu_start: Min chip rev:     v0.0
I (517) cpu_start: Max chip rev:     v3.99
I (521) cpu_start: Chip rev:         v1.0
I (526) heap_init: Initializing. RAM available for dynamic allocation:
I (534) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM
I (539) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM
I (546) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM
I (552) heap_init: At 3FFCC550 len 00013AB0 (78 KiB): DRAM
I (558) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (564) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (571) heap_init: At 4009A608 len 000059F8 (22 KiB): IRAM
I (578) spi_flash: detected chip: generic
I (581) spi_flash: flash io: dio
W (585) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (599) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (610) coexist: coex firmware version: 77cd7f8
I (615) main_task: Started on CPU0
I (625) main_task: Calling app_main()
I (625) tflite: model info: 2 1 128
TensorArena size: 20480
Arena used bytes: 6456
I (625) icm20948: I2C initialized successfully
I (635) icm20948: WHO_AM_I = 90
I (645) icm20948: icm20948 init complete
I (665) BTDM_INIT: BT controller compile version [0f0c5a2]
I (665) BTDM_INIT: Bluetooth MAC: 40:f5:20:70:62:66
I (665) phy_init: phy_version 4791,2c4672b,Dec 20 2023,16:06:06
I (965) GATTS_SPP_DEMO: my_bluetooth_init init bluetooth
I (1045) GATTS_SPP_DEMO: event = 0
I (1045) GATTS_SPP_DEMO: gatts_profile_event_handler 545
I (1055) GATTS_SPP_DEMO: gatts_profile_event_handler 548
I (1055) GATTS_SPP_DEMO: gatts_profile_event_handler 551
I (1065) GATTS_SPP_DEMO: event = 16
I (1065) GATTS_SPP_DEMO: The number handle =b
I (1065) GATTS_SPP_DEMO: GAP_EVT, event 4
I (1075) GATTS_SPP_DEMO: evI (1085) icm20948: bluetooth init complete
I (1095) GATTS_SPP_DEMO: GAP_EVT, event 6
I (1095) icm20948: calibrate start. please don't move!
I (1945) icm20948: calibrate complete.
I (1945) icm20948: creating task start...
I (1945) icm20948: measure task has been created
I (1945) tflite: detection int8 task has been created
I (1955) log: heap total size: 249096
I (1955) log: Heap free size: 150508(39.5783% used)
I (6665) tflite: anomaly detected; -1.76137, 3.96107, 0.60519, -0.21421, -0.90876, 0.08946, -1.32070, -0.23042
anomaly_index: 4 : -0.90876: expected:-0.21754

I (8275) tflite: anomaly detected; -24.24992, -5.35191, -3.31847, -0.02867, 1.39055, 0.70323, 1.10225, -0.01839
anomaly_index: 4 : 1.39055: expected:0.34042

I (11465) tflite: anomaly detected; -17.89878, 26.90763, -0.50931, -0.41197, -0.38044, -2.88320, -0.12989, -0.14072
anomaly_index: 3 : -0.41197: expected:-0.12358

I (14665) tflite: anomaly detected; 14.02489, 155.73207, -90.38718, 1.15053, -0.28279, 0.04502, -0.24083, 1.32687
anomaly_index: 1 : 155.73207: expected:14.06686

I (16265) tflite: anomaly detected; -26.81481, 152.22061, 210.84947, 0.15981, 0.14690, 0.36875, 0.35043, 0.38275
anomaly_index: 1 : 152.22061: expected:14.06686

I (17865) tflite: anomaly detected; -28.83008, 46.20534, 165.53648, -0.34947, -0.57185, -0.01308, -1.02193, -0.54844
anomaly_index: 1 : 46.20534: expected:14.06686

I (21065) tflite: anomaly detected; 21.75008, -175.33664, 6.28458, 1.16909, -0.03328, 1.01670, -0.02147, 0.85474
anomaly_index: 1 : -175.33664: expected:-11.08641

I (24265) tflite: anomaly detected; -10.54000, 191.30458, -11.41008, -0.22007, 0.09465, 0.63584, 0.13976, -0.32983
anomaly_index: 1 : 191.30458: expected:14.06686

I (30665) tflite: anomaly detected; 9.76534, -2.98550, 1.39908, 0.17397, 1.24504, -0.12490, 1.40045, 0.13815
anomaly_index: 4 : 1.24504: expected:0.05802

I (41865) tflite: anomaly detected; -75.63924, 13.94580, 121.85710, 0.52163, -0.12947, 0.21397, -0.22572, 1.12373
anomaly_index: 2 : 121.85710: expected:12.04550

I (43465) tflite: anomaly detected; -0.44840, 3.02977, 38.42199, 0.00747, -0.81843, -0.04384, -1.51651, 0.00911
anomaly_index: 2 : 38.42199: expected:11.33164

I (48265) tflite: anomaly detected; -12.83008, -40.45115, 40.39145, 0.31411, -0.46931, -0.41396, -0.73455, 0.46519
anomaly_index: 1 : -40.45115: expected:4.40011
```

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
- [esp32 bluetooth example](https://github.com/espressif/esp-idf/tree/master/examples/bluetooth/bluedroid/ble/ble_spp_server)
- [esp32 icm20948 library](https://github.com/listout/icm20948_driver)
- [https://underflow101.tistory.com/42](https://underflow101.tistory.com/42)