#include <Farfadet.h>

void Farfadet::init(uint8_t txPin)
{
  init(txPin,Serial1);
}

void Farfadet::init(uint8_t txPin, Stream& serial)
{
  tmc = Estee_TMC5130_UART_Transceiver(txPin, Serial1, 1);
  Serial1.begin(250000);
  Serial1.setTimeout(5); // TMC5130 should answer back immediately when reading a register.
  tmc.begin(4, 4, Estee_TMC5130::NORMAL_MOTOR_DIRECTION);
  tmc.setRampMode(Estee_TMC5130::POSITIONING_MODE);
  tmc.setMaxSpeed(200);
  tmc.setRampSpeeds(0, 0.1, 100); //Start, stop, threshold speeds
  tmc.setAccelerations(250, 350, 500, 700); //AMAX, DMAX, A1, D1
}

void Farfadet::setTargetPosition(long target)
{
  tmc.setTargetPosition(target);
}

long Farfadet::getCurrentPosition()
{
  return tmc.getCurrentPosition();
}

float Farfadet::getCurrentSpeed()
{
  return tmc.getCurrentSpeed();
}
