#ifndef FRIEND_H
#define FRIEND_H
#include <string>
#include <vector>
#include <stdexcept>
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
class FriendFinder
{
public:
  static const uint8_t MAX_DISTANCE = 60.0;
  std::vector<ColorStrength *> colorStrengths;
  std::map<std::string, uint8_t> newColors;
  std::map<std::string, uint8_t> colors;
  static uint8_t distanceToStrength(uint8_t distance)
  {
    if (distance > 66)
    {
      throw std::invalid_argument("Distance is too large");
    }
    if (distance <= 0)
    {
      throw std::invalid_argument("Distance is too small");
    }

    float distancePercentage = (distance * 1.0) / MAX_DISTANCE;
    return 100 - (100.0 * distancePercentage);
  }

  bool hasFriend(std::string name) {
    return colors.count(name) > 0;
  }
  std::vector<ColorStrength *> *updateColors()
  {
    colorStrengths.clear();
    for (auto const &x : colors)
    {
      auto dist = x.second;
      auto color = x.first;
      uint8_t newDistance = MAX_DISTANCE;
      if(newColors.count(color) > 0) {
        newDistance = newColors[color];
      }
      auto distance = lerp(dist, newDistance, 1);
      auto strength = distanceToStrength(distance);
      colorStrengths.push_back(new ColorStrength{
          .color = nameToColor(color),
          .strength = strength,
      });
    }
    newColors.clear();
    return &colorStrengths;
  }
  void foundFriend(Friend f, uint32_t now)
  {
    newColors.emplace(f.name,f.distance);
    if(colors.count(f.name) == 0) {
      colors[f.name] = MAX_DISTANCE;
    }
  }
};
#endif // FRIEND_H
