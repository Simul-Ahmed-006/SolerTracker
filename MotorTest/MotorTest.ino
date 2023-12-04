#define in1 8
#define in2 7
#define enA 6
#define SetSpeed 40
#define servoPinDown 9
#define servoPinUP 10
#define ldr1 A0
#define ldr2 A1
#define ldr3 A3
#define ldr4 A4
#define ldr5 A5
#define threshold 300

#include <Servo.h>
int openclose = 0;// 0 means close // 1 means open
Servo ServoUp;
Servo ServoDown;
int ldr_reading[5];
void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(ldr3, INPUT);
  pinMode(ldr4, INPUT);
  pinMode(ldr5, INPUT);
  ServoUp.attach(servoPinUP);
  ServoDown.attach(servoPinDown);
  Serial.begin(9600);
}

void loop() {

  // LDR_Reading Take
  for (int i = 1; i < 5; i++)
  {
    ldr_reading[i] = analogRead(i);
//    Serial.print(i);
//    Serial.print(" ");
    Serial.print(ldr_reading[i]);
    Serial.print(" ");     
  }
  delay(500);
  Serial.println();

  int count = 0;
  for (int i = 1; i < 5; i++)
  {
    if (ldr_reading[i] >= threshold)
    {
      count++;
    }
  }
  //open();
  //close();
  //servoUpControl();
  //servoUpControl(50);
  //servoDownControl(0);
  // Checking
  // if (Serial.available())
  // {
  //   char s = Serial.read();
  //   if (s == 'd')
  //   {
  //     Serial.read();
  //     int x = Serial.read();
  //     servoDownControl(x);
  //   }
  //   if (s == 'u')
  //   {
  //     Serial.read();
  //     int y = Serial.read();
  //     servoUpControl(y);
  //   }
  // }
   if (count >= 1 && openclose == 0)
   {
    open();
    openclose = 1;
   }
   if (count >= 4)
   {
     servoUpControl(120);
     servoDownControl(90);
   }
   if (ldr_reading[1] >= threshold && ldr_reading[2] >= threshold)
   {
     servoUpControl(50);
     servoDownControl(180);
   }
   if (ldr_reading[2] >= threshold && ldr_reading[3] >= threshold)
   {
      servoUpControl(50);
      servoDownControl(90);
   }
   if (ldr_reading[3] >= threshold && ldr_reading[4] >= threshold)
   {
      servoUpControl(50);
      servoDownControl(0);
   }
   if (count == 0 && openclose ==1)
   {
      close();
   }
}
void open()
{
  analogWrite(enA, SetSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(800);
  delay(800); 
}
void close()
{
  analogWrite(enA, SetSpeed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(800);
  delay(800);
}
void servoUpControl(int angle1)
{
  ServoUp.write(angle1);
  delay(1000);
}
void servoDownControl(int angle2)
{
  ServoDown.write(angle2);
  delay(1000);
}
void servoUpControl()
{
 ServoUp.write(0);
 delay(1000);
 ServoUp.write(90);
 delay(1100);
 ServoUp.write(180);
 delay(1000);
 ServoUp.write(90);
 delay(1000); 
}
//void servoDownControl()
//{
//  ServoDown.write(0);
//  delay(1000);
//  //delay(1000);
//  ServoDown.write(90);
//  delay(1100);
//  //delay(1000);
//  ServoDown.write(180);
//  delay(1000);
//  ServoDown.write(90);
//  delay(1000); 
//}
