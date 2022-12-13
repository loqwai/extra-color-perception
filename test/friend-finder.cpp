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
    delete manager;
}

void test_exists(void) {
    TEST_ASSERT_NOT_NULL(manager);
}
void test_returns_friends(void) {
    auto friends = manager->getFriends();
    TEST_ASSERT_NOT_NULL(friends);
}
void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_exists);
    RUN_TEST(test_returns_friends);
    UNITY_END(); // stop unit testing
}

int main()
{
    setup();
}

void loop(){
    main();
}
