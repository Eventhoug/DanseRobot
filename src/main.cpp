#include <Arduino.h>
#include <Servo.h>

#define LFootServoDefaultPos 110
#define LLegServoDefaultPos 145
#define RLegServoDefaultPos 30
#define RFootServoDefaultPos 90

Servo LFootServo;
Servo LLegServo;
Servo RLegServo;
Servo RFootServo;

void Dance();
void Walk();

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  LFootServo.attach(11);
  LLegServo.attach(6);
  RLegServo.attach(5);
  RFootServo.attach(3);

  LFootServo.write(LFootServoDefaultPos);
  LLegServo.write(LLegServoDefaultPos);
  RLegServo.write(RLegServoDefaultPos);
  RFootServo.write(RFootServoDefaultPos);
  delay(5000);
  Serial.println("Setup done");
}
void loop()
{
  
  Walk();
  delay(2000);
  Dance();
  delay(2000);
  
}

void Dance()
{
  Serial.println("Dance");
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < 20; i++)
  {
    RFootServo.write(RFootServoDefaultPos + 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos + 20);
    delay(400);
    RFootServo.write(RFootServoDefaultPos - 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos - 20);
    delay(400);
  }

  LFootServo.write(LFootServoDefaultPos);
  RFootServo.write(RFootServoDefaultPos);
  digitalWrite(LED_BUILTIN, LOW);
}



void Walk()
{
  Serial.println("Walk");
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < 20; i++)
  {
    RFootServo.write(RFootServoDefaultPos - 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos + 20);
    delay(400);
    RFootServo.write(RFootServoDefaultPos);
    delay(400);
    LLegServo.write(LLegServoDefaultPos + 20);
    delay(400);
    RLegServo.write(RLegServoDefaultPos - 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos);
    delay(400);
    RFootServo.write(RFootServoDefaultPos + 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos - 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos);
    delay(400);
    LLegServo.write(LLegServoDefaultPos);
    RLegServo.write(RLegServoDefaultPos);
    delay(400);


    // Måske reverse + og -
    LFootServo.write(LFootServoDefaultPos - 20);
    delay(400);
    RFootServo.write(RFootServoDefaultPos + 20);
    delay(400);
    LFootServo.write(LFootServoDefaultPos);
    delay(400);
    RLegServo.write(RLegServoDefaultPos + 20);
    delay(400);
    LLegServo.write(LLegServoDefaultPos - 20);
    delay(400);
    RFootServo.write(RFootServoDefaultPos);
    delay(400);
    LFootServo.write(LFootServoDefaultPos + 20);
    delay(400);
    RFootServo.write(RFootServoDefaultPos - 20);
    delay(400);
    RFootServo.write(RFootServoDefaultPos);
    delay(400);
    RLegServo.write(RLegServoDefaultPos);
    LLegServo.write(LLegServoDefaultPos);
    delay(400);
  }

  digitalWrite(LED_BUILTIN, LOW);
}