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
  void init(uint8_t txPin, int stepsPerTurn);
  void init(uint8_t txPin, int stepsPerTurn, Stream& serial);
  void stop();
  void setControlMode(uint8_t mode);
  void setTargetPosition(float target);//in degres or in meters depending on the mode
  long getCurrentPosition();
  void setTargetSpeed(float speed);
  float getCurrentSpeed();

  void setSpoolDiameter(float diameter);
  float getSpoolDiameter();

private:
  Estee_TMC5130_UART_Transceiver tmc;
  uint8_t _controlMode;
  int _stepsPerTurn;
  float _spoolDiameter;//in meters
};
