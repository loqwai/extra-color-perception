#include <Arduino.h>
#include <BLEDevice.h>
#include "heltec.h"
#include "./bluetooth-color-scan.h"
#include "./color-distance-tracker.hpp"

unsigned long lastScanTime = 0;
#define DEVICE_NAME "C0"

void setupOLED(){
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
}
void setup()
{
  delay(2000);
  colortracker::init();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  BLEDevice::init(DEVICE_NAME);
  advertiseColorService();
  setupOLED();
  Serial.printf("%s reporting for duty. \n", DEVICE_NAME);
  Heltec.display->clear();
}

int count = 0;
void loop()
{
  Heltec.display->drawStringMaxWidth(0, 0, 128, DEVICE_NAME);
  Heltec.display->display();
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  // delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  // delay(100);
  if (millis() - lastScanTime < 2000) return;
    Heltec.display->clear();
    lastScanTime = millis();
    scanForBleDevices([](Device d) {
      Serial.printf("found device: %d %d \n", d.id, d.rssi);
      colortracker::detect(d);
    });
    colortracker::update();
  for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
  {
    auto sense = colortracker::senses[i];
    if (sense.is_empty) continue;
    Serial.printf("sense: %d %d \n", sense.id, sense.strength);
    Heltec.display->drawString(0,10*i+10, String(sense.id));

    uint8_t displayWidth = 75;
    double strengthPercent = (double)sense.strength / 255.0;
    uint8_t displayStrength = (uint8_t)(strengthPercent * displayWidth);
    Heltec.display->drawProgressBar(20, 10 * i+10, displayWidth,8, displayStrength);
  }
}
