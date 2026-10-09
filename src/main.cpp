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
void TurnRightLeg_SpeedDegree(int speed, int degree);

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
  // Her laves en simpel dans
  // Føddernes servo kører ind og ud
  // Når robotten danser så tænder vi den built-in LED på Arduinoen
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < 20; i++)
  {
    LFootServo.write(LFootServoDefaultPos - 20);
    RFootServo.write(RFootServoDefaultPos + 30);
    delay(400);
    LFootServo.write(LFootServoDefaultPos);
    RFootServo.write(RFootServoDefaultPos);
    delay(400);
  }

  for (int i = 0; i < 20; i++)
  {
    // Trin 1
    LLegServo.write(LLegServoDefaultPos + 25);
    RLegServo.write(RLegServoDefaultPos - 25);
    delay(180);

    // Trin 2
    LLegServo.write(LLegServoDefaultPos);
    RLegServo.write(RLegServoDefaultPos);
    delay(180);

    // Trin 3
    LFootServo.write(LFootServoDefaultPos + 10);
    RFootServo.write(RFootServoDefaultPos + 10);
    LLegServo.write(LLegServoDefaultPos - 25);
    RLegServo.write(RLegServoDefaultPos + 25);
    delay(180);

    // Trin 4
    LFootServo.write(LFootServoDefaultPos);
    RFootServo.write(RFootServoDefaultPos);
    LLegServo.write(LLegServoDefaultPos);
    RLegServo.write(RLegServoDefaultPos);
    delay(180);
  }

  LFootServo.write(LFootServoDefaultPos);
  RFootServo.write(RFootServoDefaultPos);
  digitalWrite(LED_BUILTIN, LOW);
}

void TurnRightLeg_SpeedDegree(int speed, int degree)
{
  speed = abs(speed);
  if (speed == 0)
  {
    return;
  }

  int current = RLegServo.read();
  int increment = current < degree ? speed : -speed;

  for (int position = current;
       increment > 0 ? position <= degree : position >= degree;
       position += increment)
  {
    RLegServo.write(position);
    delay(50);
  }

  RLegServo.write(degree);
}

void Walk()
{
  Serial.println("Walk");
  digitalWrite(LED_BUILTIN, HIGH);

  for (int step = 0; step < 4; step++)
  {
    // Flyt højre ben ud, mens venstre fod holder robotten på plads.
    TurnRightLeg_SpeedDegree(2, RLegServoDefaultPos + 25);
    RFootServo.write(RFootServoDefaultPos + 25);
    delay(250);

    // Flyt venstre ben efter og sæt højre fod tilbage.
    LLegServo.write(LLegServoDefaultPos - 25);
    LFootServo.write(LFootServoDefaultPos - 20);
    delay(250);

    // Sæt benene tilbage i udgangsposition.
    RFootServo.write(RFootServoDefaultPos);
    LFootServo.write(LFootServoDefaultPos);
    LLegServo.write(LLegServoDefaultPos);
    TurnRightLeg_SpeedDegree(2, RLegServoDefaultPos);
    delay(250);
  }

  digitalWrite(LED_BUILTIN, LOW);
}