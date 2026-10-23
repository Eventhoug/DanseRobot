#include <Arduino.h>
#include <Servo.h>

#define LFootServoDefaultPos 110
#define LLegServoDefaultPos 145
#define RLegServoDefaultPos 30
#define RFootServoDefaultPos 90

// Hvor meget robotten læner sig (fødder) og svinger benene (hofter), i grader
#define TILT 15
#define SWING 20
// Skift til -1 hvis robotten går baglæns
#define WALK_DIR 1
// Hvor lang tid hver bevægelse tager (ms) - højere = roligere
#define MOVE_TIME 500

Servo LFootServo;
Servo LLegServo;
Servo RLegServo;
Servo RFootServo;

// Hvor langt fødderne og benene er fra deres default-position lige nu
int footOffset = 0;
int legOffset = 0;

// Flytter blødt fødder og ben til nye offsets over MOVE_TIME ms.
// Begge fødder får samme offset, og begge ben får samme offset.
void move(int foot, int leg)
{
  for (int t = 20; t <= MOVE_TIME; t += 20)
  {
    int f = map(t, 0, MOVE_TIME, footOffset, foot);
    int l = map(t, 0, MOVE_TIME, legOffset, leg);

    LFootServo.write(LFootServoDefaultPos + f);
    LLegServo.write(LLegServoDefaultPos + l);
    RLegServo.write(RLegServoDefaultPos + l);
    RFootServo.write(RFootServoDefaultPos + f);
    delay(20);
  }

  footOffset = foot;
  legOffset = leg;
}

void Dance()
{
  Serial.println("Dance");
  digitalWrite(LED_BUILTIN, HIGH);

  // Vugger fra side til side
  for (int i = 0; i < 6; i++)
  {
    move(TILT, 0);
    move(-TILT, 0);
  }

  // Vrider hofterne frem og tilbage
  for (int i = 0; i < 4; i++)
  {
    move(0, SWING);
    move(0, -SWING);
  }

  move(0, 0);
  digitalWrite(LED_BUILTIN, LOW);
}

void Walk(int steps)
{
  Serial.println("Walk");
  digitalWrite(LED_BUILTIN, HIGH);

  for (int i = 0; i < steps; i++)
  {
    int side = (i % 2 == 0) ? 1 : -1;

    // 1. Læn over på det ene ben (det andet ben bliver let)
    move(side * TILT, legOffset);
    // 2. Sving det lette ben frem
    move(side * TILT, side * WALK_DIR * SWING);
    // 3. Sæt foden ned igen
    move(0, side * WALK_DIR * SWING);
  }

  move(0, 0);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Sæt default pos før attach, så servoerne starter der
  LFootServo.write(LFootServoDefaultPos);
  LLegServo.write(LLegServoDefaultPos);
  RLegServo.write(RLegServoDefaultPos);
  RFootServo.write(RFootServoDefaultPos);

  LFootServo.attach(11);
  LLegServo.attach(6);
  RLegServo.attach(5);
  RFootServo.attach(3);

  delay(3000);
  Serial.println("Setup done");
}

void loop()
{
  Walk(6);
  delay(2000);
  Dance();
  delay(2000);
}
