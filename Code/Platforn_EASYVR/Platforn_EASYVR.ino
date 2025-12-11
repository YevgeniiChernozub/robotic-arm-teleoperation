#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей

#define indication 11

#include <SoftwareSerial.h>
SoftwareSerial softSerial(2,3); // В данном случае вывод TX модуля подключается к выводу 2 Arduino, а вывод RX модуля к выводу 3 Arduino.
#include "Arduino.h"
#include "SoftwareSerial.h"
SoftwareSerial port(12,13);
#include "EasyVR.h"
EasyVR easyvr(port);

//////////////////////////////EASYVR//////////////////////////

/////////////ENUM EASYVR////////////////////////////////////////////
enum Groups
{
GROUP_1  = 1,
};
enum Group1
{
G1_FORWARD = 0,
G1_REVERSE = 1,
G1_LEFT = 2,
G1_RIGHT = 3,
G1_FINISH = 4,
};
int8_t group, idx;
//////////////////////////////////////////////////////////
/////////////////////////////BLUETOOTH////////////////////
//#include <SoftwareSerial.h>
//SoftwareSerial softSerial(2,3); // В данном случае вывод TX модуля подключается к выводу 2 Arduino, а вывод RX модуля к выводу 3 Arduino.


int motor_L1,motor_L2,input_L;
int motor_R1,motor_R2,input_R;

int set_Speed = 150;
///////////////////////////////////////////////////////////////////////////
////////////////////////////FUNCTIONS//////////////////////////////////////

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
void f_left()
  {
    digitalWrite(motor_L1,LOW);
    digitalWrite(motor_L2,HIGH);
    digitalWrite(motor_R1,LOW);
    digitalWrite(motor_R2,HIGH);
  }
  void f_right()
  {
    digitalWrite(motor_L1,HIGH);
    digitalWrite(motor_L2,LOW);
    digitalWrite(motor_R1,HIGH);
    digitalWrite(motor_R2,LOW);
  }
  void backward()
  {
    digitalWrite(motor_L1,LOW);
    digitalWrite(motor_L2,HIGH);
    digitalWrite(motor_R1,HIGH);
    digitalWrite(motor_R2,LOW);
  }
  void Stop()
  {
    digitalWrite(motor_L1,LOW);
    digitalWrite(motor_L2,LOW);
    digitalWrite(motor_R1,LOW);
    digitalWrite(motor_R2,LOW);
  }
  
void action()
{
  switch (group)
    {
      case GROUP_1:
      switch (idx)
      {
        case G1_FORWARD:
        setspeed(set_Speed,set_Speed);
        forward();delay(2000);Stop();
        break;
        
        case G1_REVERSE:
        setspeed(set_Speed,set_Speed);
        backward();delay(2000);Stop();
        break;
        
        case G1_LEFT:
        setspeed(set_Speed,set_Speed);
        f_left();delay(1000);Stop();
        break;
        
        case G1_RIGHT:
        setspeed(set_Speed,set_Speed);
        f_right();delay(1000);Stop();
        break;

        case G1_FINISH:
        softSerial.begin(9600);
        port.end();
        lcd.clear();
        break;
      }
      break;
    }
}
void led_mv(char a)
{
  if(a=='m')
  {
    for(int i=0;i<5;i++)
    {
      digitalWrite(indication,HIGH);
      delay(100);
      digitalWrite(indication,LOW);
    }
  }
  if(a=='v')
  {
      digitalWrite(indication,HIGH);
      delay(2000);
      digitalWrite(indication,LOW);
  }
}
void end_m()
{
      for(int i=0;i<255;i++)
      {
       analogWrite(indication,i);delay(5);
       
      }
      for(int i=255;i>0;i++)
      {
       analogWrite(indication,i);delay(5);
       
      }
      digitalWrite(indication,LOW);
}
void end_v()
{
  for(int i=0;i<2;i++)
  {
      for(int i=0;i<255;i++)
      {
       analogWrite(indication,i);
       delay(5);
      }
      for(int i=255;i>0;i++)
      {
       analogWrite(indication,i);
       delay(5);
      }
      delay(100);
  }digitalWrite(indication,LOW);
}
  /////////////////////////////SETUP FUNCTIONS///////////////////////////////////////
  /////////////////////////////SETUP FUNCTIONS//////////////////////////////////////
  void setup()
  {
    lcd.init();                     
    lcd.backlight();// Включаем подсветку дисплея
  
    pinMode(indication,OUTPUT);
    //////////////////////////BLUTOTH SETUP
    softSerial.begin(9600); // Инициируем передачу данных по программной шине UART на скорости 38400 (между модулем и Arduino)
    Serial.begin(9600);  // Инициируем передачу данных по аппаратной шине UART на скорости 9600 (между Arduino и компьютером)
    //////////////////////////PLATFORM SETUP
    setup_motor_system(5,6,9,7,8,10);
    setspeed(0,0);
    ////////////////////////EASYVR SETUP
    
    digitalWrite(indication,HIGH);
      delay(100);
      digitalWrite(indication,LOW);
      
Serial.println("COMPLEEEEEEEEEEET");
  }
  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////LLLOOOOPPPP///////////
