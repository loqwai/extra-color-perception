#define D5 5
#define D7 7
#include <Arduino.h>
#include <BLEDevice.h>
#include <FastLED.h>
#include "./bluetooth_color_scan.h"
#include "./color_tracker.hpp"

unsigned long lastScanTime = 0;
#define DEVICE_NAME "C1"
#define DATA_PIN 22
#define NUM_LEDS 16
CRGBArray<NUM_LEDS> leds;
auto my_id = nameToId(DEVICE_NAME);
void setup()
{
    delay(2000);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // GRB ordering is assumed

    colortracker::init();
    Serial.begin(115200);
    BLEDevice::init(DEVICE_NAME);
    advertiseColorService();
    Serial.printf("%s reporting for duty. %d trackers available \n", DEVICE_NAME, NUM_COLOR_TRACKERS);
}

int count = 0;
void loop()
{
    delay(300);
    if (millis() - lastScanTime > 1100) {
        lastScanTime = millis();
        scanForBleDevices([](Device d)
                        {
        Serial.printf("found device: %d %d \n", d.id, d.rssi);
        colortracker::detect(d); });
    }
    colortracker::update();
    const CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Purple, CRGB::Blue, CRGB::Orange, CRGB::Yellow};
    int totalStrength = 0;
    colortracker::senses[my_id].strength = 10;
    colortracker::senses[my_id].is_empty = false;
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
        auto sense = colortracker::senses[i];
        if (sense.is_empty) continue;
        Serial.printf("sense: %d %d \n", sense.id, sense.strength);
        totalStrength += sense.strength;
    }
    CRGB ledColor = {.red=0, .green=0, .blue=0};
    for (int i = 0; i < NUM_COLOR_TRACKERS; i++)
    {
        auto sense = colortracker::senses[i];
        if (sense.is_empty) continue;
        Serial.printf("sense: %d %d \n", sense.id, sense.strength);
        auto trackerColor = colors[sense.id];
        double colorStrength = (sense.strength / (float)totalStrength);
        Serial.printf("colorStrength: %f \n", colorStrength);
        auto color = CRGB(trackerColor.red * colorStrength, trackerColor.green * colorStrength, trackerColor.blue * colorStrength);
        ledColor.red += color.red;
        ledColor.green += color.green;
        ledColor.blue += color.blue;
        Serial.printf("color: %d %d %d \n", color.red, color.green, color.blue);
    }
    Serial.printf("ledColor: %d %d %d \n", ledColor.red, ledColor.green, ledColor.blue);
    FastLED.clear();
    FastLED.showColor(ledColor);
}
