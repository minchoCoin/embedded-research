# anomaly_detection on raspberry pi
esp32 send icm20948 sensor value to raspberry pi, and raspberry pi detect anomaly using tensorflow lite(with LSTM autoencoder model)

model_.png generated with [Netron](https://github.com/lutzroeder/netron)

# demo video
you can watch the video via clicking the picture below

[![Video Label](http://img.youtube.com/vi/fdbXPVKhFWE/0.jpg)](https://youtu.be/fdbXPVKhFWE)

# references
- [https://velog.io/@jaehyeong/LSTM-Autoencoder-for-Anomaly-Detection](https://velog.io/@jaehyeong/LSTM-Autoencoder-for-Anomaly-Detection)
- [https://github.com/listout/icm20948_driver](https://github.com/listout/icm20948_driver)
- [https://github.com/espressif/esp-idf/tree/master/examples/bluetooth/bluedroid/ble/ble_spp_server/main](https://github.com/espressif/esp-idf/tree/master/examples/bluetooth/bluedroid/ble/ble_spp_server/main)
- [https://forums.developer.nvidia.com/t/failed-building-wheel-of-h5py/263322/3](https://forums.developer.nvidia.com/t/failed-building-wheel-of-h5py/263322/3)