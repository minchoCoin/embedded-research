#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include <sys/time.h>
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

typedef struct {
	i2c_port_t bus;
	gpio_num_t int_pin;
	uint16_t dev_addr;
	uint32_t counter;
	float dt; /*!< delay time between two measurements, dt should be small (ms level) */
	struct timeval *timer;
} icm20948_handle_t;

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

static esp_err_t
icm20948_write(icm20948_handle_t sensor,
               const uint8_t reg_start_addr,
               const uint8_t *const data_buf,
               const uint8_t data_len)
{
	
	esp_err_t ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	ret = i2c_master_start(cmd);
	assert(ESP_OK == ret);
	ret = i2c_master_write_byte(cmd, sensor.dev_addr | I2C_MASTER_WRITE, true);
	assert(ESP_OK == ret);
	ret = i2c_master_write_byte(cmd, reg_start_addr, true);
	assert(ESP_OK == ret);
	ret = i2c_master_write(cmd, data_buf, data_len, true);
	assert(ESP_OK == ret);
	ret = i2c_master_stop(cmd);
	assert(ESP_OK == ret);
	ret = i2c_master_cmd_begin(sensor.bus, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);

	return ret;
}

static esp_err_t
icm20948_read(icm20948_handle_t sensor, const uint8_t reg_start_addr, uint8_t *const data_buf, const uint8_t data_len)
{
	
	esp_err_t ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	ret = i2c_master_start(cmd);
	assert(ESP_OK == ret);
	ret = i2c_master_write_byte(cmd, sensor.dev_addr | I2C_MASTER_WRITE, true);
	assert(ESP_OK == ret);
	ret = i2c_master_write_byte(cmd, reg_start_addr, true);
	assert(ESP_OK == ret);
	ret = i2c_master_start(cmd);
	assert(ESP_OK == ret);
	ret = i2c_master_write_byte(cmd, sensor.dev_addr | I2C_MASTER_READ, true);
	assert(ESP_OK == ret);
	ret = i2c_master_read(cmd, data_buf, data_len, I2C_MASTER_LAST_NACK);
	assert(ESP_OK == ret);
	ret = i2c_master_stop(cmd);
	assert(ESP_OK == ret);
	ret = i2c_master_cmd_begin(sensor.bus, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);

	return ret;
}

icm20948_handle_t*
icm20948_create(i2c_port_t port, const uint16_t dev_addr)
{
	
	icm20948_handle_t *sensor = (icm20948_handle_t *)calloc(1, sizeof(icm20948_handle_t));
	sensor->bus = port;
	sensor->dev_addr = dev_addr << 1;
	sensor->counter = 0;
	sensor->dt = 0;
	sensor->timer = (struct timeval *)calloc(1, sizeof(struct timeval));
	return sensor;
}
void
icm20948_delete(icm20948_handle_t* sensor)
{
	
	free(sensor);
}
/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t
icm20948_set_bank(icm20948_handle_t sensor, uint8_t bank)
{
	esp_err_t ret;
	if (bank > 3)
		return ESP_FAIL;
	bank = (bank << 4) & 0x30;
	ret = icm20948_write(sensor, ICM20948_REG_BANK_SEL, &bank, 1);
	return ret;
}


esp_err_t
icm20948_reset(icm20948_handle_t sensor)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_read(sensor, ICM20948_PWR_MGMT_1, &tmp, RESET_BIT);
	if (ret != ESP_OK)
		return ret;
	tmp |= 0x80;
	ret = icm20948_write(sensor, ICM20948_PWR_MGMT_1, &tmp, RESET_BIT);
	if (ret != ESP_OK)
		return ret;

	return ret;
}

esp_err_t
icm20948_get_deviceid(icm20948_handle_t sensor, uint8_t *const deviceid)
{
	return icm20948_read(sensor, ICM20948_WHO_AM_I_REG_ADDR, deviceid, 1);
}
 esp_err_t
icm20948_wake_up(icm20948_handle_t sensor)
{
	esp_err_t ret;
	uint8_t tmp;
	ret = icm20948_read(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	if (ESP_OK != ret) {
		return ret;
	}
	tmp &= (~0x40);
	ret = icm20948_write(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	return ret;
}

esp_err_t
icm20948_set_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t gyro_fs)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ret;

	ret = icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);

#if CONFIG_LOG_DEFAULT_LEVEL == 4
	printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(tmp));
#endif

	if (ret != ESP_OK)
		return ret;
	tmp &= 0x09;
	tmp |= (gyro_fs << 1);

#if CONFIG_LOG_DEFAULT_LEVEL == 4
	printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(tmp));
#endif

	ret = icm20948_write(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	return ret;
}

esp_err_t
icm20948_get_gyro_fs(icm20948_handle_t sensor, icm20948_gyro_fs_t *gyro_fs)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ret;

	ret = icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);

#if CONFIG_LOG_DEFAULT_LEVEL == 4
	printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(tmp));
