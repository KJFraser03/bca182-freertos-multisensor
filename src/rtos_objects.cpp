#include "rtos_objects.h"
#include <stdio.h>

QueueHandle_t xSensorQueueDisplay = nullptr;
QueueHandle_t xSensorQueueAlarm = nullptr;
SemaphoreHandle_t xSerialMutex = nullptr;
EventGroupHandle_t xSystemEventGroup = nullptr;

void initRtosObjects(void) {
    xSensorQueueDisplay = xQueueCreate(2, sizeof(SensorData));
    xSensorQueueAlarm   = xQueueCreate(2, sizeof(SensorData));
    xSerialMutex        = xSemaphoreCreateMutex();
    xSystemEventGroup   = xEventGroupCreate();
    
    xEventGroupSetBits(xSystemEventGroup, EVENT_ACTIVE_BIT);
}

void safePrint(const char* msg) {
    if (xSerialMutex != nullptr) {
        if (xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
            printf("%s\r\n", msg);
            xSemaphoreGive(xSerialMutex);
        }
    } else {
        printf("%s\r\n", msg);
    }
}