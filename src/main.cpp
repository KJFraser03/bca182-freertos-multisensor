#include "stm32f1xx_hal.h"
#include "rtos_objects.h"
#include "tasks.h"

void SystemClock_Config(void) {}

static void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    initRtosObjects();

    safePrint("BCA182 FreeRTOS Multisensor");
    safePrint("System starting...");

    // Standard task priority design:
    xTaskCreate(vMotionTask,  "MotionTask",  configMINIMAL_STACK_SIZE + 64,  nullptr, 3, nullptr);
    xTaskCreate(vInputTask,   "InputTask",   configMINIMAL_STACK_SIZE + 64,  nullptr, 3, nullptr);
    xTaskCreate(vSensorTask,  "SensorTask",  configMINIMAL_STACK_SIZE + 128, nullptr, 2, nullptr);
    xTaskCreate(vAlarmTask,   "AlarmTask",   configMINIMAL_STACK_SIZE + 64,  nullptr, 2, nullptr);
    xTaskCreate(vDisplayTask, "DisplayTask", configMINIMAL_STACK_SIZE + 128, nullptr, 1, nullptr);

    vTaskStartScheduler();

    while (1) {}
}