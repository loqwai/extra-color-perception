#include <unity.h>
#include <string>
#include <map>
#include "friend.h"
FriendFinder *manager;
void setUp(void)
{
    manager = new FriendFinder();
}

void tearDown(void)
{
    // clean stuff up here
    delete manager;
}

void test_exists(void)
{
    TEST_ASSERT_NOT_NULL(manager);
}
void test_returns_friends(void)
{
    auto friends = manager->updateColors();
    TEST_ASSERT_NOT_NULL(friends);
}
void test_on_friend_found_adds_colors(void)
{
    auto colors = manager->updateColors();
    TEST_ASSERT_EQUAL(0, colors->size());
    Friend andrew = {
        .name = "Andrew",
        .distance = 20,
    };
    manager->foundFriend(andrew, 0);
    colors = manager->updateColors();
    TEST_ASSERT_EQUAL(1, colors->size());

    auto strength = colors->at(0).strength;
    TEST_ASSERT_GREATER_THAN(0, strength);

    manager->foundFriend(andrew, 0);
    colors = manager->updateColors();
    auto strength2 = colors->at(0).strength;
    TEST_ASSERT_GREATER_THAN(strength,strength2);

    manager->foundFriend(andrew, 0);
    colors = manager->updateColors();
    auto strength3 = colors->at(0).strength;
    TEST_ASSERT_GREATER_THAN(strength,strength2);

}
void test_on_friend_not_found_later_reduces_strength(void)
{
    Friend andrew = {
        .name = "Andrew",
        .distance = 20,
    };
    manager->foundFriend(andrew, 0);
    auto colors = manager->updateColors();
    auto color = colors->at(0);
    TEST_ASSERT_LESS_THAN(67, color.strength);
}
void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_exists);
    RUN_TEST(test_returns_friends);
    RUN_TEST(test_on_friend_found_adds_colors);
    RUN_TEST(test_on_friend_not_found_later_reduces_strength);
    UNITY_END(); // stop unit testing
}

int main()
{
    setup();
}

void loop()
{
    main();
}
