
#include <FarfadetDiscovery.h>

bool FarfadetDiscovery::poll(uint8_t txPin, HardwareSerial& serial)
{
  for (int i = 0; i < MAX_MOTOR_COUNT; i++)
  {
    motors[i] = Farfadet();
  }
  discoveredMotors = 0;
  serial.begin(500000);
  serial.setTimeout(1);
  bool chainEnd = false;
  while (!chainEnd && discoveredMotors < MAX_MOTOR_COUNT)
  {
    // address 1 (NAI input has a pull up resistor)
    Farfadet farfadet;
    farfadet.init(txPin,200,serial,1);//Estee_TMC5130_UART_Transceiver(txPin, serial, 1);
    motors[discoveredMotors] = farfadet;


    //Try to query a TMC5130 at address 1 (default)
    Estee_TMC5130_UART::ReadStatus readStatus;
    readStatus = motors[discoveredMotors].getReadStatus();

    switch (readStatus)
    {
      case Estee_TMC5130_UART::SUCCESS:
      {
        //Addressing
        uint8_t address = 254-discoveredMotors;
        motors[discoveredMotors].setAddress(address);
        Serial.print("Found TMC5130 address : ");
        Serial.println(address);

        //Turn on the bus switch to get access to the next board.
        // motors[discoveredMotors].writeRegister(TMC5130_Reg::IO_INPUT_OUTPUT, 0); //set NAO low
        motors[discoveredMotors].resetCommunication();
        motors[discoveredMotors].activateBusOutput();
        discoveredMotors++;
      }
      break;

      case Estee_TMC5130_UART::NO_REPLY:
      //Serial.println("No more TMC5130 found.");
      chainEnd = true;
      break;

      case Estee_TMC5130_UART::BAD_CRC:
      //Serial.println("A TMC5130 replied with a bad CRC. Trying again."); //TODO keep a count of failed attempts.
      motors[discoveredMotors].resetCommunication();
      break;
    }
  }
  return discoveredMotors > 0;
}

Farfadet FarfadetDiscovery::getMotorAtIndex(int index)
{
  if( index < 0 || index > discoveredMotors )
  {
    Serial.print(" No motor available at index ");
    Serial.println(index);
    Farfadet f;
    f.init(0,0,-1);
    return f;
  }
  return motors[index];
}
