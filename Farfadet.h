#include <Estee_TMC5130.h>

enum FARFADET_MODES
{
  SPEED_CONTROL_MODE  = 0x00,
  ANGULAR_POSITION_MODE = 0x01,
  LINEAR_POSITION_MODE = 0x02
};

class Farfadet
{
public:
  void init(uint8_t txPin);
  void init(uint8_t txPin, Stream& serial);

  void setControlMode(uint8_t mode);
  void setTargetPosition(long target);
  long getCurrentPosition();
  float getCurrentSpeed();

private:
  Estee_TMC5130_UART_Transceiver tmc;
  uint8_t _controlMode;
};