void loop()
{     
      
      char trigger;
      char reg;
      lcd.print("CHOOSE REGIME");
        lcd.setCursor(0, 1);
        lcd.print("( < or x )");
      
      do
      {
        delay(1);
      }while(softSerial.available()==0);
      if (softSerial.available()==1)
      {
        lcd.clear();
          trigger=(char)softSerial.read();Serial.println(trigger);
          led_mv(trigger);
          switch (trigger)
          {
            
              ////////////////////////////////////MANUAL CONTROL
              case 'm':
              { 
                lcd.clear();
                lcd.print("MANUAL CONTROL");
                  do
                  {
                   
                  reg = (char)softSerial.read(); 
                  
                  switch (reg)
                  {
                   case 'f':
                   do
                   {
                   setspeed(set_Speed,set_Speed);
                   forward();Serial.println(reg);
                   }while(softSerial.available()==0);
                   
                   case 'l':
                   do
                   {
                   setspeed(set_Speed,set_Speed);
                   f_left();Serial.println(reg);
                   }while(softSerial.available()==0);
                   
                   case 'r':
                   do
                   {
                   setspeed(set_Speed,set_Speed);
                   f_right();Serial.println(reg);
                   }while(softSerial.available()==0);
                   
                   case 'b':
                   do
                   {
                   setspeed(set_Speed,set_Speed);
                   backward();Serial.println(reg);
                   }while(softSerial.available()==0);
                   
                   case 's':
                   Stop();
                   }
                 
                  
              }while(reg != 'B');lcd.clear();break; //end_m();
                }
              
              ////////////////////////////////////////////////////VOISE CONTROL
              case 'v':
              {
                int voise = 1;
                lcd.print("VOISE CONTROL");
                //int ending=0;
                softSerial.end();
                port.begin(9600);
                if (!easyvr.detect())
                {
                digitalWrite(indication,HIGH);
                for (;;);
                }
                easyvr.setPinOutput(EasyVR::IO1, LOW);
                digitalWrite(indication,LOW);
                Serial.println("EasyVR detected!");
                easyvr.setTimeout(5);
                easyvr.setLanguage(EasyVR::ENGLISH);
                  do
                  {
                    if (!easyvr.detect())
                    {
                    voise == 0;
                    break;
                    }
                    easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)
                    digitalWrite(indication,HIGH);
                    lcd.clear();
                    lcd.print("SAY SOMETHING");
                    Serial.print("Say a command in Group");
                    Serial.println(group);
                    easyvr.recognizeCommand(group);
                    
                    do{}while (!easyvr.hasFinished());
                    
                    easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off
                    digitalWrite(indication,LOW);
                    lcd.clear();
                    lcd.print("DETECTION");
                    idx = easyvr.getWord();
                    ///////////////+- JUMPER FUNKTION
                    idx = easyvr.getCommand();
                    if (idx >= 0)
                    {
                    // print debug message
                    uint8_t train = 0;
                    char name[32];
                    Serial.print("Command: ");
                    Serial.print(idx);
                    if (easyvr.dumpCommand(group, idx, name, train))
                    {
                    Serial.print(" = ");
                    Serial.println(name);
                    }
                    else
                    Serial.println();
                    easyvr.playSound(0, EasyVR::VOL_FULL);
                    // perform some action
                    action();
                    }
                    else // errors or timeout
                    {
                    if (easyvr.isTimeout())
                    lcd.clear();
                    lcd.print("Timed out,");
                    lcd.setCursor(3, 1);
                    lcd.print("try again…");
                    Serial.println("Timed out, try again…");
                    int16_t err = easyvr.getError();
                    if (err >= 0)
                    {
                    Serial.print("Error");
                    Serial.println(err, HEX);
                    }
                    
                    group = GROUP_1;
                    } 
                    //port.end();
                    
                    //softSerial.begin(9600);
                    /*digitalWrite(indication,HIGH);
                    softSerial.setTimeout(2);
                    for(int i=0;i=3;i++)
                    {
                      if((char)softSerial.read() == 'B')
                      {ending=1;break;}
                      delay(1000);
                    }
                    digitalWrite(indication,LOW);*/
                  }while(voise == 1);
                  //end_v();
                  lcd.clear();
                  break;  
              }
              default:
              
              break;
            } 
          }
} 
      
  
