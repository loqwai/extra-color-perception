#ifndef FRIEND_H
#define FRIEND_H
#include <string>
#include <vector>
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

typedef void onFriendFound(Friend f);
typedef void FriendResultFn(onFriendFound callback);
class FriendFinder {
  private:
    std::map<std::string, Friend> friends;
  public:
    FriendFinder() {
    }
    std::vector<ColorStrength>* getColors(int delta=0) {
      auto colorStrengthList = new std::vector<ColorStrength>();
      for (auto const& x : friends)
      {
        colorStrengthList->push_back({});
      }
      return colorStrengthList;
    }
    void foundFriend(Friend f) {
      friends[f.name] = f;
    }
};
#endif // FRIEND_H
