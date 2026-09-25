#include <Arduino.h>
#include <Servo.h>

#define LFootServoDefaultPos 110
#define LLegServoDefaultPos 145
#define RLegServoDefaultPos 30
#define RFootServoDefaultPos 80


Servo LFootServo;
Servo LLegServo;
Servo RLegServo;
Servo RFootServo;

void setup()
{
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
  delay(2000);
}
void loop()
{
  Dance();
  delay(2000);
  Walk();
  delay(2000);
}

void Dance()
{
  // Her laves en simpel dans
  // Føddernes servo kører ind og ud
  // Når robotten danser så tænder vi den built-in LED på Arduinoen
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < 20; i++)
  {
    LFootServo.write(LFootServoDefaultPos - 20);
    RFootServo.write(RFootServoDefaultPos + 20);
    delay(300);
    LFootServo.write(LFootServoDefaultPos + 20);
    RFootServo.write(RFootServoDefaultPos - 20);
    delay(300);
  }

  LFootServo.write(LFootServoDefaultPos);
  RFootServo.write(RFootServoDefaultPos);
  digitalWrite(LED_BUILTIN, LOW);
}

void Walk()
{
  // Her bevæges servoerne så robotten kan gå sidelæns
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < 20; i++) {
    LLegServo.write(LLegServoDefaultPos - 20);
    LFootServo.write(LFootServoDefaultPos + 20);
    RLegServo.write(RLegServoDefaultPos + 20);
    RFootServo.write(RFootServoDefaultPos - 20);
    delay(500);
    LLegServo.write(LLegServoDefaultPos);
    LFootServo.write(LFootServoDefaultPos);
    RLegServo.write(RLegServoDefaultPos);
    RFootServo.write(RFootServoDefaultPos);
    delay(500);
  }

  digitalWrite(LED_BUILTIN, LOW);
}