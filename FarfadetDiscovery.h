#include <Farfadet.h>

#define MAX_MOTOR_COUNT 10


class FarfadetDiscovery
{
public:
  bool poll(uint8_t txPin, HardwareSerial& serial);
  Farfadet getMotorAtIndex(int index);
private:
  int discoveredMotors = 0;
  Farfadet motors[MAX_MOTOR_COUNT];
};
