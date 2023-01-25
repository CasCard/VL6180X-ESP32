#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "driver/i2c.h"

#include "vl6180x_api.h"
#include "vl6180x_def.h"
#include "vl6180x_platform.h"

#include "esp_log.h"
#define TAG "VL6180X"

#define VL6180x_I2C_ADDRESS_DEFAULT 0x29

typedef struct {
    i2c_port_t i2c_port;
    VL6180xDev_t dev;
    int32_t TimingBudgetMicroSeconds;
} VL6180X;

bool VL6180X_init(VL6180X* vl);
bool VL6180X_read(VL6180X* vl, uint16_t *pRangeMilliMeter);
void VL6180X_i2cMasterInit(VL6180X* vl, gpio_num_t pin_sda, gpio_num_t pin_scl, uint32_t freq);
void VL6180X_destroy(VL6180X* vl);


bool VL6180X_init(VL6180X* vl) {
    /* device init */
    vl->dev->i2c_port_num = vl->i2c_port;
    vl->dev->i2c_address = VL6180x_I2C_ADDRESS_DEFAULT;
    if (VL6180x_InitData(vl->dev) < 0) {
        ESP_LOGE(TAG, "InitData");
        return false;
    }
    if (VL6180x_Prepare(vl->dev) < 0) {
        ESP_LOGE(TAG, "Prepare");
        return false;
    }
    return true;
}



bool VL6180X_read(VL6180X* vl, uint16_t *pRangeMilliMeter) {
    VL6180x_RangeData_t Range;
    int status = VL6180x_RangePollMeasurement(vl->dev, &Range);
    if (status != 0 || Range.errorStatus != 0) {
        ESP_LOGW(TAG, "i2c status: %d, range status: %s", status,
                 VL6180x_RangeGetStatusErrString(Range.errorStatus));
        return false;
    }
    *pRangeMilliMeter = Range.range_mm;
    return true;
}



void VL6180X_i2cMasterInit(VL6180X* vl, gpio_num_t pin_sda, gpio_num_t pin_scl, uint32_t freq) {
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = pin_sda;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = pin_scl;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = freq;
    i2c_param_config(vl->i2c_port, &conf);
    i2c_driver_install(vl->i2c_port, conf.mode, 0, 0, 0);
}



void VL6180X_destroy(VL6180X* vl) {
    i2c_driver_delete(vl->i2c_port);
    free(vl);
}

