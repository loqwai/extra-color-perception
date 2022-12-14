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
typedef void onFriendFound(Friend f);
typedef void FriendResultFn(onFriendFound callback);
class FriendFinder {
  private:
    std::map<std::string, Friend> friends;
  public:
    FriendFinder() {
    }
    std::vector<Friend>* getFriends(int delta=0) {
      auto friendList = new std::vector<Friend>();
      for (auto const& x : friends)
      {
        friendList->push_back(x.second);
      }
      return friendList;
    }
    void foundFriend(Friend f) {
      friends[f.name] = f;
    }
};
#endif // FRIEND_H
