#include <Encoder.h>

#include <LiquidCrystal.h>

const int pingPin = 31;
LiquidCrystal lcd(30, 32, 5, 4, 3, 2);
int s[]={0,0,0,0,0,0,0};
int bin[]={0,0,0,0,0,0,0};
int sum=0,mean=0;
int i;
float pos=0;
float error=0;
int t_flag=1;
const float standard=25;
const int pwmL=100;
const int pwmR=100;
//char course[7]={'F','F','R','L','F','R','S'};
char course[10]={'F','R','F','L','F','F','L','S'};//,'F','S'};
signed left;
signed right;
float prop,intg,deriv,last_prop;

const int kp=10;
const int ki=0;
const int kd=4;
Encoder myEnc(20, 21);
int a=0; 
int count=0;
int t1,t2;
int flag=0,n=0;

long oldPosition  = -999;
void setup()
{
  lcd.begin(16, 2);
  //Serial.begin(9600);
  lcd.print("Initiating Robot");
  delay(1000);
  lcd.clear();
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);
   pinMode(37,OUTPUT);
    pinMode(42,OUTPUT);
    digitalWrite(37,HIGH);
    digitalWrite(42,HIGH);
 // s[0]=0;
 // bin[0]=0;
//Serial.begin(9600);
 

//fwd();


}

void loop()
{
  
  while(n<=7)
{
  course_plan(course[n]);
}
  
/*
switch(n)
{
  
   case 1: follow_nd_check();
      
           break;
   case 2: follow_nd_check();
     break;
   case 3:if(done_3==1)
   {
     rotate_right();
     done_3=0;
     line_correction(); 
   }
   
   follow_nd_check();
           break;
   case 4:
   done_3=1;
   if(done_4==1)
  { 
   rotate_right();
   done_4=0;
   line_correction(); 
  }
   follow_nd_check();
           break;
   case 5: 
   done_4=1;
   follow_nd_check();
   break;
           
   case 6: 
   if(done_6==1)
   {
     rotate_left();
     done_6=0;
     line_correction(); 
   }
           break;
   case 7: 
   done_6=1;
   if(done_7==1)
   {
     rotate_left();
     done_7=0;
     line_correction(); 
   }
   follow_nd_check();
   
           break;
   case 8: 
   done_7=1;
   follow_nd_check();
           break;
  case 9: follow_nd_check();
           break;
   default: follow_nd_check();
            break;
 }
 
 */
//follow_nd_check();
/*
if(intersec_check())
{
  digitalWrite(42,LOW);
  lcd.clear();
   lcd.setCursor(0,1);
  lcd.print(analogRead(12));
  lcd.setCursor(13,1);
  lcd.print(analogRead(9));

}
else
{
  digitalWrite(42,HIGH);
   lcd.clear();
   lcd.setCursor(0,1);
  lcd.print(analogRead(12));
  lcd.setCursor(13,1);
  lcd.print(analogRead(9));

}
*/
 

}


void course_plan(char ch)
{
  switch(ch)
  {
    case 'F': follow_nd_check();
              break;
    case 'L':
    if(t_flag==1)
    {
      t_flag=0;
      rotate_left();
             line_correction();
    }
    follow_nd_check();
             break;
    case 'R':if(t_flag==1)
    {
      t_flag=0;
      rotate_right();
             line_correction();
    }
    follow_nd_check();
             break;
     case 'S':motor_stop();
              break;
              
      default:follow_nd_check();
               break;
  }
}

void rotate_right()
{
analogWrite(8,90);
analogWrite(9,90);  
  while(count<31)
  {
  //oldPosition  = -999;
digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    count++;
    lcd.setCursor(7,0);
    lcd.print(count);
}
  }
  
  oldPosition  = -999;
  count=0;
 
}
void rotate_left()
{
analogWrite(8,90);
analogWrite(9,90);  
  while(count<34)
  {
  //oldPosition  = -999;
digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    count++;
    lcd.setCursor(7,0);
    lcd.print(count);
}
  }
  
  oldPosition  = -999;
  count=0;
 
}



void follow_nd_check()
{
  
  if(intersec_check())
 {
   
   t1=millis();
   if(flag==1)
 {
   n++;
   t_flag=1;
   digitalWrite(42,LOW);
   delay(50);
   digitalWrite(42,HIGH);
 }
   flag=0;
   
  // tone_gen();
  
//rotate_left ();

 //line_correction(); 
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
delay(10);
}

void line_correction()
{
  for(a=1;a<=2;a++)
   {
     line_follow();
     delay(200);
   }
}



int intersec_check()
{
  if((analogRead(12)<200)&&(analogRead(9)<70))
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
  left=120;
  right=120;
  motor_turn();
while(analogRead(14)<200)
  {
  digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
  }

while(analogRead(14)>200)
  {
      digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);

  }
  
   
  
  
}

void left_turn()
{
  left=120;
  right=120;
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
*/ digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
delay(300);

}

void right_turn()
{
  left=100;
  right=100;
  motor_turn();
   digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
  delay(100);
}
void turn_left()
{
   
  left=120;
  right=120;
  motor_turn();
 
 
  while((analogRead(8)<100)&&(analogRead(9)<300))
  {
      digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
  } 
//delay(100);
  while((analogRead(8)<100)&&(analogRead(9)<300))
  {
      digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH); 
  }  
}


void line_follow()
{  digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
  digitalWrite(42,HIGH);
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
  
  for(i=1;i<=4;i++)
  {
    s[i]=analogRead(i);
    
  }
  
 // sensor_calib();
  for(i=1;i<=4;i++)
  { 
    
    bin[i]=adc(s[i]);
    
   // lcd.setCursor(i*3,0);
   // lcd.print(bin[i]);
    mean+=bin[i]*i*10;
    sum+=bin[i];
    pos=float(mean/sum); 
    //lcd.setCursor(3,1);
    //lcd.print(pos);
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

  error=(prop*kp)+(intg*ki)+(deriv*kd);
  
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

  if(error<0)
  {
    left=pwmL-error;   // -error
    right=pwmR;//+(error/2);
    if(right<0)
    {
      right=0;
    }


    // Right turn 

  }
  else
  {
    right=pwmR+error;
    left=pwmL;//-(error/2);        // -error

 if(left<0)
 {
   left=0;
 }
  }
  
  

}



void serial_disp()
{
  for(i=1;i<=4;i++)
  {
    //Serial.print(s[i]);
    //Serial.print("\t");
    Serial.print(bin[i]);
    Serial.print("\t");
  }
  Serial.print(mean);
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
  /*
   digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
 */

  analogWrite(9,right);
  analogWrite(8,left);
  lcd.setCursor(0,1);
  lcd.print(analogRead(8));
  lcd.setCursor(13,1);
  lcd.print(analogRead(9));

}
void fwd()
{
  digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
}

void motor_stop()
{
   digitalWrite(50,LOW);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,LOW);
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

void beep()
{
  int x;
  for(x=0;x<=3;x++)
  {
  digitalWrite(42,LOW);
  delay(50);
  digitalWrite(42,HIGH);
  delay(50);
  }
}
