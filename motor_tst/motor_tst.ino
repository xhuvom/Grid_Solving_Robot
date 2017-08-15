signed val=-10;
void setup() {
  // put your setup code here, to run once:
pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);
digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);

analogWrite(8,0); // left
analogWrite(9,100);
}

void loop() {
  fwd();
  // put your main code here, to run repeatedly: 
//right();
/*delay(1000);
left();
delay(1000);
right();
delay(1000);
back();
delay(1000);
*/
}


void stop()
{
   digitalWrite(50,LOW);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,LOW);
}

void back()
{
  
     digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);


}

void fwd()
{
  digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
}
void left()
{
  digitalWrite(50,HIGH);
digitalWrite(51,LOW);
digitalWrite(52,LOW);
digitalWrite(53,HIGH);
}

void right()
{
  digitalWrite(50,LOW);
digitalWrite(51,HIGH);
digitalWrite(52,HIGH);
digitalWrite(53,LOW);
}
