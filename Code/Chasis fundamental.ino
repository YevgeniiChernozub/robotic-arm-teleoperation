int motor_L1,motor_L2,input_L;
int motor_R1,motor_R2,input_R;
void setup_motor_system(int L1,int L2,int iL,int R1,int R2,int iR)
{
  motor_L1=L1,motor_L2=L2,input_L=iL;
  motor_R1=R1,motor_R2=R2,input_R=iR;
  pinMode(motor_L1,OUTPUT);
  pinMode(motor_L2,OUTPUT);
  pinMode(input_L,OUTPUT);
  pinMode(motor_R1,OUTPUT);
  pinMode(motor_R2,OUTPUT);
  pinMode(input_R,OUTPUT);
  }
  void setspeed(int LeftSpeed,int RightSpeed)
  {
    analogWrite(input_L,LeftSpeed);
    analogWrite(input_R,RightSpeed);
  }
  void forward()
  {
    digitalWrite(motor_L1,HIGH);
    digitalWrite(motor_L2,LOW);
    digitalWrite(motor_R1,LOW);
    digitalWrite(motor_R2,HIGH);
  }
void forward_left()
  {
    digitalWrite(motor_L1,LOW);
    digitalWrite(motor_L2,LOW);
    digitalWrite(motor_R1,LOW);
    digitalWrite(motor_R2,HIGH);
  }
  void forward_right()
  {
    digitalWrite(motor_L1,HIGH);
    digitalWrite(motor_L2,LOW);
    digitalWrite(motor_R1,LOW);
    digitalWrite(motor_R2,LOW);
  }
  void backward()
  {
    digitalWrite(motor_L1,LOW);
    digitalWrite(motor_L2,HIGH);
    digitalWrite(motor_R1,HIGH);
    digitalWrite(motor_R2,LOW);
  }
  void _stop()
  {
    digitalWrite(motor_L1,LOW);
    digitalWrite(motor_L2,LOW);
    digitalWrite(motor_R1,LOW);
    digitalWrite(motor_R2,LOW);
  }
/////////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
const byte HC12RxdPin = 3;                  // Линия приема данных на HC12
const byte HC12TxdPin = 4;                  // Линия передачи данных на HC12
SoftwareSerial HC12(HC12TxdPin,HC12RxdPin); // Инициализация последовательного порта для H
int moving;
void setup() 
{
    setup_motor_system(12,13,11,8,9,10);
    setspeed(0,0);
    HC12.begin(9600);
    Serial.begin(9600);
}

void loop() 
{
 String swch;
int trig;
do{delay (5);}while(HC12.available()==0);
if(HC12.available())
{                            
 swch = HC12.readString();
 Serial.print(swch);
 if(swch == "1")trig=1;
 if(swch == "2")trig=2;
 //Serial.println("");
}
 switch (trig)
 { 
  case 1:
  {
    break;
  }
  case 2:
  {
    int h=1;
    while(h==1)
    {
    String mas[11];int dat[11];
    do{delay (1);}while(HC12.available()==0);
     if(HC12.available()>0)
    { 
      h=1;
    String input;                            
    input = HC12.readString();
    /////////////////////////////////////////////////////
    int j=0;
    for(int i=0;i<11;i++)
    {
      int p=0;
      do
      {
       mas[i]+=input[j];
        j++;
      }while(isSpace(input[j]) == 0);
    }
    for(int i=0;i<11;i++)
    {
      dat[i]=mas[i].toInt();
    }
    
    for(int i=0;i<11;i++)
    {
      Serial.print(dat[i]);Serial.print(" ");
    }Serial.println();
    moving= dat[8];
    if(moving==1)
    {
        forward();setspeed(100,100);delay(1000);_stop();
    }
    if(moving==2)
    {
        backward();setspeed(100,100);delay(1000);_stop();
    }
    if(moving==3)
    {
        forward_left();setspeed(100,100);delay(1000);_stop();
    }
    if(moving==4)
    {
      forward_right();setspeed(100,100);delay(1000);_stop();
    }
    Serial.println("Compleeted");    
    }
    if(HC12.available()==0)
    {
      delay(500);
      if(HC12.available()==0)
      { 
        h=0;
       Serial.println("Process Ended");
      }  
    }
    } 
    break; 
 }
}
}

