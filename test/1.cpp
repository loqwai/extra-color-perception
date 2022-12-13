#include <unity.h>
#include "friend.h"
#include <string>
// include standard C++ map
#include <map>
std::map<std::string, Friend>* deviceMap;
void setUp(void) {
    // set stuff up here
    deviceMap = new std::map<std::string, Friend>();
}

void tearDown(void) {
    // clean stuff up here
    deviceMap->clear();
}

void test_string_concat(void) {
    TEST_ASSERT_EQUAL_INT(0, deviceMap->size());
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_string_concat);
    UNITY_END(); // stop unit testing
}

int main()
{
    setup();
}

void loop(){
    main();
}
