#include <LiquidCrystal.h>

int sonar=0;


const int pingPin = 31;
LiquidCrystal lcd(30, 32, 5, 4, 3, 2);
void setup() {
  lcd.begin(16, 2);

  lcd.print("Initiating Robot");
  delay(1000);
  lcd.clear();
}

void loop()
{

   lcd.clear();
   
  lcd.print(sonar_range());
  delay(200);
 
}
int sonar_range()
{
  long distance;
  distance=sonar_data();
   if((distance>1)&&(distance<=32))
  {
    return 1;
  }
  else if((distance>32)&&(distance<=60))
  {
    return 2;
  }
  else if((distance>60)&&(distance<=88))
  {
    return 3;
  }
  else if((distance>88)&&(distance<=116))
  {
    return 4;
  }
  else
  {
    return 0;
  }

}
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
long sonar_data()
{
  long duration, cm;

  
  pinMode(pingPin, OUTPUT);
  delayMicroseconds(10);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(20);
   pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}
