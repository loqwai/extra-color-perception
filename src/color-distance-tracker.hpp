#ifndef NUM_COLOR_TRACKERS
#ifndef NUM_COLOR_TRACKERS
#define NUM_COLOR_TRACKERS 3
#endif
#include "./utils.h"
// BLE Device Name Data Structure:
// [0] - Intentionally blank
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

  void clear(Device* d, int id)
  {
    d->id = id;
    d->rssi = -999;
    d->is_empty = true;
  }
  void clear(Sense* s, int id)
  {
    s->id = id;
    s->strength = 0;
    s->is_empty = true;
  }
  void init(Device *d)
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      clear(&d[i], i);
    }
  }
  void init(Sense *s)
  {
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      clear(&s[i], i);
    }
  }

  void init()
  {
      init(devices);
      init(new_devices);
      init(senses);
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
        clear(&senses[i], i);
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
        clear(&new_devices[i], i);
      }
      if (devices[i].rssi < -100)
      {
        clear(&devices[i], i);
        clear(&senses[i], i);
        continue;
      }
      senses[i].strength = utils::rssi_to_strength(devices[i].rssi);
    }
  }
}
#endif
