#include <LiquidCrystal.h>
#include <EEPROM.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(30, 32, 5, 4, 3, 2);
int s[]={0,0,0,0,0,0,0};
int bin[]={0,0,0,0,0,0,0};
int sum=0,mean=0;
int i=0;
float pos=0;
signed int error=0;

const float standard=25;
const int pwmL=90;
const int pwmR=90;

float left;
float right;
float prop,intg,deriv,last_prop;

int kp=10;//EEPROM.read(0); 
int ki=0;//EEPROM.read(1);  //5
int kd=0;//EEPROM.read(2);  //5

volatile int n=0; 
int flag=0;
unsigned long t1,t2;
int count=0;
int a=0;
int done1=1,done2=1,done3=1,done4=1,done5=1,done6=1,done7=1,done8=1;
void setup()
{
 //int kp=EEPROM.read(0); //40
//int ki=EEPROM.read(1);  //5
//int kd=EEPROM.read(2);  //5

  
  lcd.begin(16, 2);
  
  lcd.print("System Check...");
  lcd.setCursor(0,1);
  lcd.print("Please wait");
  delay(1000);
  
  lcd.clear();
  
  lcd.setCursor(4,0);
  lcd.print("n=");
  //lcd.clear();
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
   pinMode(53,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(44,OUTPUT);
  digitalWrite(38,HIGH);
  
  //init_pid_tune();
  //tune_pid();
  
  //s[0]=0;
  //bin[0]=0;

}

void loop()
{ 
  
  /*                            //////////         Line zig zag /////////// 
 while(n<2)
 {
   follow_nd_check();
  }
 if((n==2))
 {
 left_turn();
 line_correction();
 
 }
 while(n!=3)
 {
   follow_nd_check();
 }
 if((n==3))
 {
 left_turn();
 line_correction();
 
 }
 while(n!=5)
 {
   follow_nd_check();
 }
 if(n==5)
 {
 left_turn();
 line_correction();
 }
 while(n!=6)
 {
   follow_nd_check();
 }
 if(n==6)
 {
 left_turn();
 line_correction();
 n=0;
 }
 */
 /*
 switch(n)
 {
   case 1: if(done1)
   {
           left_turn();
           line_correction();
   }
   done1=0;   
           break;
   case 2: if(done2)
   {left_turn();
           line_correction();
   }
     done2=0;
     break;
   case 3: if(done3)
           {
             right_turn();
           line_correction();
           }
           done3=0;
           break;
   case 4: if(done4)
           {
           right_turn();
           line_correction();
           }
           done4=0;
           break;
   case 5: if(done5)
            {
              right_turn();
           line_correction();
            }
            done5=0;
           break;
   case 6: if(done6)
           {
             right_turn();
           line_correction();
           }
           done6=0;
           break;
   case 7: if(done7)
   {
          left_turn();
           line_correction();
   }
   done7=0;
           break;
   case 8: if(done8)
   {
           left_turn();
           line_correction();
           n=0;
   }
   done8=0;
           break;
   default: follow_nd_check();
            break;
 }
 */
 follow_nd_check();
  
}

void follow_nd_check()
{
  if(intersec_check())
 { t1=millis();
   if(flag==1)
 {
   n++;
 }
   flag=0;
   digitalWrite(44,LOW);
  // tone_gen();
  
 left_turn();
   
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
lcd.setCursor(7,0);
  lcd.print(n);

}

void line_correction()
{
  for(a=1;a<=4;a++)
   {
     line_follow();
     delay(50);
   }
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
 {
   n=map(analogRead(15),0,1024,0,100);
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

void right_turn()
{
  left=pwmL;
  right=pwmR;
  motor_turn();
digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
delay(420);
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
  while((analogRead(8)>100)&&(analogRead(7)>300))
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
/*
while(analogRead(15)<200)
{
     digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
}
while(analogRead (15)>200)
{
     digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
}
*/
       digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
delay(200);

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
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
  } 

  while((analogRead(8)>100)&&(analogRead(7)>300))
  {
      digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
  }
   
 
}


void line_follow()
{
   digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
digitalWrite(44,HIGH);
  // lcd.clear();
  mean=0;
  sum=0;
  sensor_read();
  PID_calc();
  motor_speed();
motor_turn();
}



void sensor_read()
{
  /*s[1]=analogRead(8)+150;
  for(i=2;i<=5;i++)
  {
    s[i]=analogRead(i-1);
    
  }
  s[6]=analogRead(7);
 // sensor_calib();
  */
  for(i=1;i<=4;i++)
  { 
    bin[i]=adc(s[i]);
   // lcd.setCursor(i*3,0);
    //lcd.print(bin[i]);
    mean+=bin[i]*i*10;
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
   
 

  analogWrite(9,right);
  analogWrite(8,left);

}

void motor_stop()
{
   digitalWrite(50,LOW);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,LOW);
}

void tone_gen()
{
  
  tone(11,11000,300);
  delay(50);
  noTone(11);
  delay(50);
  
}

