#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(30, 32, 5, 4, 3, 2);

int i;
int val[4]={0,0,0,0};
void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 2);
Serial.begin(9600);
pinMode(22,OUTPUT);
pinMode(23,OUTPUT);
pinMode(24,OUTPUT);
pinMode(25,OUTPUT);
pinMode(9,OUTPUT);
pinMode(8,OUTPUT);
analogWrite(9,200);
analogWrite(8,200);

lcd.print("Initiating Robot");
delay(1000);
lcd.clear();
//fwd();
}

void loop() {
  // put your main code here, to run repeatedly: 

for(i=0;i<=3;i++)
{
  
lcd.setCursor(i*4,0);
lcd.print(analogRead(i+1));
}
lcd.setCursor(2,1);
lcd.print(analogRead(15));
lcd.setCursor(11,1);
lcd.print(analogRead(9));
delay(200);
lcd.clear();

}

int adc(int t)
{
  if(t<300)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


  
  



void back()
{
  digitalWrite(22,LOW);
digitalWrite(23,HIGH);
digitalWrite(24,HIGH);
digitalWrite(25,LOW);
}

void fwd()
{
  digitalWrite(22,HIGH);
digitalWrite(23,LOW);
digitalWrite(24,LOW);
digitalWrite(25,HIGH);
}

void left()
{
  digitalWrite(22,HIGH);
digitalWrite(23,LOW);
digitalWrite(24,HIGH);
digitalWrite(25,LOW);
}

void right()
{
  digitalWrite(22,LOW);
digitalWrite(23,HIGH);
digitalWrite(24,LOW);
digitalWrite(25,HIGH);
}
