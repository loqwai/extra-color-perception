#include <unity.h>
#include <string>
#include <map>
#include "friend.h"
FriendFinder* manager;
void setUp(void) {
    manager = new FriendFinder();
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
void test_on_friend_found_adds_friend(void) {
    auto friends = manager->getFriends();
    TEST_ASSERT_EQUAL(0, friends->size());
    Friend andrew = {
        .distance = 1,
        .color = nameToColor("red"),
    };
    manager->foundFriend(andrew);
    friends = manager->getFriends();
    TEST_ASSERT_EQUAL(1, friends->size());
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
