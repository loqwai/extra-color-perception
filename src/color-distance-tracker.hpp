#ifndef NUM_COLOR_TRACKERS
#ifndef NUM_COLOR_TRACKERS
#define NUM_COLOR_TRACKERS 3
#endif

// BLE Device Name Data Structure:
// [1] - ID (0-255)
// [2] - R (0-255)
// [3] - G (0-255)
// [4] - B (0-255)
namespace colortracker
{
  struct Sense
  {
    uint8_t id;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t strength;
  };

  struct Device
  {
    char *name;
    uint8_t id;
    uint8_t rssi;
  };

  Device devices[NUM_COLOR_TRACKERS];
  Device newDevices[NUM_COLOR_TRACKERS];
  Sense senses[NUM_COLOR_TRACKERS];
  void init()
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {

      devices[i].name = NULL;
      devices[i].rssi = 0;
      devices[i].id = i;

      newDevices[i].name = NULL;
      newDevices[i].rssi = 0;
      newDevices[i].id = i;

      senses[i].id = i;
      senses[i].r = 0;
      senses[i].g = 0;
      senses[i].b = 0;
      senses[i].strength = 0;
    }
  }
}
#endif
