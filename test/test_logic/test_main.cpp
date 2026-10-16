#include <unity.h>
#include "../../src/logic_engine.cpp"

void setUp(void) {}
void tearDown(void) {}

void test_temp_below_lower_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::LOW_TEMPERATURE, evaluateTemperature(17.9f));
}

void test_temp_exactly_lower_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::NORMAL, evaluateTemperature(18.0f));
}

void test_temp_normal_range(void) {
    TEST_ASSERT_EQUAL(AlarmState::NORMAL, evaluateTemperature(24.5f));
}

void test_temp_exactly_upper_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::NORMAL, evaluateTemperature(30.0f));
}

void test_temp_above_upper_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::HIGH_TEMPERATURE, evaluateTemperature(30.1f));
}

void test_display_next_normal(void) {
    TEST_ASSERT_EQUAL(DisplayMode::HUMIDITY, nextDisplayMode(DisplayMode::TEMPERATURE));
}

void test_display_next_wraparound(void) {
    TEST_ASSERT_EQUAL(DisplayMode::TEMPERATURE, nextDisplayMode(DisplayMode::MOTION));
}

void test_display_prev_normal(void) {
    TEST_ASSERT_EQUAL(DisplayMode::LIGHT, previousDisplayMode(DisplayMode::MOTION));
}

void test_display_prev_wraparound(void) {
    TEST_ASSERT_EQUAL(DisplayMode::MOTION, previousDisplayMode(DisplayMode::TEMPERATURE));
}

void test_state_active_no_timeout(void) {
    TEST_ASSERT_EQUAL(SystemState::ACTIVE, evaluateSystemState(SystemState::ACTIVE, false, 5000, 15000));
}

void test_state_active_timeout_reached(void) {
    TEST_ASSERT_EQUAL(SystemState::INACTIVE, evaluateSystemState(SystemState::ACTIVE, false, 15000, 15000));
}

void test_state_inactive_remains_inactive(void) {
    TEST_ASSERT_EQUAL(SystemState::INACTIVE, evaluateSystemState(SystemState::INACTIVE, false, 20000, 15000));
}

void test_state_inactive_motion_reactivates(void) {
    TEST_ASSERT_EQUAL(SystemState::ACTIVE, evaluateSystemState(SystemState::INACTIVE, true, 20000, 15000));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_temp_below_lower_threshold);
    RUN_TEST(test_temp_exactly_lower_threshold);
    RUN_TEST(test_temp_normal_range);
    RUN_TEST(test_temp_exactly_upper_threshold);
    RUN_TEST(test_temp_above_upper_threshold);
    RUN_TEST(test_display_next_normal);
    RUN_TEST(test_display_next_wraparound);
    RUN_TEST(test_display_prev_normal);
    RUN_TEST(test_display_prev_wraparound);
    RUN_TEST(test_state_active_no_timeout);
    RUN_TEST(test_state_active_timeout_reached);
    RUN_TEST(test_state_inactive_remains_inactive);
    RUN_TEST(test_state_inactive_motion_reactivates);
    return UNITY_END();
}