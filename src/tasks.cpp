#include "tasks.h"
#include "rtos_objects.h"
#include "logic_engine.h"
#include <stdio.h>

void vSensorTask(void* pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(2000);
    SensorData data;

    for (;;) {
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
// vTaskDelayUntil(&xLastWakeTime, xPeriod);
        data.temperature = 25.4f; 
        data.humidity = 61.2f;
        data.lightLevel = 75;
        data.motionDetected = (xEventGroupGetBits(xSystemEventGroup) & EVENT_MOTION_BIT) != 0;

        safePrint("[SensorTask] New sample acquired.");
        xQueueOverwrite(xSensorQueueDisplay, &data);
        xQueueOverwrite(xSensorQueueAlarm, &data);
    }
}

void vDisplayTask(void* pvParameters) {
    SensorData currentData = {0.0f, 0.0f, 0, false};
    DisplayMode currentMode = DisplayMode::TEMPERATURE;
    char buffer[64];

    for (;;) {
        xEventGroupWaitBits(
            xSystemEventGroup,
            EVENT_ACTIVE_BIT,
            pdFALSE,
            pdTRUE,
            portMAX_DELAY
        );

        if (xQueueReceive(xSensorQueueDisplay, &currentData, pdMS_TO_TICKS(200)) == pdPASS) {
            snprintf(buffer, sizeof(buffer), "[OLED] Mode: %d | Temp: %.1f C | Hum: %.1f %%", 
                     static_cast<int>(currentMode), currentData.temperature, currentData.humidity);
            safePrint(buffer);
        }
    }
}

void vInputTask(void* pvParameters) {
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void vMotionTask(void* pvParameters) {
    TickType_t lastMotionTick = xTaskGetTickCount();

    for (;;) {
        bool motion = false;

        if (motion) {
            lastMotionTick = xTaskGetTickCount();
            xEventGroupSetBits(xSystemEventGroup, EVENT_ACTIVE_BIT | EVENT_MOTION_BIT);
            safePrint("[MotionTask] Motion Detected -> Active.");
        } else {
            xEventGroupClearBits(xSystemEventGroup, EVENT_MOTION_BIT);
            if ((xTaskGetTickCount() - lastMotionTick) > pdMS_TO_TICKS(INACTIVITY_TIMEOUT_TICKS)) {
                xEventGroupClearBits(xSystemEventGroup, EVENT_ACTIVE_BIT);
                safePrint("[MotionTask] Inactivity timeout -> Inactive.");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vAlarmTask(void* pvParameters) {
    SensorData data;

    for (;;) {
        if (xQueueReceive(xSensorQueueAlarm, &data, portMAX_DELAY) == pdPASS) {
            AlarmState state = evaluateTemperature(data.temperature);
            if (state != AlarmState::NORMAL) {
                xEventGroupSetBits(xSystemEventGroup, EVENT_ALARM_BIT);
                safePrint("[AlarmTask] ALARM TRIGGERED! Out of range.");
            } else {
                xEventGroupClearBits(xSystemEventGroup, EVENT_ALARM_BIT);
            }
        }
    }
}