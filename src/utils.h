#ifndef COLOR_SENSE_UTILS_H
#define COLOR_SENSE_UTILS_H
#include <math.h>
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
#endif // COLOR_SENSE_UTILS_H
