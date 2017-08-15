#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int count=0,n=0,kp=0,ki=0,kd=0;
void setup()
{
  lcd.begin(16,2);
  
  lcd.clear();
  pinMode(32,OUTPUT);
pinMode(26,OUTPUT);
digitalWrite(32,HIGH);
digitalWrite(26,HIGH);
init_pid_tune();
}

void loop()
{
 tune_pid();
 lcd.clear();
lcd.print("parameters set"); 
}

void init_pid_tune()
{
  pinMode(47,INPUT);

digitalWrite(32,HIGH);
lcd.print("PID TUNE");
lcd.setCursor(0,1);
lcd.print("Wizard");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
  lcd.print("Kp=");
  lcd.setCursor(7,0);
  lcd.print("Kd=");
  lcd.setCursor(2,1);
  lcd.print("Ki=");
count=0;
}

void tune_pid()
{
  
  do
  {
    if(digitalRead(47) == LOW)
  {
    digitalWrite(26,LOW);
    delay(300);
    digitalWrite(26,HIGH);
    count++;
    
  }
 
 if(count==1)
 {n=map(analogRead(15),0,1024,0,100);
   kp=n;
 }
 
 else if(count==2)
 { n=map(analogRead(15),0,1024,0,20);
   kd=n;
 }
 else if(count==3)
 { 
   n=map(analogRead(15),0,1024,0,20);
   ki=n;
 }
  
lcd.setCursor(3,0);
  lcd.print(kp);
  lcd.setCursor(10,0);
  lcd.print(kd);
  lcd.setCursor(5,1);
  lcd.print(ki);
  
  }while(count!=4);
}
