int s[]={0,0,0,0,0,0,0};
int sum=0,mean=0,i;
float pos=0;
signed float error;
float standard=4;

void setup()
{
  Serial.begin(9600);    //boud rate??
}

void loop()
{ 
  avg=0;
  sum=0;
  pos=0;
  Serial.print(i);
  Serial.print("\t\t");

  Serial.print(s[i]);
  Serial.print("\t");
  
  Serial.print(sum);
  Serial.print("\t\t");

  Serial.print(avg);
  Serial.print("\t\t");
  Serial.print(pos); 
  Serial.print("\n");

 
}
delay(1000);
Serial.print("\n\n\n");
}

void sensor_read()
{
  for(i=1;i<=7;i++)
{
  s[i]=adc(analogRead(i-1));
  mean+=s[i]*i;
  sum+=s[i];
  pos=mean/sum; 
}
}

int adc(int t)
{
  if(t<=550)
  {
    return 0;
  }
  else
  {
    return 1;
  }
  
}

void PID_calc(float)
{
  float kp;
  error=pos-standard;
  if(error>0)
  {
    while(error!=0)
    {
      
      motor_right();
    kp=(255*error)/standard;
    
    analogWrite(13,kp);                           //  Motor thereshold val for PWM   and speed calib
    
     analogWrite(12,kp);
     
  }
  else if(error<0)
    {
    while(error!=0)
    {
    motor_left();
      kp=(255*error)/standard;
      
  analogWrite(13,kp);                           //  Motor thereshold val for PWM   and speed calib
    
     analogWrite(12,kp);
    }
  
  }
  else
  
  void motor_fwd()
  {
    digitalWrite(31,HIGH);
    digitalWrite(33,LOW);
    digitalWrite(35,HIGH);
    digitalWrite(37,LOW);
  }
  void motor_left()
  {
     digitalWrite(31,HIGH);
    digitalWrite(33,LOW);
    digitalWrite(35,LOW);
    digitalWrite(37,HIGH);
  }
  
  void motor_right()
  {
     digitalWrite(31,LOW);
    digitalWrite(33,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(37,LOW);
  }
              
  
