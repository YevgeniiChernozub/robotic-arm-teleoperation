#define E_PlechLev 6
#define E_PlechPrav 7
#define E_Vrash 5
int lp = 75,rp=105,vr=90;
int ReadPlech;
int ReadVrash;
#include <VarSpeedServo.h>
VarSpeedServo PlechLev;
VarSpeedServo PlechPrav;
VarSpeedServo Vrash;


#include <SoftwareSerial.h>
const byte HC12RxdPin = 10;                  // Линия приема данных на HC12
const byte HC12TxdPin = 11;                  // Линия передачи данных на HC12
SoftwareSerial HC12(HC12TxdPin,HC12RxdPin); // Инициализация последовательного порта для H
void setup() 
{
  PlechLev.attach(E_PlechLev);
  PlechPrav.attach(E_PlechPrav);
  Vrash.attach(E_Vrash);
    HC12.begin(9600);
    Serial.begin(9600);
    PlechLev.write(0,40);PlechPrav.write(180,40);delay(2000); 
    PlechLev.write(lp,40);PlechPrav.write(rp,40);delay(2000);
    Vrash.write(vr,40);delay(1500);
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
    ReadPlech=dat[9];
    ReadVrash=dat[10];
    Serial.println("ReadPlech         "+String(ReadPlech));
    Serial.println("ReadVrash         "+String(ReadVrash));   
  /////////////////////////////////////////////////////////Скетч для плеча
 if( ReadPlech == 1) {lp-=25;rp+=25;}
 if( ReadPlech == -1){lp+=25;rp-=25;}
 if( ReadVrash == 1) {vr+=30;}
 if( ReadVrash == -1){vr-=30;}  
  PlechLev.write(lp,40);PlechPrav.write(rp,20);
  Vrash.write(vr,50);delay(2000);
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

