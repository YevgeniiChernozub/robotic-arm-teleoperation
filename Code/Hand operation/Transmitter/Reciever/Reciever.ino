#include <SPI.h>                                            // Подключаем библиотеку  для работы с шиной SPI
#include <nRF24L01.h>                                      // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку  для работы с nRF24L01+
#include <VarSpeedServo.h>
VarSpeedServo fbig;
VarSpeedServo fukaz;
VarSpeedServo fsred;
VarSpeedServo fbezim;
VarSpeedServo fmizin;
VarSpeedServo sixam[5];

int start_value[10]={0,310,320,360,300,450,205,360,150,180}; 
int servo_angle[10];
RF24           radio(49, 48);                               // Создаём объект radio   для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
int            data[10];                                   // Создаём массив для приёма данных
////////////////////////////////////////////////////////////
int bigFing(int bF)
{
  if(bF >= 250){return 70;}
  if(bF<250 && bF >=180){return 35;}
  if(bF<180){return 0;}
}
////////////////////////////////////////////
int elbow(int el)
{
  if(el >= 330){return 150;}
  if(el<330 && el >=220){return 100;}
  if(el<220){return 50;}
}
////////////////////////////////////////////
int spinShoulder(int sho)
{
  int res =sho - start_value[9];
  if(res>0)return 95+res*5;
  if(res>0)return 95-(res*(-5));
}
////////////////////////////////////////////
void setup(){
    Serial.begin(9600);
    delay(1000);
    radio.begin();                                              // Инициируем работу nRF24L01+
    radio.setChannel(120);                                     // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate     (RF24_2MBPS);                       // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
    radio.setPALevel      (RF24_PA_HIGH);                    // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
    radio.openReadingPipe (1, 0x1234567890LL);              // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
    radio.startListening  ();                              // Включаем приемник, начинаем прослушивать открытую трубу
//  radio.stopListening   ();                             // Выключаем приёмник, если потребуется передать данные
   if(radio.available()==0)Serial.println("not available");
  if(radio.available()==1)Serial.println(" available");
  /////////////////////////////////////////////НАСТРОЙКА ЛAДОНИ
  fbig.attach(2);
  fukaz.attach(3);
  fsred.attach(4);
  fbezim.attach(5);
  fmizin.attach(6);
  fbig.write(70,100);delay(5);
  fukaz.write(180,100);delay(5);
  fsred.write(180,100);delay(5);
  fbezim.write(180,100);delay(5);
  fmizin.write(0,100);delay(5);
  delay(3000);
  /////////////////////////////////////////////НАСТРОЙКА 6о МАНИПУЛЯТОРА
  for(int i=0;i<5;i++)
  {
    sixam[i].attach(14+i);
  }
  sixam[0].write(90,30);delay(5);
  sixam[1].write(96,30);delay(5);
  sixam[2].write(90,30);delay(2000);
  sixam[2].write(120,30);delay(2000);
  sixam[2].write(90,30);delay(2000);
  sixam[3].write(100,30);delay(5);
  sixam[4].write(95,30);delay(5);
  delay(4000);
  do
  {
    Serial.println("Didn`t get");
    delay(1);
  }while(radio.available() == 0);
  /*if(radio.available()==1)
  {
    Serial.println("got data ");
    radio.read(&data, sizeof(data));
    start_value[9] = data[9];
    start_value[8] = data[8];
Serial.println("Start data^ ");
     for(int i=0;i<10;i++)
        {
         Serial.print(String(data[i])+"  ");
        }Serial.println();
  }*/
}

void loop(){
   //for(int i=0;i<10000;i++)
  // {
    if(radio.available()==1)
   {   
     //Serial.println("available");
        int valBF;                                                  
        radio.read(&data, sizeof(data));
/////////////////////////////////////////////////////////////ПРЕОБРАЗОВАНИЕ ПОЛУЧЕННОЙ ИНФОРМАЦИИ                        
        /* for(int i=0;i<10;i++)
        {
         Serial.print(String(data[i])+"  ");
        }Serial.println();*/
        for(int i=1;i<7;i++)
        {
         servo_angle[i]=180-(start_value[i]-data[i]);
        }
        servo_angle[4]=(start_value[4]-data[4]);
        servo_angle[5]=(start_value[5]-data[5]);
        if(data[6]<195)servo_angle[6]=180;
        else servo_angle[6]=96;
        servo_angle[8]=(90+((data[8]-start_value[8]) * 2));
        Serial.println(String(data[8])+" "+String(servo_angle[8]));
        //servo_angle[9]=180-(start_value[i]-data[i]);
       // servo_angle[7]=(start_value[7]-data[7]);
//////////////////////////////////////////////////////////////// РАБОТА С ПАЛЬЦАМИ

        fbig.write(bigFing(data[0]),100);delay(5);   
        fukaz.write(servo_angle[1],100);delay(5);
        fsred.write(servo_angle[2],100);delay(5);
        fbezim.write(servo_angle[3],100);delay(5);
        fmizin.write(servo_angle[4],100);delay(5);
 
/////////////////////////////////////////////////////////////       // РАБОТА С ОСЯМИ        
        sixam[0].write(servo_angle[5],50);               // наклон кисти
        sixam[1].write(servo_angle[6],50);              //  поворот кисти
       sixam[3].write(elbow(data[7]),40);            //   локоть
       //if(i%5==0)
      // {
        sixam[2].write(servo_angle[8],40); delay(100);//}             //   плечо наклон
        
        //sixam[4].write(spinShoulder(data[9]),40);     //  плечо 
        //Serial.println(String(data[9])+" "+String(spinShoulder(data[9])));
    }
    
}
//}

