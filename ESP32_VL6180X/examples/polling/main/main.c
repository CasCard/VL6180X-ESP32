#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <nvs_flash.h>

#include "VL6180X.h"

/* config */
#define I2C_PORT I2C_NUM_0
#define GPIO_NUM_21 21
#define GPIO_NUM_22 22
#define FREQ_HZ 400000


#include "app_log.h"


void app_main() {
  /* Boot Message */
  logi;
  printf("VL6180X\n");

  /* NVS flash initialization */
  nvs_flash_init();

  /* initialization */
  VL6180X vl;
  vl.i2c_port = I2C_PORT;
  VL6180X_i2cMasterInit(&vl, GPIO_NUM_21, GPIO_NUM_22, FREQ_HZ);
  if (!VL6180X_init(&vl)) {
    loge;
    printf("Failed to initialize VL6180X\n");
    return;
  }


  /* Main Loop */
  /* Main Loop */
  while (1) {
    /* Measurement */
    uint16_t result_mm = 0;
    TickType_t tick_start = xTaskGetTickCount();
    bool res = VL6180X_read(&vl, &result_mm);
    TickType_t tick_end = xTaskGetTickCount();
    int took_ms = pdTICKS_TO_MS((int)tick_end - tick_start);
    if (res) {
      logi;
      printf("Range: %d [mm] took %d [ms]\n", result_mm, took_ms);
    } else {
      loge;
      printf("Failed to measure :(\n");
    }
  }

  vTaskDelay(portMAX_DELAY);
}
