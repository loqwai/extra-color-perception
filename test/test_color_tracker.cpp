#include <unity.h>
#include "color_tracker.hpp"
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
    for(int i = 0; i < 5; i++) {
        colortracker::update();
    }
    TEST_ASSERT_GREATER_THAN(colortracker::senses[2].strength, colortracker::senses[1].strength);
}

void test_smaller_rssi_is_larger_distance(void)
{
    auto d1 = utils::rssi_to_distance(-55);
    auto d2 = utils::rssi_to_distance(-80);
    TEST_ASSERT_GREATER_THAN(d1, d2);
}
void test_sense_fades_over_time(void)
{
    colortracker::detect({.id = 1,
                          .rssi = -65,
                          .is_empty = false});
    colortracker::update();
    auto before_strength = colortracker::senses[1].strength;
    for (int i = 0; i < 10; i++)
    {
        colortracker::update();
    }
    auto after_strength = colortracker::senses[1].strength;
    TEST_ASSERT_LESS_THAN(before_strength, after_strength);
}
void test_sense_eventually_reaches_0(void)
{
    colortracker::detect({.id = 1,
                          .rssi = -65,
                          .is_empty = false});

    for (int i = 0; i < 100; i++)
    {
        colortracker::update();
    }
    auto strength = colortracker::senses[1].strength;
    auto device = colortracker::devices[1];
    TEST_ASSERT_TRUE(device.is_empty);
    // TEST_ASSERT_EQUAL(0, strength);
}
void test_sense_close_eventually_reaches_close_to_255(void)
{
    for (int i = 0; i < 100; i++)
    {
        colortracker::detect({.id = 1,
                              .rssi = -70,
                              .is_empty = false});

        colortracker::update();
    }
    auto strength = colortracker::senses[1].strength;
    TEST_ASSERT_FALSE(colortracker::devices[1].is_empty);
    TEST_ASSERT_GREATER_THAN(225, strength);
}
void test_middle_sense_eventually_reaches_close_to_128(void)
{
    for (int i = 0; i < 100; i++)
    {
        colortracker::detect({.id = 1,
                              .rssi = -85,
                              .is_empty = false});

        colortracker::update();
    }
    auto strength = colortracker::senses[1].strength;
    TEST_ASSERT_GREATER_THAN(120, strength);
    TEST_ASSERT_LESS_THAN(200, strength);
}
void test_low_sense_still_above_0(void)
{
    for (int i = 0; i < 100; i++)
    {
        colortracker::detect({.id = 1,
                              .rssi = -95,
                              .is_empty = false});

        colortracker::update();
    }
    auto strength = colortracker::senses[1].strength;
    TEST_ASSERT_GREATER_THAN(0, strength);
    TEST_ASSERT_LESS_THAN(50, strength);
}
void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_tracker_exists);
    RUN_TEST(test_tracker_sees_device);
    RUN_TEST(test_tracker_does_not_see_device);
    RUN_TEST(test_detect_rssi_to_strength);
    RUN_TEST(test_smaller_rssi_is_larger_distance);
    RUN_TEST(test_sense_fades_over_time);
    RUN_TEST(test_sense_eventually_reaches_0);
    RUN_TEST(test_sense_close_eventually_reaches_close_to_255);
    RUN_TEST(test_middle_sense_eventually_reaches_close_to_128);
    RUN_TEST(test_low_sense_still_above_0);
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
