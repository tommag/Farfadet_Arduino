#include <Farfadet.h>

#define MAX_MOTOR_COUNT 10


class FarfadetDiscovery
{
  public:
    bool poll(uint8_t txPin, HardwareSerial& serial);

  private:
    int discoveredMotors = 0;
    Estee_TMC5130_UART_Transceiver motors[MAX_MOTOR_COUNT];
};
