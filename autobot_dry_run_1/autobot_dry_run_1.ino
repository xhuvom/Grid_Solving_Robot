#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int s[]={0,0,0,0,0,0,0};
int bin[]={0,0,0,0,0,0,0};
int sum=0,mean=0;
int i=0;
float pos=0;
signed int error=0;

const float standard=3.5;
const int pwmL=110;
const int pwmR=200;

float left;
float right;
float prop,intg,deriv,last_prop;

int kp=40;
int ki=3;
int kd=7;

int n=0; 
int flag=0;
unsigned long t1,t2;
int count=0;


void setup()
{
  lcd.begin(16, 2);
  
  lcd.print("System Check...");
  lcd.setCursor(0,1);
  lcd.print("Please wait");
  delay(1000);
  
  lcd.clear();
  
   
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
   pinMode(53,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(26,OUTPUT);
  digitalWrite(32,HIGH);
  digitalWrite(26,HIGH);
  
  //init_pid_tune();
  //tune_pid();
  
  //s[0]=0;
  //bin[0]=0;
n=0;
}

void loop()
{
 lcd.clear();
 lcd.print(n);
 fwd();
  
}

void turn_dir(int k)
{
 
if((k==2)|(k==3)|(k==5)|(k==6)|(k==8)|(k==9))
{
  right_turn();
}
else
{
  line_follow();
}
}
void fwd()
{
  
 if(intersec_check())
 {
   
   t1=millis();
   if(flag==1)
 {
   n++;
 }
   flag=0;
   digitalWrite(26,LOW);
   if(n>8)
   {
     n=0;
   }
   turn_dir(n);
    }
    
    else
    {
   
   line_follow();
    }
    
 t2=millis();
 if(t2-t1>800)
 {
 flag=1;
 }
 else
 {
   flag=0;
 }
    delay(50);
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

int intersec_check()
{
  if((analogRead(8)<100)&&(analogRead(7)<300))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void turn_right()
{
  left=pwmL;
  right=pwmR;
  motor_turn();
  while((analogRead(8)>100)&&(analogRead(7)>300))
  {
     digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
  }
  
  while((analogRead(8)<100)&&(analogRead(7)<300))
  {
     digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
  }
  
}

void left_turn()
{
  left=pwmL;
  right=pwmR;
  motor_turn();
     digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
delay(350);

}

void right_turn()
{
  left=pwmL;
  right=pwmR;
  motor_turn();
     digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
delay(350);
}
  

void turn_left()
{
   
  left=pwmL;
  right=pwmR;
  motor_turn();
 
 
 while((analogRead(8)<100)&&(analogRead(7)<350))
  {
     digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
  } 
  
 
  while((analogRead(8)>100)&&(analogRead(7)>300))
  {
     digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
  }
 
}


void line_follow()
{
  digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
digitalWrite(26,HIGH);
   lcd.clear();
  mean=0;
  sum=0;
  sensor_read();
  PID_calc();
  motor_speed();
motor_turn();
}



void sensor_read()
{
  s[1]=analogRead(8)+150;
  for(i=2;i<=5;i++)
  {
    s[i]=analogRead(i-1);
    
  }
  s[6]=analogRead(7);
 // sensor_calib();
  for(i=1;i<=6;i++)
  { 
    bin[i]=adc(s[i]);
   // lcd.setCursor(i*3,0);
    //lcd.print(bin[i]);
    mean+=bin[i]*i;
    sum+=bin[i];
    pos=mean/sum; 
   // lcd.setCursor(3,1);
   // lcd.print(pos);
  }

 
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

void PID_calc()
{
  prop=pos-standard;
  intg=(intg/100)+prop;
  deriv=prop-last_prop;
  last_prop=prop;

  error=int((prop*kp)+(intg*ki)+(deriv*kd));
//lcd.setCursor(9,1);
  //  lcd.print(error);
}


void motor_speed()
{


  if(error<-255)
  {
    error=-255;
   
      


  }
   if(error>255)
  {
    error=255;
    
  }

  if(error>0)
  {
    left=pwmL-error;   // -error
    right=pwmR;


    // Left turn 

  }
  else
  {
    right=pwmL;
    left=pwmR-error;        // -error


  }
  
  

}



void serial_disp()
{
  for(i=1;i<=6;i++)
  {
    Serial.print(s[i]);
    Serial.print("\t");
    Serial.print(bin[i]);
    Serial.print("\t");
  }
  Serial.print(sum);
  Serial.print("\t\t");
  Serial.print(pos);
  Serial.print("\t\t");
  Serial.print(error);
  Serial.print("\t\t");
  Serial.print(left);
  Serial.print("\t\t");
  Serial.print(right);
  Serial.print("\t\t");

  Serial.print("\n\n");

  delay(20);

}
void sensor_calib()
{

  s[5]=s[5]-200;
  s[3]=s[3]-350;
  s[6]=s[6]+50;


}    

void motor_turn()
{

  analogWrite(9,left);
  analogWrite(8,right);

}

void motor_stop()
{
   digitalWrite(50,LOW);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,LOW);
}

