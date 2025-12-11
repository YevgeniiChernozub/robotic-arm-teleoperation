////////////////////////Обьявление контактов под сервы(E=ENGINE)
#define E_pinBolPal 23//7
#define E_pinUkazPal 27//5//
#define E_pinSredPal 25//6//
#define E_pinBezimPal 31//3
#define E_pinMizinPal 29//4
#define E_Kist 33//2
#define E_LokotLev 37//1
#define E_LokotPrav 35//0
//#define E_PlechLev 39
//#define E_PlechPrav 41
//int lp = 75,rp=105;
////////////////////////Обьявление Переменных
int ReadBolP;
int ReadUkazP;
int ReadSredP;
int ReadBezimP;
int ReadMizinP;
int ReadLokot;
int ReadVr;
int ReadPlech;
///////////////////////////////////////////////ПОДКЛЮЧЕНИЕ библиотек

#include <VarSpeedServo.h>
VarSpeedServo BolPal;
VarSpeedServo Ukazpal;
VarSpeedServo SredPal;
VarSpeedServo BezimPal;
VarSpeedServo MizinPal;
VarSpeedServo VrKisti;
VarSpeedServo LokLev;
VarSpeedServo LokPrav;
//VarSpeedServo PlechLev;
//VarSpeedServo PlechPrav;

#include <SoftwareSerial.h>
const byte HC12RxdPin = 10;                  // Линия приема данных на HC12
const byte HC12TxdPin = 11;                  // Линия передачи данных на HC12
SoftwareSerial HC12(HC12TxdPin,HC12RxdPin); // Инициализация последовательного порта для HC12
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Настройка
void setup() {
  HC12.begin(9600);
  Serial.begin(9600);
  BolPal.attach(E_pinBolPal);//Большой палец
  Ukazpal.attach(E_pinUkazPal);//Указательный палец
  SredPal.attach(E_pinSredPal);//Средний палец
  //BezimPal.attach(E_pinBezimPal);//Безимянный палец
  MizinPal.attach(E_pinMizinPal);//Мизинец
  LokLev.attach(E_LokotLev);
  LokPrav.attach(E_LokotPrav);
  //VrKisti.attach(E_Kist);
  //PlechLev.attach(E_PlechLev);
  //PlechPrav.attach(E_PlechPrav);
  BolPal.write(120,255);//Большой палец
  delay(500);
  Ukazpal.write(120,255);//Указательный палец
  delay(500);
  SredPal.write(120,255);//Средний палец
  delay(500);
  //BezimPal.write(120,255);//Безимянный палец
 // delay(500);
  MizinPal.write(120,255);//Мизинец
  delay(500);
  LokLev.write(125,40);
  LokPrav.write(65,40);
  delay(5000);
  //VrKisti.write(0,20);
  //delay(1000);
  //VrKisti.write(180,20);
  //delay(1000);
  
  //PlechLev.write(lp);PlechPrav.write(rp);delay(500);
}
void  loop() 
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
    
  ReadBolP=dat[1];
  ReadUkazP=dat[2];
  ReadSredP=dat[3];
  ReadBezimP=dat[3];
  ReadMizinP=dat[5];
  ReadLokot=dat[6];
  //ReadVr=dat[7];
  //ReadPlech=dat[9];
  /////////////////////////////////////////////////////////Скетч для плеча
 //if( ReadPlech == 1) {PlechLev.write(lp+25);PlechPrav.write(rp-25); delay(5);}
 //if( ReadPlech == -1){PlechLev.write(lp-25);PlechPrav.write(rp+25); delay(5);}
  /////////////////////////////////////////////////////////Скетч для кисти
 //if( ReadVr >= 400 ||  ReadVr == 0) { VrKisti.write(85,20); delay(5); }
 //if( ReadVr >= 200 &&  ReadVr < 400){ VrKisti.write(50,20); delay(5); }
 //if( ReadVr < 200 &&  ReadVr > 90)  { VrKisti.write(20,20); delay(5); }
  /////////////////////////////////////////////////////////Скетч для локтя

  if( ReadLokot >= 400 ||  ReadLokot == 0) { LokLev.write(125,40); LokPrav.write(65,40); delay(5);}
  if( ReadLokot >= 200 &&  ReadLokot < 400){ LokLev.write(50,40); LokPrav.write(130,40); delay(5);}
  if( ReadLokot < 200 &&  ReadLokot > 90)  { LokLev.write(20,40); LokPrav.write(160,40); delay(5);}
  
  /////////////////////////////////////////////////////////Скетч для большого пальца
  
  if(ReadBolP >= 340 || ReadBolP == 0) {BolPal.write(120,255);  delay(5);}
  if(ReadBolP >= 260 && ReadBolP < 340){BolPal.write(60,255);   delay(5);}
  if(ReadBolP < 260 && ReadBolP > 90)  {BolPal.write(0,255);    delay(5);}
  
  ////////////////////////////////////////////////////////Скетч для указательного пальца
  
  if(ReadUkazP >= 275 || ReadUkazP == 0) { Ukazpal.write(120,255);  }
  if(ReadUkazP >= 170 && ReadUkazP < 275){ Ukazpal.write(60,255);   }
  if(ReadUkazP < 170 && ReadUkazP > 90)  { Ukazpal.write(0,255);    }
  
  ///////////////////////////////////////////////////////////Скетч для среднего пальца
  
  if(ReadSredP >= 270 || ReadSredP == 0) { SredPal.write(120,255);  }
  if(ReadSredP >= 200 && ReadSredP < 270){ SredPal.write(60,255);   }
  if(ReadSredP < 200 && ReadSredP > 90)  { SredPal.write(0,255);    }
  
  //////////////////////////////////////////////////////////Скетч для безимянного пальца
  
  //if(ReadBezimP >= 310 || ReadBezimP == 0) { BezimPal.write(120,255);}
  //if(ReadBezimP >= 210 && ReadBezimP < 310){ BezimPal.write(60,255);   }
 // if(ReadBezimP < 210 && ReadBezimP > 90)  { BezimPal.write(0,255);   }
  
  //////////////////////////////////////////////////////////Скетч для мизинца
  
  if(ReadMizinP >= 280 || ReadMizinP == 0) { MizinPal.write(120,255); }
  if(ReadMizinP >= 180 && ReadMizinP < 280){ MizinPal.write(60,255);  }
  if(ReadMizinP < 180 && ReadMizinP > 90)  { MizinPal.write(0,255);  }
 /*for(int i=0;i<11;i++)
    {
      Serial.print(String(dat[i])); Serial.print(" ");
    }Serial.println(" ");*/
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
  default:
  {
    //Serial.println("DEFAULT");
    break;
  }
 }
}
