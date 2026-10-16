#pragma once
#include <stdint.h>
#include <stdbool.h>

enum class DisplayMode {
    TEMPERATURE = 0,
    HUMIDITY,
    LIGHT,
    MOTION,
    COUNT
};

enum class AlarmState {
    NORMAL = 0,
    LOW_TEMPERATURE,
    HIGH_TEMPERATURE
};

enum class SystemState {
    ACTIVE = 0,
    INACTIVE
};

struct SensorData {
    float temperature;
    float humidity;
    int lightLevel;
    bool motionDetected;
};

// Event Group Bitmask definitions
#define EVENT_ACTIVE_BIT    (1 << 0)
#define EVENT_MOTION_BIT    (1 << 1)
#define EVENT_ALARM_BIT     (1 << 2)

// Temperature thresholds
constexpr float TEMP_LOW_THRESHOLD = 18.0f;
constexpr float TEMP_HIGH_THRESHOLD = 30.0f;
constexpr uint32_t INACTIVITY_TIMEOUT_TICKS = 15000; // 15 seconds