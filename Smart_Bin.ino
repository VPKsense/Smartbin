#include<Servo.h>
#include<EEPROM.h>

int bin = EEPROM.read(0);//0=non metal,1=metal
int ind=0;
Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(12,INPUT);//stop ind
  pinMode(11,INPUT);//sense ind
  pinMode(10,INPUT);//sense ind
  pinMode(9,INPUT);//sense ind
  
  servo.attach(7);
  servo.write(180);
  
  pinMode(5,INPUT);//sense IR

  
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);//anti
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}

void loop() {
  Serial.println(digitalRead(5));
  if(!digitalRead(5))
  {
    /*if(digitalRead(11) || digitalRead(10) || digitalRead(9))
    {
      ind=1;
      }*/
    delay(1500);
    if(digitalRead(11) || digitalRead(10) || digitalRead(9) && bin != 1)
    {
      Serial.println("Metal");
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      delay(1000); 
      while(!digitalRead(12));//stop sensor
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      servo.write(0);
      delay(1500);
      servo.write(180);
      bin=1;
      EEPROM.write(0,bin);
      //ind=0;
    }
    else if(digitalRead(11) || digitalRead(10) || digitalRead(9) && bin == 1)
    {
      Serial.println("Metal");
      servo.write(0);
      delay(1500);
      servo.write(180);
    }
    
    else if(bin != 0)
    {
     Serial.println("Not Metal");
     digitalWrite(3,HIGH);
     digitalWrite(4,LOW); 
     delay(1000); 
     while(!digitalRead(12));//stop sensor
     digitalWrite(3,LOW);
     digitalWrite(4,LOW);
     servo.write(0);
     delay(1500);
     servo.write(180);
     bin=0;
     EEPROM.write(0,bin);
    }

    else if(bin == 0 && !digitalRead(5))
    {
      Serial.println("Non Metal");
      servo.write(0);
      delay(1500);
      servo.write(180);
    }
   }
 }
