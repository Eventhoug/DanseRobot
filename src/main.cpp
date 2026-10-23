#include <Arduino.h>
#include <Servo.h>

// Startpositioner for servoerne (grader)
#define LF_HOME 110
#define LL_HOME 145
#define RL_HOME 30
#define RF_HOME 80

// Bevægelser (grader) og ventetid (ms) - juster efter behov
#define TILT 20
#define LEFT_SWING 25
#define RIGHT_SWING 25
#define PAUSE 300

Servo LFootServo;
Servo LLegServo;
Servo RLegServo;
Servo RFootServo;

void moveTo(int lf, int ll, int rl, int rf) {
  LFootServo.write(constrain(lf, 0, 180));
  LLegServo.write(constrain(ll, 0, 180));
  RLegServo.write(constrain(rl, 0, 180));
  RFootServo.write(constrain(rf, 0, 180));
}

void home() {
  moveTo(LF_HOME, LL_HOME, RL_HOME, RF_HOME);
}

// VENSTRE SKRIDT
void stepLeft() {
  // Flyt vægten over på højre ben
  moveTo(
    LF_HOME + TILT,
    LL_HOME,
    RL_HOME,
    RF_HOME
  );
  delay(PAUSE);

  // Sving venstre ben frem
  moveTo(
    LF_HOME + TILT,
    LL_HOME,
    RL_HOME,
    RF_HOME - TILT
  );
  delay(PAUSE);

moveTo(
    LF_HOME,
    LL_HOME - LEFT_SWING,
    RL_HOME - RIGHT_SWING,
    RF_HOME - TILT
  );
  delay(PAUSE);

  // Sæt venstre ben ned
  moveTo(
    LF_HOME,
    LL_HOME - LEFT_SWING,
    RL_HOME - RIGHT_SWING,
    RF_HOME
  );
delay(PAUSE);

 moveTo(
    LF_HOME,
    LL_HOME,
    RL_HOME,
    RF_HOME
  );

  delay(100);
  home();
  delay(PAUSE);
}

// HØJRE SKRIDT
void stepRight() {
  // Flyt vægten over på venstre ben
  moveTo(
    LF_HOME,
    LL_HOME,
    RL_HOME,
    RF_HOME - TILT
  );
  delay(PAUSE);

  // Højre bens fungerende bevægelse
  moveTo(
    LF_HOME + TILT,
    LL_HOME,
    RL_HOME,
    RF_HOME - TILT
  );
  delay(PAUSE);

  // Sæt højre ben ned
  moveTo(
    LF_HOME + TILT,
    LL_HOME + LEFT_SWING,
    RL_HOME + RIGHT_SWING,
    RF_HOME
  );
delay(PAUSE);

moveTo(
    LF_HOME,
    LL_HOME + LEFT_SWING,
    RL_HOME + RIGHT_SWING,
    RF_HOME
  );
delay(PAUSE);

  moveTo(
    LF_HOME,
    LL_HOME,
    RL_HOME,
    RF_HOME
  );

  delay(100);
  home();
  delay(PAUSE);
}

void walk(int steps) {
  for (int i = 0; i < steps; i++) {
    if (i % 2 == 0) {
      stepLeft();
    } else {
      stepRight();
    }
  }
  home();
}

void setup() {
  LFootServo.attach(11);
  LLegServo.attach(6);
  RLegServo.attach(5);
  RFootServo.attach(3);
  home();
  delay(1000);
}

void loop() {
  walk(4);
  delay(1000);
}
