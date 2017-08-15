#include <EEPROM.h>
int kp=35;
int ki=20;
int kd=5;

void setup()
{
}

void loop()
{
  EEPROM.write(0,kp);
  EEPROM.write(1,ki);
  EEPROM.write(2,kd);
}