#endif

	tmp &= 0x06;
	tmp >>= 1;
	*gyro_fs = tmp;
	return ret;
}

esp_err_t
icm20948_get_gyro_sensitivity(icm20948_handle_t sensor, float *const gyro_sensitivity)
{
	esp_err_t ret;
	icm20948_gyro_fs_t gyro_fs;
	ret = icm20948_get_gyro_fs(sensor, &gyro_fs);
	if (ret != ESP_OK)
		return ret;

	switch (gyro_fs) {
	case GYRO_FS_250DPS:
		*gyro_sensitivity = 131;
		break;

	case GYRO_FS_500DPS:
		*gyro_sensitivity = 65.5;
		break;

	case GYRO_FS_1000DPS:
		*gyro_sensitivity = 32.8;
		break;

	case GYRO_FS_2000DPS:
		*gyro_sensitivity = 16.4;
		break;

	default:
		break;
	}
	return ret;
}

esp_err_t
icm20948_get_raw_gyro(icm20948_handle_t sensor, icm20948_raw_gyro_value_t *const raw_gyro_value)
{
	uint8_t data_rd[6];
	esp_err_t ret = icm20948_read(sensor, ICM20948_GYRO_XOUT_H, data_rd, sizeof(data_rd));

	raw_gyro_value->raw_gyro_x = (int16_t)((data_rd[0] << 8) + (data_rd[1]));
	raw_gyro_value->raw_gyro_y = (int16_t)((data_rd[2] << 8) + (data_rd[3]));
	raw_gyro_value->raw_gyro_z = (int16_t)((data_rd[4] << 8) + (data_rd[5]));

	return ret;
}

esp_err_t
icm20948_get_gyro(icm20948_handle_t sensor, icm20948_gyro_value_t *const gyro_value)
{
	esp_err_t ret;
	float gyro_sensitivity;
	icm20948_raw_gyro_value_t raw_gyro;

	ret = icm20948_get_gyro_sensitivity(sensor, &gyro_sensitivity);
	if (ret != ESP_OK) {
		return ret;
	}

	ret = icm20948_set_bank(sensor, 0);
	if (ret != ESP_OK) {
		return ret;
	}

	ret = icm20948_get_raw_gyro(sensor, &raw_gyro);
	if (ret != ESP_OK) {
		return ret;
	}

	gyro_value->gyro_x = raw_gyro.raw_gyro_x / gyro_sensitivity;
	gyro_value->gyro_y = raw_gyro.raw_gyro_y / gyro_sensitivity;
	gyro_value->gyro_z = raw_gyro.raw_gyro_z / gyro_sensitivity;
	return ESP_OK;
}

esp_err_t
icm20948_set_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t acce_fs)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ret;

	ret = icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);

#if CONFIG_LOG_DEFAULT_LEVEL == 4
	printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(tmp));
#endif

	if (ret != ESP_OK)
		return ret;
	tmp &= 0x09;
	tmp |= (acce_fs << 1);

#if CONFIG_LOG_DEFAULT_LEVEL == 4
	printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(tmp));
#endif

	ret = icm20948_write(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	return ret;
}

esp_err_t
icm20948_get_acce_fs(icm20948_handle_t sensor, icm20948_acce_fs_t *acce_fs)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ret;

	ret = icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);

#if CONFIG_LOG_DEFAULT_LEVEL == 4
	printf(BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(tmp));
#endif

	tmp &= 0x06;
	tmp >>= 1;
	*acce_fs = tmp;
	return ret;
}

esp_err_t
icm20948_get_raw_acce(icm20948_handle_t sensor, icm20948_raw_acce_value_t *const raw_acce_value)
{
	uint8_t data_rd[6];
	esp_err_t ret = icm20948_read(sensor, ICM20948_ACCEL_XOUT_H, data_rd, sizeof(data_rd));

	raw_acce_value->raw_acce_x = (int16_t)((data_rd[0] << 8) + (data_rd[1]));
	raw_acce_value->raw_acce_y = (int16_t)((data_rd[2] << 8) + (data_rd[3]));
	raw_acce_value->raw_acce_z = (int16_t)((data_rd[4] << 8) + (data_rd[5]));
	return ret;
}

esp_err_t
icm20948_get_acce_sensitivity(icm20948_handle_t sensor, float *const acce_sensitivity)
{
	esp_err_t ret;
	icm20948_acce_fs_t acce_fs;
	ret = icm20948_get_acce_fs(sensor, &acce_fs);
	switch (acce_fs) {
	case ACCE_FS_2G:
		*acce_sensitivity = 16384;
		break;

	case ACCE_FS_4G:
		*acce_sensitivity = 8192;
		break;

	case ACCE_FS_8G:
		*acce_sensitivity = 4096;
		break;

	case ACCE_FS_16G:
		*acce_sensitivity = 2048;
		break;

	default:
		break;
	}
	return ret;
}

