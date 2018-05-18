#include <Farfadet.h>

void Farfadet::init(uint8_t txPin, int stepsPerTurn)
{
  init(txPin, stepsPerTurn, Serial1);
}

void Farfadet::init(uint8_t txPin, int stepsPerTurn, Stream& serial)
{
  tmc = Estee_TMC5130_UART_Transceiver(txPin, Serial1, 1);
  Serial1.begin(250000);
  Serial1.setTimeout(5); // TMC5130 should answer back immediately when reading a register.
  _stepsPerTurn = stepsPerTurn;
  _spoolDiameter = 0;
  tmc.begin(4, 4, Estee_TMC5130::NORMAL_MOTOR_DIRECTION);
  setControlMode(ANGULAR_POSITION_MODE);
  tmc.setMaxSpeed(200);
  tmc.setRampSpeeds(0, 0.1, 100); //Start, stop, threshold speeds
  tmc.setAccelerations(250, 350, 500, 700); //AMAX, DMAX, A1, D1
}

void Farfadet::stop()
{
  tmc.stop();
}

void Farfadet::setControlMode(uint8_t mode)
{
  if( mode != _controlMode )
  {
    _controlMode = mode;
    if( _controlMode == SPEED_CONTROL_MODE )
    {
      tmc.setRampMode(Estee_TMC5130::VELOCITY_MODE);
    }
    else if( _controlMode == LINEAR_POSITION_MODE || _controlMode == ANGULAR_POSITION_MODE )
    {
      tmc.setRampMode(Estee_TMC5130::POSITIONING_MODE);
    }
  }
}

void Farfadet::setTargetPosition(float target)
{
  if( _controlMode == LINEAR_POSITION_MODE  )
  {
    float nbTurns = target/(M_PI*_spoolDiameter);
    long targetSteps = nbTurns * _stepsPerTurn;
    tmc.setTargetPosition(targetSteps);
  }
  else if( _controlMode == ANGULAR_POSITION_MODE )
  {
    long targetSteps = target*_stepsPerTurn/360.0;
    tmc.setTargetPosition(targetSteps);
  }
}

void Farfadet::setTargetSpeed(float speed)
{
  tmc.setMaxSpeed(speed);
}

float Farfadet::getCurrentPosition()
{
  if( _controlMode == LINEAR_POSITION_MODE  )
  {
    float nbTurns = tmc.getCurrentPosition()/_stepsPerTurn;
    return nbTurns*M_PI*_spoolDiameter;
  }
  else if( _controlMode == ANGULAR_POSITION_MODE )
  {
    long currentAngle = tmc.getCurrentPosition()*360.0/_stepsPerTurn;
    return currentAngle;
  }
}

float Farfadet::getCurrentSpeed()
{
  return tmc.getCurrentSpeed();
}

void Farfadet::setSpoolDiameter(float diameter)
{
  _spoolDiameter = diameter;
}

float Farfadet::getSpoolDiameter()
{
  return _spoolDiameter;
}
