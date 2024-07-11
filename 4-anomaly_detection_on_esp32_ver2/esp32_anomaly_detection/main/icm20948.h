#ifndef ICM20948_H
#define ICM20948_H
#include <cstdio>
#include "esp_log.h"
#include "driver/i2c.h"
#define ICM20948_SENSOR_ADDR                 0x68        /*!< Slave address of the MPU9250 sensor */
#define ICM20948_REG_BANK_SEL               0x7F
#define ICM20948_WHO_AM_I_REG_ADDR           0x00        /*!< Register addresses of the "who am I" register */

#define ICM20948_PWR_MGMT_1                   0x06

#define ICM20948_GYRO_CONFIG_1  0x01
#define ICM20948_ACCEL_CONFIG           0x20
#define RESET_BIT                               1

#define ICM20948_ACCEL_XOUT_H   0x2D
#define ICM20948_ACCEL_XOUT_L   0x2E
#define ICM20948_ACCEL_YOUT_H   0x2F
#define ICM20948_ACCEL_YOUT_L   0x30
#define ICM20948_ACCEL_ZOUT_H   0x31
#define ICM20948_ACCEL_ZOUT_L   0x32

#define ICM20948_GYRO_XOUT_H   0x33
#define ICM20948_GYRO_XOUT_L   0x34
#define ICM20948_GYRO_YOUT_H   0x35
#define ICM20948_GYRO_YOUT_L   0x36
#define ICM20948_GYRO_ZOUT_H   0x37
#define ICM20948_GYRO_ZOUT_L   0x38

#define I2C_MASTER_SCL_IO           22      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              I2C_NUM_0                         /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define ICM20948_INT_STATUS_1	0x1A

#define NUM_SAMPLE 100



typedef enum {
	ACCE_FS_2G = 0,  /*!< Accelerometer full scale range is +/- 2g */
	ACCE_FS_4G = 1,  /*!< Accelerometer full scale range is +/- 4g */
	ACCE_FS_8G = 2,  /*!< Accelerometer full scale range is +/- 8g */
	ACCE_FS_16G = 3, /*!< Accelerometer full scale range is +/- 16g */
} icm20948_acce_fs_t;

typedef enum {
	GYRO_FS_250DPS = 0,  /*!< Gyroscope full scale range is +/- 250 degree per sencond */
	GYRO_FS_500DPS = 1,  /*!< Gyroscope full scale range is +/- 500 degree per sencond */
	GYRO_FS_1000DPS = 2, /*!< Gyroscope full scale range is +/- 1000 degree per sencond */
	GYRO_FS_2000DPS = 3, /*!< Gyroscope full scale range is +/- 2000 degree per sencond */
} icm20948_gyro_fs_t;

typedef struct {
	int16_t raw_acce_x;
	int16_t raw_acce_y;
	int16_t raw_acce_z;
} icm20948_raw_acce_value_t;

typedef struct {
	int16_t raw_gyro_x;
	int16_t raw_gyro_y;
	int16_t raw_gyro_z;
} icm20948_raw_gyro_value_t;

typedef struct {
	float acce_x;
	float acce_y;
	float acce_z;
} icm20948_acce_value_t;

typedef struct {
	float gyro_x;
	float gyro_y;
	float gyro_z;
} icm20948_gyro_value_t;



typedef enum {
	ICM20948_DLPF_0,
	ICM20948_DLPF_1,
	ICM20948_DLPF_2,
	ICM20948_DLPF_3,
	ICM20948_DLPF_4,
	ICM20948_DLPF_5,
	ICM20948_DLPF_6,
	ICM20948_DLPF_7,
	ICM20948_DLPF_OFF
} icm20948_dlpf_t;
typedef struct {
	i2c_port_t bus;
	gpio_num_t int_pin;
	uint16_t dev_addr;
	uint32_t counter;
	float dt; /*!< delay time between two measurements, dt should be small (ms level) */
	struct timeval *timer;
} icm20948_handle_t;


esp_err_t
icm20948_write(icm20948_handle_t sensor,
               const uint8_t reg_start_addr,
               const uint8_t *const data_buf,
               const uint8_t data_len);

 esp_err_t
icm20948_read(icm20948_handle_t sensor, const uint8_t reg_start_addr, uint8_t *const data_buf, const uint8_t data_len);

icm20948_handle_t*
icm20948_create(i2c_port_t port, const uint16_t dev_addr);
void
icm20948_delete(icm20948_handle_t* sensor);
/**
 * @brief i2c master initialization
 */
 esp_err_t i2c_master_init(void);

esp_err_t
icm20948_set_bank(icm20948_handle_t sensor, uint8_t bank);


esp_err_t
icm20948_reset(icm20948_handle_t sensor);

esp_err_t
icm20948_get_deviceid(icm20948_handle_t sensor, uint8_t *const deviceid);
 esp_err_t
icm20948_wake_up(icm20948_handle_t sensor);

esp_err_t
icm20948_set_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t gyro_fs);

esp_err_t
icm20948_get_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t *gyro_fs);

esp_err_t
icm20948_get_gyro_sensitivity(icm20948_handle_t sensor, float *const gyro_sensitivity);

esp_err_t
icm20948_get_raw_gyro(icm20948_handle_t sensor, icm20948_raw_gyro_value_t *const raw_gyro_value);

esp_err_t
icm20948_get_gyro(icm20948_handle_t sensor, icm20948_gyro_value_t *const gyro_value);

esp_err_t
icm20948_set_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t acce_fs);

esp_err_t
icm20948_get_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t *acce_fs);

esp_err_t
icm20948_get_raw_acce(icm20948_handle_t sensor, icm20948_raw_acce_value_t *const raw_acce_value);

esp_err_t
icm20948_get_acce_sensitivity(icm20948_handle_t sensor, float *const acce_sensitivity);

esp_err_t
icm20948_get_acce(icm20948_handle_t sensor, icm20948_acce_value_t *const acce_value);

esp_err_t
icm20948_set_acce_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_acce);

esp_err_t
icm20948_set_gyro_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_gyro);

esp_err_t
icm20948_enable_dlpf(icm20948_handle_t sensor, bool enable);


esp_err_t
icm20948_sleep(icm20948_handle_t sensor);
esp_err_t calibrate_gyro(icm20948_handle_t sensor, icm20948_gyro_value_t* bias);
esp_err_t calibrate_acce(icm20948_handle_t sensor, icm20948_acce_value_t* bias);

icm20948_handle_t* my_icm20948_init();
#endif