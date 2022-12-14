#include <unity.h>
#include "color-distance-tracker.hpp"
#include "utils.h"
void setUp(void)
{
    colortracker::init();
}

void tearDown(void)
{
}

void test_tracker_exists(void)
{
    auto sense = colortracker::senses[1];
    TEST_ASSERT_EQUAL(1, sense.id);
}

void test_tracker_sees_device(void)
{
    colortracker::detect({.id = 1,
                          .rssi = -55,
                          .is_empty = false});
    colortracker::update();
    auto sense = colortracker::senses[1];
    TEST_ASSERT_FALSE(sense.is_empty);
}

void test_tracker_does_not_see_device(void)
{
    colortracker::detect({.id = 1,
                          .rssi = -55,
                          .is_empty = false});
    colortracker::update();
    auto sense = colortracker::senses[0];
    TEST_ASSERT_TRUE(sense.is_empty);
}

void test_detect_rssi_to_strength(void)
{
    colortracker::detect({.id = 1,
                          .rssi = -55,
                          .is_empty = false});
    colortracker::detect({.id = 2,
                          .rssi = -80,
                          .is_empty = false});
    colortracker::update();
    TEST_ASSERT_GREATER_THAN(colortracker::senses[1].strength, colortracker::senses[2].strength);
}

// void test_distance_to_strength(void)
// {
//     auto strength = utils::rssi_to_strength(-55);
//     TEST_ASSERT_GREATER_THAN(999,strength);
// }

void test_smaller_rssi_is_larger_distance(void)
{
    auto d1 = utils::rssi_to_distance(-55);
    auto d2 = utils::rssi_to_distance(-80);
    TEST_ASSERT_GREATER_THAN(d1, d2);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_tracker_exists);
    RUN_TEST(test_tracker_sees_device);
    RUN_TEST(test_tracker_does_not_see_device);
    RUN_TEST(test_detect_rssi_to_strength);
    RUN_TEST(test_smaller_rssi_is_larger_distance);
    // RUN_TEST(test_distance_to_strength);
    UNITY_END(); // stop unit testing
}

int main()
{
    setup();
    return 0;
}
void loop()
{
}
