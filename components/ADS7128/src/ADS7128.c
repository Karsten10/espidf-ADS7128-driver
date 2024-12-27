#include "ADS7128.h"

#include "esp_log.h"
#include "driver/i2c_master.h"

static const char *TAG = "ADS7128_Driver";

// The registers of the PCA9555, for more information please refer to section 6.2 of the datasheet
//                   REGISTERS              READ / WRITE
ADS7128_reg_t REG_SYS_STATUS = 0x00;        // READ / WRITE
ADS7128_reg_t REG_GENERAL_CFG = 0x01;       // READ / WRITE

ADS7128_reg_t REG_DATA_CFG = 0x02;          // READ / WRITE
ADS7128_reg_t REG_OSR_CFG = 0x03;           // READ / WRITE

ADS7128_reg_t REG_OPMODE_CFG = 0x04;        // READ / WRITE
ADS7128_reg_t REG_PIN_CFG = 0x05;           // READ / WRITE

ADS7128_reg_t REG_GPIO_CFG = 0x06;          // READ / WRITE
ADS7128_reg_t REG_GPIO_DRIVE_CFG = 0x07;	// READ / WRITE
/**
 * Reads a register of the PCA9555.
 * @param i2c_dev_handle The i2c device handle to write the settings of the ADS7128 to.
 * @param reg The register of the PCA9555 to read.
 */
uint8_t ADS7128_read_register(i2c_master_dev_handle_t i2c_dev_handle, ADS7128_reg_t reg) {
	uint8_t i2c_request_reg[1] = {reg};
	uint8_t reg_sett;

	// Requesting the settings of the PCA9555 to confirm if the settings have been set correctly
	ESP_ERROR_CHECK(i2c_master_transmit_receive(i2c_dev_handle, i2c_request_reg, 1, &reg_sett, sizeof(reg), -1) );

	return reg_sett;
}

/**
 * Checks if the setting requested to the PCA9555 has been set successfully.
 * @param i2c_dev_handle The i2c device handle to write the settings of the ADS7128 to.
 * @param reg The register of the PCA9555 to read.
 * @param requested_settings The desired settings for the register in the PCA9555.
 * @returns True on successful, false on unsuccessful.
 */
bool ADS7128_check_loaded(i2c_master_dev_handle_t i2c_dev_handle, ADS7128_reg_t reg, uint8_t requested_settings) {
	// Requesting the settings of the PCA9555 to confirm if the settings have been set correctly
	uint8_t loaded_settings = ADS7128_read_register(i2c_dev_handle, reg);
	if( loaded_settings == requested_settings ) {
		ESP_LOGI(TAG, "PCA9555 settings loaded successfully!");
		return true;
	} else {
		ESP_LOGE(TAG, "PCA9555 settings have not been loaded successfully, set to 0x%X instead of 0x%X. Check the I2C connection to make sure it is connected properly!", loaded_settings, requested_settings);
		return false;
	}
}
