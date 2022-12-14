#ifndef COLOR_SENSE_UTILS_H
#define COLOR_SENSE_UTILS_H
#include <math.h>

uint8_t lerp(uint8_t a, uint8_t b, float f)
{
  return a + f * (b - a);
}

double rssiToDistance(int rssi)
{
  int txPower = -59; // hard coded power value. Usually ranges between -59 to -65

  if (rssi == 0)
  {
    return -1.0; // if we cannot determine accuracy, return -1.
  }

  double ratio = rssi * 1.0 / txPower;
  if (ratio < 1.0)
  {
    return pow(ratio, 10);
  }
  else
  {
    double accuracy = (0.89976) * pow(ratio, 7.7095) + 0.111;
    return accuracy;
  }
}
uint8_t mapRange(int8_t x, int8_t in_min, int8_t in_max, int8_t out_min, int8_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
#endif // COLOR_SENSE_UTILS_H
