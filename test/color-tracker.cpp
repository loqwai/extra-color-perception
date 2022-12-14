#include <unity.h>
#include "color-distance-tracker.hpp"

ColorTracker* tracker;
void setUp(void) {
    // set stuff up here
    tracker = new ColorTracker();
}

void tearDown(void) {
    // clean stuff up here
    delete tracker;
}

void test_string_concat(void) {
    TEST_ASSERT_NOT_NULL(tracker);
}


void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_string_concat);
    UNITY_END(); // stop unit testing
}

int main(){
    setup();
    return 0;
}
void loop()
{
}
