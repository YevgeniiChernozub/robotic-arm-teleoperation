#include <VarSpeedServo.h>
VarSpeedServo sixam[5];


int start_value[5]={400,310,320,360,300};

void setup() 
{
  for(int i=0;i<5;i++)
  {
    sixam[i].attach(14+i);
  }
  sixam[0].write(90,30);delay(5);
  sixam[1].write(96,30);delay(5);
  sixam[2].write(90,30);delay(5);
  sixam[3].write(90,30);delay(5);
  sixam[4].write(95,30);delay(5);
  delay(3000);
}

void loop()
{
  sixam[0].write(180,30);delay(2000);
  sixam[0].write(0,30);delay(2000);
  sixam[0].write(90,30);delay(2000);
  delay(2000);
  sixam[1].write(180,30);delay(2000);
  sixam[1].write(0,30);delay(2000);
  sixam[1].write(96,30);delay(2000);
  delay(2000);
  sixam[2].write(140,30);delay(2000);
  sixam[2].write(40,30);delay(2000);
  sixam[2].write(95,30);delay(2000);
  delay(2000);
  sixam[3].write(180,30);delay(2000);
  sixam[3].write(0,30);delay(2000);
  sixam[3].write(95,30);delay(2000);
  delay(2000);
  sixam[4].write(180,30);delay(2000);
  sixam[4].write(0,30);delay(2000);
  sixam[4].write(95,30);delay(2000);
  delay(2000);
/*  int servo_angle[5];
 for(int i=0;i<4;i++)
 {
  servo_angle[i]=180-(start_value[i]-analogRead(i));
 }
 servo_angle[4]=(start_value[4]-analogRead(4));
  //fbig.write(servo_angle[0],100);delay(5);
  fukaz.write(servo_angle[1],100);delay(5);
  fsred.write(servo_angle[2],100);delay(5);
  fbezim.write(servo_angle[3],100);delay(5);
  fmizin.write(servo_angle[4],100);delay(5);*/
}
