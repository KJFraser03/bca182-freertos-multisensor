#pragma once
#include "app_types.h"

#ifdef __cplusplus
extern "C" {
#endif

AlarmState evaluateTemperature(float temperature);
DisplayMode nextDisplayMode(DisplayMode current);
DisplayMode previousDisplayMode(DisplayMode current);
SystemState evaluateSystemState(SystemState current, bool motionDetected, uint32_t inactiveDurationMs, uint32_t timeoutLimitMs);

#ifdef __cplusplus
}
#endif