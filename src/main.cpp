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

// Nuværende positioner, så vi kan bevæge os blødt derfra
int lfPos = LFootServoDefaultPos;
int llPos = LLegServoDefaultPos;
int rlPos = RLegServoDefaultPos;
int rfPos = RFootServoDefaultPos;

void Dance();
void Walk(int steps);

// Flytter alle 4 servoer samtidig og blødt til de nye positioner over 'ms' millisekunder
void moveTo(int lf, int ll, int rl, int rf, int ms)
{
  int startLf = lfPos, startLl = llPos, startRl = rlPos, startRf = rfPos;
  int steps = max(1, ms / 20);

  for (int i = 1; i <= steps; i++)
  {
    LFootServo.write(startLf + (long)(lf - startLf) * i / steps);
    LLegServo.write(startLl + (long)(ll - startLl) * i / steps);
    RLegServo.write(startRl + (long)(rl - startRl) * i / steps);
    RFootServo.write(startRf + (long)(rf - startRf) * i / steps);
    delay(20);
  }

  lfPos = lf;
  llPos = ll;
  rlPos = rl;
  rfPos = rf;
}

// Begge fødder vippes samme vej, så robotten læner sig over på det ene ben.
// tilt: +1 / -1 / 0 (lige), swing: hoftevinkel i forhold til default
void pose(int tilt, int swing, int ms)
{
  moveTo(
      LFootServoDefaultPos + tilt * TILT,
      LLegServoDefaultPos + swing,
      RLegServoDefaultPos + swing,
      RFootServoDefaultPos + tilt * TILT,
      ms);
}

void home()
{
  moveTo(LFootServoDefaultPos, LLegServoDefaultPos, RLegServoDefaultPos, RFootServoDefaultPos, MOVE_TIME);
}

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Reset servo pos: sæt default pos før attach, så servoerne starter der
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

void Dance()
{
  Serial.println("Dance");
  digitalWrite(LED_BUILTIN, HIGH);

  // Vugger fra side til side
  for (int i = 0; i < 6; i++)
  {
    pose(1, 0, MOVE_TIME);
    pose(-1, 0, MOVE_TIME);
  }

  // Vrider hofterne frem og tilbage
  for (int i = 0; i < 4; i++)
  {
    pose(0, SWING, MOVE_TIME);
    pose(0, -SWING, MOVE_TIME);
  }

  home();
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
    pose(side, rlPos - RLegServoDefaultPos, MOVE_TIME);
    // 2. Sving det lette ben frem
    pose(side, side * WALK_DIR * SWING, MOVE_TIME);
    // 3. Sæt foden ned igen
    pose(0, side * WALK_DIR * SWING, MOVE_TIME);
  }

  home();
  digitalWrite(LED_BUILTIN, LOW);
}
