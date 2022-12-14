#ifndef FRIEND_H
#define FRIEND_H
#include <string>
#include <vector>
#include "./utils.h"
struct Color
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct Friend
{
  std::string name;
  uint8_t distance;
  Color color;
};


Color nameToColor(std::string name)
{
  if (name == "red")
  {
    return {255, 0, 0};
  }
  if (name == "green")
  {
    return {0, 255, 0};
  }
  if (name == "blue")
  {
    return {0, 0, 255};
  }
  if (name == "yellow")
  {
    return {255, 255, 0};
  }
  if (name == "purple")
  {
    return {255, 0, 255};
  }
  if (name == "cyan")
  {
    return {0, 255, 255};
  }
  if (name == "white")
  {
    return {255, 255, 255};
  }
  if (name == "black")
  {
    return {0, 0, 0};
  }
  return {0, 0, 0};
}

struct ColorStrength
{
  Color color;
  uint8_t strength;
};
struct FriendLastSeen
{
  Friend theFriend;
  uint32_t lastSeen;
};
typedef void onFriendFound(Friend f);
typedef void FriendResultFn(onFriendFound callback);
class FriendFinder {
  private:
    std::map<std::string, FriendLastSeen> friends;
    std::map<std::string,ColorStrength> prevColorStrengths;
  public:
    static const uint8_t MAX_DISTANCE = 60;
    static uint8_t distanceToStrength(uint8_t distance) {
      return 100 - (distance * 100 / MAX_DISTANCE);
    }
    std::vector<ColorStrength>* getColors(uint32_t now) {
      auto colorStrengthList = new std::vector<ColorStrength>();
      for (auto const& x : friends)
      {
        auto friendLastSeen = x.second;
        colorStrengthList->push_back(ColorStrength{
          .color = friendLastSeen.theFriend.color,
          .strength = distanceToStrength(friendLastSeen.theFriend.distance)
        });
      }
      return colorStrengthList;
    }
    void foundFriend(Friend f, uint32_t now) {
      friends[f.name] = FriendLastSeen {
        .theFriend = f,
        .lastSeen = now
      };
    }
};
#endif // FRIEND_H
