#include <Arduino.h>
#include <BLEDevice.h>
#include "./bluetooth-color-scan.h"
#include "./color-distance-tracker.hpp"
void setup()
{
  delay(2000);
  colortracker::init();
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  BLEDevice::init("Color Sense");
}

int count = 0;
void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  // Serial.println("about to scan");
  scanForBleDevices([](Device d){
    Serial.printf("found device: %d %d \n", d.id, d.rssi);
    colortracker::detect(d);
  });
  colortracker::update();
  for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
  {
    auto sense = colortracker::senses[i];
    if(sense.is_empty) continue;
    Serial.printf("sense: %d %d \n", sense.id, sense.strength);
  }
}
