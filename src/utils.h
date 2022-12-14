#ifndef COLOR_SENSE_UTILS_H
#define COLOR_SENSE_UTILS_H
#include <math.h>
#define MAX_DISTANCE 60
namespace utils
{
  uint8_t smooth(uint8_t val, uint8_t prev_val, float smooth_factor)
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

  double map_range(double x, double in_min, double in_max, double out_min, double out_max)
  {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  uint8_t distance_to_strength(double distance)
  {
    return map_range(distance, 0, MAX_DISTANCE, 0, 255);
  }

  uint8_t rssi_to_strength(int rssi)
  {
    return distance_to_strength(rssi_to_distance(rssi));
  }
}
#endif // COLOR_SENSE_UTILS_H