esp_err_t
icm20948_get_acce(icm20948_handle_t sensor, icm20948_acce_value_t *const acce_value)
{
	esp_err_t ret;
	float acce_sensitivity;
	icm20948_raw_acce_value_t raw_acce;

	ret = icm20948_get_acce_sensitivity(sensor, &acce_sensitivity);
	if (ret != ESP_OK) {
		return ret;
	}

	ret = icm20948_set_bank(sensor, 0);
	if (ret != ESP_OK)
		return ret;

	ret = icm20948_get_raw_acce(sensor, &raw_acce);
	if (ret != ESP_OK) {
		return ret;
	}

	acce_value->acce_x = raw_acce.raw_acce_x / acce_sensitivity;
	acce_value->acce_y = raw_acce.raw_acce_y / acce_sensitivity;
	acce_value->acce_z = raw_acce.raw_acce_z / acce_sensitivity;
	return ESP_OK;
}

esp_err_t
icm20948_set_acce_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_acce)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ESP_FAIL;

	ret = icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	tmp &= 0xC7;
	tmp |= dlpf_acce << 3;

	ret = icm20948_write(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	return ret;
}

esp_err_t
icm20948_set_gyro_dlpf(icm20948_handle_t sensor, icm20948_dlpf_t dlpf_gyro)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ESP_FAIL;

	ret = icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	tmp &= 0xC7;
	tmp |= dlpf_gyro << 3;

	ret = icm20948_write(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	return ret;
}

esp_err_t
icm20948_enable_dlpf(icm20948_handle_t sensor, bool enable)
{
	esp_err_t ret;
	uint8_t tmp;

	ret = icm20948_set_bank(sensor, 2);
	if (ret != ESP_OK)
		return ESP_FAIL;

	ret = icm20948_read(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	if (enable)
		tmp |= 0x01;
	else
		tmp &= 0xFE;

	ret = icm20948_write(sensor, ICM20948_ACCEL_CONFIG, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	ret = icm20948_read(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	if (enable)
		tmp |= 0x01;
	else
		tmp &= 0xFE;

	ret = icm20948_write(sensor, ICM20948_GYRO_CONFIG_1, &tmp, 1);
	if (ret != ESP_OK)
		return ESP_FAIL;

	return ret;
}


esp_err_t
icm20948_sleep(icm20948_handle_t sensor)
{
	esp_err_t ret;
	uint8_t tmp;
	ret = icm20948_read(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	if (ESP_OK != ret) {
		return ret;
	}
	tmp |= 0x40;
	ret = icm20948_write(sensor, ICM20948_PWR_MGMT_1, &tmp, 1);
	return ret;
}

esp_err_t calibrate_gyro(icm20948_handle_t sensor, icm20948_gyro_value_t* bias)
{
	esp_err_t ret=ESP_OK;
	static uint8_t int_status=0x00;
    float x_sum=0.0;
    float y_sum=0.0;
    float z_sum=0.0;
	ESP_ERROR_CHECK(icm20948_set_bank(sensor,0));
	icm20948_gyro_value_t tmp={0.0,0.0,0.0};

	for(int i=0;i<NUM_SAMPLE;i++){
		ESP_ERROR_CHECK(icm20948_read(sensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
		while(!(int_status&0x01));
		ret = icm20948_get_gyro(sensor,&tmp);
		if(ret!=ESP_OK) return ret;

		x_sum += tmp.gyro_x;
		y_sum +=tmp.gyro_y;
		z_sum +=tmp.gyro_z;
		int_status = 0x00;
		ESP_ERROR_CHECK(icm20948_write(sensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
	}
	bias->gyro_x = x_sum / NUM_SAMPLE;
	bias->gyro_y=y_sum/NUM_SAMPLE;
	bias->gyro_z=z_sum/NUM_SAMPLE;

	return ret;
    
}

esp_err_t calibrate_acce(icm20948_handle_t sensor, icm20948_acce_value_t* bias)
{
	esp_err_t ret=ESP_OK;
	static uint8_t int_status=0x00;
    float x_sum=0.0;
    float y_sum=0.0;
    float z_sum=0.0;

	icm20948_acce_value_t tmp={0.0,0.0,0.0};

	for(int i=0;i<NUM_SAMPLE;i++){
		ESP_ERROR_CHECK(icm20948_read(sensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
		while(!(int_status&0x01));
		ret = icm20948_get_acce(sensor,&tmp);
		if(ret!=ESP_OK) return ret;

		x_sum += tmp.acce_x;
		y_sum +=tmp.acce_y;
		z_sum +=tmp.acce_z;
		int_status = 0x00;
		ESP_ERROR_CHECK(icm20948_write(sensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
	}
	bias->acce_x = x_sum / NUM_SAMPLE;
	bias->acce_y=y_sum/NUM_SAMPLE;
	bias->acce_z=z_sum/NUM_SAMPLE;

	return ret;
    
}
