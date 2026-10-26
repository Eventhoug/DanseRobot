// Her inkluderes 2 biblioteker, som er nødvendige for at kunne styre servoerne
#include <Arduino.h>
#include <Servo.h>

// Her sættes start positionerne for servoerne som er de positioner hvor robotten står lige
#define LFootServoDefaultPos 110
#define LLegServoDefaultPos 145
#define RLegServoDefaultPos 30
#define RFootServoDefaultPos 90

// Her sættes hvor mange grader robotten tilter fødderne og svinger benene
#define TILT 15
#define SWING 20

// Her sættes hvor lang tid hver bevægelse tager i millisekunder
#define MOVE_TIME 500

// Her laves servo objekter til de 4 servoer
Servo LFootServo;
Servo LLegServo;
Servo RLegServo;
Servo RFootServo;

// Her gemmes hvor langt fødderne og benene er fra deres default position lige nu
int footOffset = 0;
int legOffset = 0;

// vores bevægelses funktion, hvor begge fødder får samme offset og begge ben får samme offset
void move(int foot, int leg)
{
  // Her bruges et for loop til at lave en glidende bevægelse for ikke at skabe ubalance og vælte robotten
  for (int t = 20; t <= MOVE_TIME; t += 20)
  {
    // Her bruges map() til at beregne hvor langt servoerne skal være i forhold til hvor lang tid der er gået
    int f = map(t, 0, MOVE_TIME, footOffset, foot);
    int l = map(t, 0, MOVE_TIME, legOffset, leg);

    // Her skrives de nye positioner til servoerne
    LFootServo.write(LFootServoDefaultPos + f);
    LLegServo.write(LLegServoDefaultPos + l);
    RLegServo.write(RLegServoDefaultPos + l);
    RFootServo.write(RFootServoDefaultPos + f);
    delay(20);
  }

  // Når bevægelsen er færdig, sættes offset til de nye værdier
  footOffset = foot;
  legOffset = leg;
}

// vores danse funktion
void Dance()
{
  // Printer Dance til serial monitor og tænder LED_BUILTIN for nemmere at debugge
  Serial.println("Dance");
  digitalWrite(LED_BUILTIN, HIGH);

  // Tilter fødderne fra side til side 6 gange
  for (int i = 0; i < 6; i++)
  {
    move(TILT, 0);
    move(-TILT, 0);
  }

  // Svinger benene frem og tilbage 4 gange
  for (int i = 0; i < 4; i++)
  {
    move(0, SWING);
    move(0, -SWING);
  }

  // Tilbage til default position
  move(0, 0);
  digitalWrite(LED_BUILTIN, LOW);
}

// Step funktionen der går et skridt fremad, hvor side er 1 for højre ben og -1 for venstre ben
void Step(int side)
{
  // Læner sig over på det ene ben
  move(side * TILT, legOffset);

  // Svinger det andet ben frem
  move(side * TILT, side * SWING);

  // Sætter foden ned igen
  move(0, side * SWING);
}

// vores gå funktion, som tager et antal skridt og skifter ben hver gang
void Walk(int steps)
{
  // Printer Walk til serial monitor og tænder LED_BUILTIN for nemmere at debugge
  Serial.println("Walk");
  digitalWrite(LED_BUILTIN, HIGH);

  // Tager et skridt og skifter side, så robotten går på skiftevis højre og venstre ben
  int side = 1;
  for (int i = 0; i < steps; i++)
  {
    Step(side);
    side = -side;
  }

  // Læner sig over på det forreste ben og samler benene igen, så robotten ender i default position
  move(side * TILT, legOffset);
  move(side * TILT, 0);
  move(0, 0);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  // Starter serial monitor og sætter LED_BUILTIN som output
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Her skrives default positionerne før attach, så servoerne starter der
  LFootServo.write(LFootServoDefaultPos);
  LLegServo.write(LLegServoDefaultPos);
  RLegServo.write(RLegServoDefaultPos);
  RFootServo.write(RFootServoDefaultPos);

  // Her forbindes servoerne til deres pins
  LFootServo.attach(11);
  LLegServo.attach(6);
  RLegServo.attach(5);
  RFootServo.attach(3);

  // Der er et 3 sek delay for at robotten ikke starter så snart kablet indsættes
  delay(3000);
  Serial.println("Setup done");
}

// Her kaldes Walk og Dance i loop, så robotten går 6 skridt fremad og danser 4 gange
void loop()
{
  Walk(6);
  delay(2000);
  Dance();
  delay(2000);
}
