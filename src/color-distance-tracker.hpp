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
    bool is_empty;
  };

  struct Device
  {
    uint8_t id;
    int32_t rssi;
    bool is_empty;
  };

  Device devices[NUM_COLOR_TRACKERS];
  Device newDevices[NUM_COLOR_TRACKERS];
  Sense senses[NUM_COLOR_TRACKERS];
  uint32_t num_color_trackers = NUM_COLOR_TRACKERS;

  void init(Device* d){
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      d[i].id = i;
      d[i].is_empty = true;
    }
  }
  void init(Sense* s){
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
      init(newDevices);
      init(senses);
    }
  }
  void detect(Device device){
    if (device.is_empty)
    {
      return;
    }
    if (devices[device.id].is_empty)
    {
      devices[device.id].rssi = 0;
      devices[device.id].is_empty = false;
    }
    newDevices[device.id].rssi = device.rssi;
    newDevices[device.id].is_empty = false;
  };

  void update(){
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
      auto device = devices[i];
      auto sense = senses[i];

      if(device.is_empty){
        sense.is_empty = true;
        continue;
      }
      sense.is_empty = false;
      sense.strength = 100;
    }
  }
}
#endif
