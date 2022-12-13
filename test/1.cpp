#include <unity.h>
#include <string>
#include <map>
#include "friend.h"
FriendManager* manager;
void setUp(void) {
    manager = new FriendManager();
}

void tearDown(void) {
    // clean stuff up here
    manager = NULL;
}

void test_string_concat(void) {
    TEST_ASSERT_NOT_NULL(manager);
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
