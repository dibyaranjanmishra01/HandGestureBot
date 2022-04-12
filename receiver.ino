#include <VirtualWire.h>

#define en1 9
#define en2 10
#define in1 4
#define in2 5
#define in3 6
#define in4 7

int pitch,roll;
void setup()
{
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(en1,OUTPUT);
    pinMode(en2,OUTPUT);
    vw_set_rx_pin(11);
    vw_setup(2000);
    vw_rx_start();
    Serial.begin(9600);
    pitch = 0;
    roll = 0;
    digitalWrite(en1,HIGH);
    digitalWrite(en2,HIGH);
}

void forward(){
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
void reverse(){
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  }
void left()
{
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }

void right()
{
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  }
void stop()
{
  digitalWrite(in1,LOW); 
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  }

void loop()
{
  String temp="";
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN; 
  if (vw_get_message(buf, &buflen))
  {
    for (int i = 0; i < buflen; i++)
    {
      char ch = (char)buf[i];
      if(ch!=',') temp=temp+ch;
      else{
        pitch = temp.toInt();
        temp = "";
        continue;
        } 
    }
    roll = temp.toInt();
  }
//  Serial.print(pitch);
//  Serial.print("  ");
//  Serial.print(roll);
//  Serial.println();
  if(pitch>20) forward();
  else if(pitch<-20)reverse();
  else stop();
  if(roll>20) right();
  if(roll<-20) left();
}
