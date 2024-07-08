# embedded-research
The results of the undergraduate research student

# index
## 1-ICM20948-ESP32-Raspberry_Pi_4B
- ESP32 get acceleration and gyro sensor value from ICM20948 9-axis sensor using i2c communication
- before measurement, calibrating acceleration and gyro value (using first N values from starting)
- raspberry pi get acceleration and gyro value from ESP32 using bluetooth(ble)
- raspberry pi can pause the receving the values.

## 2-anomaly_detection
- anomaly detection on raspberry pi using LSTM autoencoder model(using tensorflow and tensorflow-lite)
- training data and anomaly data have generated using [getTrainingData.py](https://github.com/minchoCoin/embedded-research/blob/main/2-anomaly_detection/raspberry/getTrainingData.py)
    - data is saved as .csv file
    - esp32 send the values, and raspberry pi process the data and save the data.
- LSTM autoencoder model is generated with [anomaly_detection.ipynb](https://github.com/minchoCoin/embedded-research/blob/main/2-anomaly_detection/model/anomaly_detection.ipynb)

## 3-anomaly_detection_on_esp32
- anomaly detection on esp32 using CNN autoencoder model(using tensorflow-lite)
- using [esp32-tflite-micro](https://github.com/espressif/esp-tflite-micro)
- measure task: measuring sensor values and sending the values to 'detection task'
- detection task: detecting anomalies from receving values from 'measure task'
    - measure task send values using queue
