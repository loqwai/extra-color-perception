#ifndef NUM_COLOR_TRACKERS
#ifndef NUM_COLOR_TRACKERS
#define NUM_COLOR_TRACKERS 3
#endif
#include "./utils.h"
#include <memory>
#include <vector>

#define ptr std::shared_ptr
#define vec std::vector
#define string std::string
// BLE Device Name Data Structure:
// [1] - ID (0-255)
// [2] - R (0-255)
// [3] - G (0-255)
// [4] - B (0-255)
namespace colortracker
{
  class Device
  {
    public:
     const string id;
     int32_t rssi;
     Device(const string &id, int32_t rssi) : id(id), rssi(rssi) {}
  };

  class Sense
  {
    public:
      uint8_t id;
      uint8_t strength;
  };

  class ColorTracker
  {
    vec<ptr<Device>> devices;
    vec<ptr<Device>> new_devices;
    vec<ptr<Sense>> senses;
    ColorTracker(const uint32_t num_color_trackers=3){

    }
  };
}
#endif
