void home()
{
  moveTo(LF_HOME, LL_HOME, RL_HOME, RF_HOME);
}

// VENSTRE SKRIDT
void stepLeft()
{
  // Flyt vægten over på højre ben
  moveTo(
      LF_HOME + TILT,
      LL_HOME,
      RL_HOME,
      RF_HOME);
  delay(PAUSE);

  // Sving venstre ben frem
  moveTo(
      LF_HOME + TILT,
      LL_HOME,
      RL_HOME,
      RF_HOME - TILT);
  delay(PAUSE);

  moveTo(
      LF_HOME,
      LL_HOME - LEFT_SWING,
      RL_HOME - RIGHT_SWING,
      RF_HOME - TILT);
  delay(PAUSE);

  // Sæt venstre ben ned
  moveTo(
      LF_HOME,
      LL_HOME - LEFT_SWING,
      RL_HOME - RIGHT_SWING,
      RF_HOME);
  delay(PAUSE);

  moveTo(
      LF_HOME,
      LL_HOME,
      RL_HOME,
      RF_HOME);

  delay(100);
  home();
  delay(PAUSE);
}

// HØJRE SKRIDT
void stepRight()
{
  // Flyt vægten over på venstre ben
  moveTo(
      LF_HOME,
      LL_HOME,
      RL_HOME,
      RF_HOME - TILT);
  delay(PAUSE);

  // Højre bens fungerende bevægelse
  moveTo(
      LF_HOME + TILT,
      LL_HOME,
      RL_HOME,
      RF_HOME - TILT);
  delay(PAUSE);

  // Sæt højre ben ned
  moveTo(
      LF_HOME + TILT,
      LL_HOME + LEFT_SWING,
      RL_HOME + RIGHT_SWING,
      RF_HOME);
  delay(PAUSE);

  moveTo(
      LF_HOME,
      LL_HOME + LEFT_SWING,
      RL_HOME + RIGHT_SWING,
      RF_HOME);
  delay(PAUSE);

  moveTo(
      LF_HOME,
      LL_HOME,
      RL_HOME,
      RF_HOME);

  delay(100);
  home();
  delay(PAUSE);
}

void walk(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    if (i % 2 == 0)
    {
      stepLeft();
    }
    else
    {
      stepRight();
    }
  }
  home();
}