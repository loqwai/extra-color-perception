#include <Arduino.h>
#include <string>
#include <BLEDevice.h>

typedef void onDeviceFoundCallback(BLEAdvertisedDevice device);

int deviceCount = 0;
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  onDeviceFoundCallback* callback;
  public: MyAdvertisedDeviceCallbacks(onDeviceFoundCallback* callback) {
    // super();
    this->callback = callback;
  }
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    deviceCount++;
    Serial.println(("Found device named " + advertisedDevice.getName()).c_str());
    this->callback(advertisedDevice);
    // name = advertisedDevice.getName();
    // if (name[0] == 'M')
    // {
    //   auto rssi = advertisedDevice.getRSSI();
    //   maxRssi = max(maxRssi, rssi);
    // }
  }
};
void scanForBleDevices (onDeviceFoundCallback callback) {
  Serial.println("Scanning...");
  Serial.println("Found " + String(deviceCount) + " devices");
  BLEScan *pBLEScan;
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(callback));
  pBLEScan->start(1);
}
