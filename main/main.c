#include <esp_log.h>
#include <stdint.h>
#include <stdio.h>

#include <ADS7128.h>

static const char *TAG = "main";

#define IIC_SCL	0
#define IIC_SDA	1

// Defining the settings for the i2c handle
i2c_master_bus_config_t i2c_mst_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = I2C_NUM_0,
    .scl_io_num = IIC_SCL,
    .sda_io_num = IIC_SDA,
    .glitch_ignore_cnt = 7
};
i2c_device_config_t i2c_ads7128_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = 0x17,
    .scl_speed_hz = 100000,
};

// Prints the given unsigned integer (16-bit) bit by bit. Source: overleaf
void print_uint8_t(port_config_t num)
{
	for (int bit = 0; bit < (sizeof(uint8_t) * 8); bit++)
	{
		printf("%i", (num & 0b10000000)>0?1:0);
		num = num << 1;
	}
	printf("\n");
}

void app_main()
{
	esp_log_level_set("*", ESP_LOG_DEBUG);
	ESP_LOGI(TAG, "MCU has booted up successfully!");

	// Setting-up the used PCA9555
	port_config_t sys_stat, general_cfg, data_cfg;
	sys_stat.reg.b5 = 0b00;
	print_uint8_t(sys_stat);

	i2c_master_dev_handle_t i2c_dev_handle;
	i2c_master_bus_handle_t bus_handle;

	ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
	ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &i2c_ADS7128_cfg, &i2c_dev_handle));
}
