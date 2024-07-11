
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include <sys/time.h>
#include "icm20948.h"


static const char *TAG = "icm20948";

 esp_err_t
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

 esp_err_t
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
esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master ={I2C_MASTER_FREQ_HZ} ,
    };

    i2c_param_config((i2c_port_t)i2c_master_port, &conf);

    return i2c_driver_install((i2c_port_t)i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
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
	*gyro_fs = (icm20948_gyro_fs_t)tmp;
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

	gyro_value->gyro_x = raw_gyro.raw_gyro_x / (float)gyro_sensitivity;
	gyro_value->gyro_y = raw_gyro.raw_gyro_y / (float)gyro_sensitivity;
	gyro_value->gyro_z = raw_gyro.raw_gyro_z / (float)gyro_sensitivity;
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
	*acce_fs = (icm20948_acce_fs_t)tmp;
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

	acce_value->acce_x = raw_acce.raw_acce_x / (float)acce_sensitivity;
	acce_value->acce_y = raw_acce.raw_acce_y / (float)acce_sensitivity;
	acce_value->acce_z = raw_acce.raw_acce_z / (float)acce_sensitivity;
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
		
		while(!(int_status&0x01)){
			ESP_ERROR_CHECK(icm20948_read(sensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
		}
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
		while(!(int_status&0x01)){
			ESP_ERROR_CHECK(icm20948_read(sensor,ICM20948_INT_STATUS_1,&int_status,sizeof(int_status)));
		}
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
icm20948_handle_t* my_icm20948_init(){
    uint8_t data[2];
    /*I2C and icm20948 setting start*/
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    //select bank
    icm20948_handle_t* sensor = icm20948_create(I2C_NUM_0,ICM20948_SENSOR_ADDR);
    ESP_ERROR_CHECK(icm20948_reset(*sensor));
    ESP_ERROR_CHECK(icm20948_get_deviceid(*sensor,&data[0]));

    ESP_LOGI(TAG,"WHO_AM_I = %X",data[0]);

    

    ESP_ERROR_CHECK(icm20948_wake_up(*sensor));
    ESP_ERROR_CHECK(icm20948_set_acce_dlpf(*sensor,ICM20948_DLPF_0));
    ESP_ERROR_CHECK(icm20948_set_acce_fs(*sensor,ACCE_FS_4G));
    ESP_ERROR_CHECK(icm20948_set_gyro_dlpf(*sensor,ICM20948_DLPF_0));
    ESP_ERROR_CHECK(icm20948_set_gyro_fs(*sensor,GYRO_FS_500DPS));

    /*I2C and icm20948 setting end*/
    return sensor;
}