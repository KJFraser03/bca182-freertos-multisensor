#include "logic_engine.h"

AlarmState evaluateTemperature(float temperature) {
    if (temperature < TEMP_LOW_THRESHOLD) {
        return AlarmState::LOW_TEMPERATURE;
    } else if (temperature > TEMP_HIGH_THRESHOLD) {
        return AlarmState::HIGH_TEMPERATURE;
    }
    return AlarmState::NORMAL;
}

DisplayMode nextDisplayMode(DisplayMode current) {
    int next = static_cast<int>(current) + 1;
    if (next >= static_cast<int>(DisplayMode::COUNT)) {
        return DisplayMode::TEMPERATURE;
    }
    return static_cast<DisplayMode>(next);
}

DisplayMode previousDisplayMode(DisplayMode current) {
    int prev = static_cast<int>(current) - 1;
    if (prev < 0) {
        return DisplayMode::MOTION;
    }
    return static_cast<DisplayMode>(prev);
}

SystemState evaluateSystemState(SystemState current, bool motionDetected, uint32_t inactiveDurationMs, uint32_t timeoutLimitMs) {
    if (motionDetected) {
        return SystemState::ACTIVE;
    }
    if (current == SystemState::ACTIVE && inactiveDurationMs >= timeoutLimitMs) {
        return SystemState::INACTIVE;
    }
    return current;
}