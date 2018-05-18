#include <Estee_TMC5130.h>

class Farfadet
{
public:
  void init(uint8_t txPin);
  void init(uint8_t txPin, Stream& serial);

  void setTargetPosition(long target);
  long getCurrentPosition();
  float getCurrentSpeed();

private:
  Estee_TMC5130_UART_Transceiver tmc;
};
