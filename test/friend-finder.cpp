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
    auto friends = manager->getColors(0);
    TEST_ASSERT_NOT_NULL(friends);
}
void test_on_friend_found_adds_colors(void) {
    auto colors = manager->getColors(0);
    TEST_ASSERT_EQUAL(0, colors->size());
    Friend andrew = {
        .name = "Andrew",
        .distance = 20,
    };
    manager->foundFriend(andrew, 0);
    colors = manager->getColors(0);
    TEST_ASSERT_EQUAL(1, colors->size());
    auto color = colors->at(0);
    TEST_ASSERT_EQUAL(80, color.strength);
}
// void test_on_friend_not_found_much_later_disappears(void) {
//     Friend andrew = {
//         .name = "Andrew",
//         .distance = 20,
//     };
//     manager->foundFriend(andrew, 0);
//     auto colors = manager->getColors(1000);
//     TEST_ASSERT_EQUAL(1, colors->size());
// }
void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_exists);
    RUN_TEST(test_returns_friends);
    RUN_TEST(test_on_friend_found_adds_colors);
    UNITY_END(); // stop unit testing
}

int main()
{
    setup();
}

void loop(){
    main();
}
