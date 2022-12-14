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


void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_tracker_exists);
    UNITY_END(); // stop unit testing
}

int main(){
    setup();
    return 0;
}
void loop()
{
}