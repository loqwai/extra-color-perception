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
void test_on_friend_found_adds_colors(void)
{
    auto colors = manager->updateColors();
    TEST_ASSERT_EQUAL(0, colors->size());
    Friend a = {
        .name = "Andrew",
        .distance = 1,
    };
    auto andrew = a;

    manager->foundFriend(andrew, 0);
    colors = manager->updateColors();
    // TEST_ASSERT_EQUAL(1, colors->size());
    // TEST_ASSERT_TRUE(manager->hasFriend("Andrew"));
    // auto strength = colors->at(0)->strength;
    // // TEST_ASSERT_GREATER_THAN(0, strength);

    // manager->foundFriend(andrew, 0);
    // colors = manager->updateColors();
    // auto strength2 = colors->at(0)->strength;
    // TEST_ASSERT_GREATER_THAN(strength, strength2);

    // manager->foundFriend(andrew, 0);
    // colors = manager->updateColors();
    // auto strength3 = colors->at(0)->strength;
    // TEST_ASSERT_GREATER_THAN(strength2, strength3);
}
// void test_on_friend_not_found_later_reduces_strength(void)
// {
//     auto colors = manager->updateColors();
//     TEST_ASSERT_EQUAL(0, colors->size());
//     Friend s = {
//         .name = "Sarah",
//         .distance = 20,
//     };
//     auto sarah = s;
//     manager->foundFriend(sarah, 0);
//     colors = manager->updateColors();
//     TEST_ASSERT_EQUAL(1, colors->size());

//     auto strength = colors->at(0)->strength;
//     TEST_ASSERT_GREATER_THAN(0, strength);

//     colors = manager->updateColors();
//     auto strength2 = colors->at(0)->strength;
//     TEST_ASSERT_GREATER_THAN(strength2, strength);
// }
// void test_friend_found_eventually_reaches_100(void)
// {
//     Friend s = {
//         .name = "Sarah",
//         .distance = 1,
//     };
//     auto sarah = s;
//     for (int i = 0; i < 100; i++)
//     {
//         manager->foundFriend(sarah, 0);
//         auto colors = manager->updateColors();
//         auto strength = colors->at(0)->strength;
//         TEST_ASSERT_GREATER_THAN(0, strength);
//     }
//     manager->foundFriend(sarah, 0);
//     auto colors = manager->updateColors();
//     auto strength = colors->at(0)->strength;
//     TEST_ASSERT_EQUAL(100, strength);
// }
// void test_friend_not_found_eventually_reaches_0(void)
// {
//     Friend s = {
//         .name = "Sarah",
//         .distance = 20,
//     };
//     auto sarah = s;
//     manager->foundFriend(sarah, 0);
//     for (int i = 0; i < 100; i++)
//     {
//         manager->updateColors();
//     }
//     auto colors = manager->updateColors();
//     auto strength = colors->at(0)->strength;
//     TEST_ASSERT_EQUAL(0, strength);
// }
// void test_missing_friend_doesnt_go_to_0_immediately(void)
// {
//     Friend s = {
//         .name = "Sarah",
//         .distance = 1,
//     };
//     auto sarah = s;
//     manager->foundFriend(sarah, 0);
//     auto colors = manager->updateColors();

//     colors = manager->updateColors();
//     auto strength = colors->at(0)->strength;

//     TEST_ASSERT_GREATER_THAN(0, strength);

//     colors = manager->updateColors();
//     strength = colors->at(0)->strength;
//     TEST_ASSERT_GREATER_THAN(0, strength);
// }

// void test_closer_distance_means_more_strength(void)
// {
//     Friend s = {
//         .name = "Sarah",
//         .distance = 1,
//         .color = {255, 0, 0}};
//     Friend a = {
//         .name = "Andrew",
//         .distance = 20,
//         .color = {0, 255, 0}};

//     auto sarah = s;
//     auto andrew = a;
//     for (int i = 0; i < 10; i++)
//     {
//         manager->foundFriend(sarah, 0);
//         manager->foundFriend(andrew, 0);
//         manager->updateColors();
//     }
//     manager->foundFriend(sarah, 0);
//     manager->foundFriend(andrew, 0);
//     auto colors = manager->updateColors();
//     auto first = colors->at(1);
//     auto strength = first->strength;
//     // make sure the first color is red
//     TEST_ASSERT_EQUAL(255, first->color.r);

//     auto strength2 = colors->at(1)->strength;
//     TEST_ASSERT_GREATER_THAN(strength, strength2);
// }
void test_distance_is_inverted_to_strength(void)
{
    auto d1 = manager->distanceToStrength(1);
    auto d2 = manager->distanceToStrength(2);
    TEST_ASSERT_GREATER_THAN(d2,d1);
}
void test_large_distance_means_no_strength(void)
{
    auto d1 = manager->distanceToStrength(60);
    TEST_ASSERT_EQUAL(0, d1);
}
void test_zero_distance_means_full_strength(void)
{
    auto d1 = manager->distanceToStrength(0);
    TEST_ASSERT_EQUAL(100, d1);
}
void test_small_distance_means_full_strength(void)
{
    auto d1 = manager->distanceToStrength(1);
    TEST_ASSERT_GREATER_THAN(90, d1);
}
void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_on_friend_found_adds_colors);
    // RUN_TEST(test_on_friend_not_found_later_reduces_strength);
    // RUN_TEST(test_friend_not_found_eventually_reaches_0);
    // RUN_TEST(test_friend_found_eventually_reaches_100);
    // RUN_TEST(test_closer_distance_means_more_strength);
    // RUN_TEST(test_missing_friend_doesnt_go_to_0_immediately);
    RUN_TEST(test_distance_is_inverted_to_strength);
    RUN_TEST(test_large_distance_means_no_strength);
    RUN_TEST(test_zero_distance_means_full_strength);
    RUN_TEST(test_small_distance_means_full_strength);
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
