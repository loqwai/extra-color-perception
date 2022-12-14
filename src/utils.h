#ifndef COLOR_SENSE_UTILS_H
#define COLOR_SENSE_UTILS_H
#include <math.h>
#define MAX_DISTANCE 80
namespace utils
{
  double smooth(double val, double prev_val, double smooth_factor)
  {
    return val + smooth_factor * (prev_val - val);
  }

  double rssi_to_distance(int rssi)
  {
    int txPower = -59; // hard coded power value. Usually ranges between -59 to -65

    if (rssi == 0)
    {
      return 255; // if we cannot determine accuracy, return max distance.
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

  uint8_t distance_to_strength(double distance)
  {
    double distancePercentage = distance * 1.0 /MAX_DISTANCE;
    return 255 - (distancePercentage * 255);

  }

  uint8_t rssi_to_strength(int rssi)
  {
    return distance_to_strength(rssi_to_distance(rssi));
  }
}
#endif // COLOR_SENSE_UTILS_H
