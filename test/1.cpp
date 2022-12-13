#include <unity.h>
#include "friend.h"
#include <string>
std::string STR_TO_TEST;

void setUp(void) {
    // set stuff up here
    STR_TO_TEST = "Hello, world!";
}

void tearDown(void) {
    // clean stuff up here
    STR_TO_TEST = "";
}

void test_string_concat(void) {

}

void test_string_substring(void) {
    TEST_ASSERT_EQUAL_STRING("Hello", STR_TO_TEST.c_str());
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_string_concat);
    RUN_TEST(test_string_substring);

    UNITY_END(); // stop unit testing
}

int main()
{
    setup();
}

void loop(){
    main();
}
