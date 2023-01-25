#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#if 1
#define logd                                                                   \
  (printf("[D] %8d [%s:%d] [%s()] ",xTaskGetTickCount() * portTICK_PERIOD_MS, __FILE__, __LINE__, __func__))
#else
#define logd
#endif

#if 1
#define logi                                                                   \
  (printf("[I] %8d [%s:%d] [%s()] ",xTaskGetTickCount() * portTICK_PERIOD_MS, __FILE__, __LINE__, __func__))
#else
#define logi
#endif

#if 1
#define logw                                                                   \
  (printf("[W] %8d [%s:%d] [%s()] ",xTaskGetTickCount() * portTICK_PERIOD_MS, __FILE__, __LINE__, __func__))
#else
#define logw
#endif

#if 1
#define loge                                                                   \
  (printf("[E] %8d [%s:%d] [%s()] ",xTaskGetTickCount() * portTICK_PERIOD_MS, __FILE__, __LINE__, __func__))
#else
#define loge
#endif
