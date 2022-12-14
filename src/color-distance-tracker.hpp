#ifndef NUM_COLOR_TRACKERS
#ifndef NUM_COLOR_TRACKERS
#define NUM_COLOR_TRACKERS 3
#endif
#include "./utils.h"
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
    bool is_empty;
  };

  struct Device
  {
    uint8_t id;
    int32_t rssi;
    bool is_empty;
  };

  Device devices[NUM_COLOR_TRACKERS];
  Device new_devices[NUM_COLOR_TRACKERS];
  Sense senses[NUM_COLOR_TRACKERS];
  uint32_t num_color_trackers = NUM_COLOR_TRACKERS;

  void init(Device *d)
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      d[i].id = i;
      d[i].is_empty = true;
    }
  }
  void init(Sense *s)
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      s[i].id = i;
      s[i].is_empty = true;
    }
  }

  void init()
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      init(devices);
      init(new_devices);
      init(senses);
    }
  }
  void detect(Device device)
  {
    if (devices[device.id].is_empty)
    {
      devices[device.id].rssi = -95;
      devices[device.id].is_empty = false;
    }
    new_devices[device.id].rssi = device.rssi;
    new_devices[device.id].is_empty = false;
  };

  void update()
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      if (devices[i].is_empty)
      {
        senses[i].is_empty = true;
        senses[i].strength = 0;
        continue;
      }
      senses[i].is_empty = false;
      if (new_devices[i].is_empty)
      {
        devices[i].rssi = utils::smooth(devices[i].rssi, -110, 0.1);
      }
      else
      {
        devices[i].rssi = utils::smooth(devices[i].rssi, new_devices[i].rssi, 0.1);
        new_devices[i].is_empty = true;
      }
      if(devices[i].rssi < -100){
        devices[i].is_empty = true;
        senses[i].is_empty = true;
        senses[i].strength = 0;
        continue;
      }
      senses[i].strength = utils::rssi_to_strength(devices[i].rssi);
    }
  }
}
#endif
