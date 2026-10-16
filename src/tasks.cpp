#include "tasks.h"
#include "rtos_objects.h"
#include "logic_engine.h"
#include <stdio.h>

void vSensorTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(2000); // 2000 ms periodic delay
    SensorData data;
    char logBuffer[80];

    for (;;) {
        // Block until exactly 2000 ms have elapsed since the last period
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        // This runs the moment the delay expires:
        snprintf(logBuffer, sizeof(logBuffer), 
                 "[SensorTask] Unblocked! Current Tick: %lu ms (Delay: 2000 ms)", 
                 (unsigned long)xTaskGetTickCount());
        safePrint(logBuffer);

        data.temperature = 25.4f;
        data.humidity = 61.2f;
        data.lightLevel = 75;
        data.motionDetected = (xEventGroupGetBits(xSystemEventGroup) & EVENT_MOTION_BIT) != 0;

        xQueueOverwrite(xSensorQueueDisplay, &data);
        xQueueOverwrite(xSensorQueueAlarm, &data);
    }
}