void setup() {
Serial.begin(9600);
}
int a[8];
void loop() {
  for(int i=0;i<8;i++)
  {
    a[i]=analogRead(i);
  }
   for(int i=0;i<8;i++)
  {
    Serial.print(a[i]);Serial.print("  ");
  }Serial.println();
  delay(100);
}
