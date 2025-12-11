#include <VarSpeedServo.h>
VarSpeedServo fbig;
VarSpeedServo fukaz;
VarSpeedServo fsred;
VarSpeedServo fbezim;
VarSpeedServo fmizin;

int start_value[5]={400,310,320,360,300};

void setup() 
{
  fbig.attach(2);
  fukaz.attach(3);
  fsred.attach(4);
  fbezim.attach(5);
  fmizin.attach(6);
  //fbig.write();;
  fukaz.write(180,100);delay(5);
  fsred.write(180,100);delay(5);
  fbezim.write(180,100);delay(5);
  fmizin.write(0,100);delay(5);
  delay(3000);
}

void loop()
{
  int servo_angle[5];
 for(int i=0;i<4;i++)
 {
  servo_angle[i]=180-(start_value[i]-analogRead(i));
 }
 servo_angle[4]=(start_value[4]-analogRead(4));
  //fbig.write(servo_angle[0],100);delay(5);
  fukaz.write(servo_angle[1],100);delay(5);
  fsred.write(servo_angle[2],100);delay(5);
  fbezim.write(servo_angle[3],100);delay(5);
  fmizin.write(servo_angle[4],100);delay(5);
}
