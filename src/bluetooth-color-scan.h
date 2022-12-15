#include <Arduino.h>
#include <string>
#include <BLEDevice.h>
#include "./utils.h"
#include "./color-distance-tracker.hpp"

#define COLOR_SENSE_UUID "ceb9bda0-7adc-11ed-93f2-bf342b277c5d"
#define COLOR_CHARACTERISTIC_UUID "99aba128-7ae6-11ed-bf02-0b5fba621e12"

using Device = colortracker::Device;
typedef void onDeviceFound(Device);
uint8_t nameToId(std::string name)
{
  if (name[1] == '1')
  {
    return 1;
  }
  if (name[1] == '2')
  {
    return 2;
  }
  if (name[1] == '3')
  {
    return 3;
  }
  return 255;
}
class BLEColorScanner : public BLEAdvertisedDeviceCallbacks
{
  onDeviceFound *callback;

public:
  explicit BLEColorScanner(onDeviceFound cb)
  {
    callback = cb;
  }
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    auto service_id = advertisedDevice.getServiceUUID();

    if (service_id.toString() != COLOR_SENSE_UUID)
    {
      return;
    }
    Serial.println("Found extra color service");
    auto name = advertisedDevice.getName();
    auto rssi = advertisedDevice.getRSSI();
    auto id = nameToId(name);
    if (id == 255)
    {
      return;
    }
    callback({
      .id = id,
      .rssi = rssi,
      .is_empty = false,
    });
  }
};
void scanForBleDevices(onDeviceFound callback)
{
  auto pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setAdvertisedDeviceCallbacks(new BLEColorScanner(callback));

  pBLEScan->start(
      1, [](BLEScanResults results)
      {
        for(int i = 0; i < results.getCount(); i++)
        {
          auto result = results.getDevice(i);
          Serial.println(result.toString().c_str());
        } },
      false);
}
