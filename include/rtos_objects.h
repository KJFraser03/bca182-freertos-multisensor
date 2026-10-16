#pragma once
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "app_types.h"

extern QueueHandle_t xSensorQueueDisplay;
extern QueueHandle_t xSensorQueueAlarm;
extern SemaphoreHandle_t xSerialMutex;
extern EventGroupHandle_t xSystemEventGroup;

void initRtosObjects(void);
void safePrint(const char* msg);