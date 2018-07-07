
#include <FarfadetDiscovery.h>

bool FarfadetDiscovery::poll(uint8_t txPin, HardwareSerial& serial)
{
  serial.begin(500000);
  serial.setTimeout(1);
  bool chainEnd = false;
  while (!chainEnd && discoveredMotors < MAX_MOTOR_COUNT)
  {
    // address 1 (NAI input has a pull up resistor)
    motors[discoveredMotors] = Estee_TMC5130_UART_Transceiver(txPin, serial, 1);

    //Try to query a TMC5130 at address 1 (default)
    Estee_TMC5130_UART::ReadStatus readStatus;
    uint32_t gconf = motors[discoveredMotors].readRegister(TMC5130_Reg::GCONF, &readStatus);

    switch (readStatus)
    {
      case Estee_TMC5130_UART::SUCCESS:
      {
        //Addressing
        uint8_t address = 254-discoveredMotors;
        motors[discoveredMotors].setSlaveAddress(address, true);
        Serial.print("Found TMC5130 address : ");
        Serial.println(address);

        //Turn on the bus switch to get access to the next board.
        motors[discoveredMotors].writeRegister(TMC5130_Reg::IO_INPUT_OUTPUT, 0); //set NAO low
        motors[discoveredMotors].resetCommunication();
        discoveredMotors++;
      }
      break;

      case Estee_TMC5130_UART::NO_REPLY:
      //Serial.println("No more TMC5130 found.");
      chainEnd = true;
      break;

      case Estee_TMC5130_UART::BAD_CRC:
      Serial.println("A TMC5130 replied with a bad CRC. Trying again."); //TODO keep a count of failed attempts.
      motors[discoveredMotors].resetCommunication();
      break;
    }
  }
}
