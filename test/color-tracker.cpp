#include <unity.h>
#include "color-distance-tracker.hpp"
void setUp(void) {
    colortracker::init();
}

void tearDown(void) {
}

void test_tracker_exists(void) {
   auto sense = colortracker::senses[1];
   TEST_ASSERT_EQUAL(1, sense.id);
}

void test_tracker_sees_device(void) {
   colortracker::detect({
        .id = 1,
        .rssi = -55,
        .is_empty = false
   });
   colortracker::update();
   auto sense = colortracker::senses[1];
   TEST_ASSERT_FALSE(sense.is_empty);
}

void test_tracker_does_not_see_device(void) {
   colortracker::detect({
        .id = 1,
        .rssi = -55,
        .is_empty = false
   });
   colortracker::update();
   auto sense = colortracker::senses[0];
   TEST_ASSERT_TRUE(sense.is_empty);
}

void test_rssi_to_strength(void) {
   colortracker::detect({
        .id = 1,
        .rssi = -55,
        .is_empty = false
   });
    colortracker::detect({
        .id = 2,
        .rssi = -80,
        .is_empty = false
    });
   colortracker::update();
   TEST_ASSERT_GREATER_THAN(colortracker::senses[1].strength, colortracker::senses[2].strength);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_tracker_exists);
    RUN_TEST(test_tracker_sees_device);
    RUN_TEST(test_tracker_does_not_see_device);
    RUN_TEST(test_rssi_to_strength);
    UNITY_END(); // stop unit testing
}

int main(){
    setup();
    return 0;
}
void loop()
{
}
