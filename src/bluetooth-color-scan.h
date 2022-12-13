#include <Arduino.h>
#include <string>
#include <BLEDevice.h>
#include "./utils.h"
#include "./friend.h"

#define COLOR_SENSE_UUID "ceb9bda0-7adc-11ed-93f2-bf342b277c5d"
#define COLOR_CHARACTERISTIC_UUID "99aba128-7ae6-11ed-bf02-0b5fba621e12"

typedef void onFriendFound(Friend f);

class BLEColorScanner : public BLEAdvertisedDeviceCallbacks
{
  onFriendFound *callback;

public:
  BLEColorScanner(onFriendFound callback)
  {
    this->callback = callback;
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
    auto distance = rssiToDistance(rssi);
    auto color = nameToColor(name);
    Friend f;
    f.distance = distance;
    f.color = color;
    callback(f);
  }
};

void scanForBleDevices(onFriendFound callback)
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
        }
      },
      true);
}
