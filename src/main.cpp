#include <Arduino.h>
#include <BLEDevice.h>
#include "./bluetooth-color-scan.h"

void setup()
{
  delay(2000);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  BLEDevice::init("");
}

int count = 0;
void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("about to scan");
  scanForBleDevices([](Friend f){
    Serial.println("found friend");
    Serial.println(f.distance);
    // Serial.printf("Color: %n %n %n", f.color.r, f.color.g, f.color.b);
  });
}
