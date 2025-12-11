#include <VarSpeedServo.h>
VarSpeedServo g;

void setup() {
 g.attach(5);
}

void loop() {
 g.write (90,30 );
}
