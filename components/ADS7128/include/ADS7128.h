#ifndef ADS7128_H
#define ADS7128_H

#include "driver/i2c_master.h"
#include <stdint.h>

typedef union {
    struct {
        uint8_t b7:1;
        uint8_t b6:1;
        uint8_t b5:1;
        uint8_t b4:1;
        uint8_t b3:1;
        uint8_t b2:1;
        uint8_t b1:1;
        uint8_t b0:1;
    } reg __attribute__((packed));
    uint8_t unsigned_val;           // Access as packed uint8_t
} port_config_t;

typedef const uint8_t ADS7128_reg_t;

//                   REGISTERS              READ / WRITE
extern ADS7128_reg_t REG_SYS_STATUS;        // READ / WRITE
extern ADS7128_reg_t REG_GENERAL_CFG;       // READ / WRITE

extern ADS7128_reg_t REG_DATA_CFG;          // READ / WRITE
extern ADS7128_reg_t REG_OSR_CFG;           // READ / WRITE

extern ADS7128_reg_t REG_OPMODE_CFG;        // READ / WRITE
extern ADS7128_reg_t REG_PIN_CFG;           // READ / WRITE

extern ADS7128_reg_t REG_GPIO_CFG;          // READ / WRITE
extern ADS7128_reg_t REG_GPIO_DRIVE_CFG;    // READ / WRITE

bool ADS7128_check_loaded(i2c_master_dev_handle_t i2c_dev_handle, ADS7128_reg_t reg, uint8_t requested_settings);
uint8_t ADS7128_read_register(i2c_master_dev_handle_t i2c_dev_handle, ADS7128_reg_t reg);

#endif