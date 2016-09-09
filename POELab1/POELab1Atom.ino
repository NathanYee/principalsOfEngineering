/*
PoeLab1 - Bike Light
A bike LED with 5 featured modes.

0 - blink all LED's
1 - turn on all LED's
2 - cycle LED's one at a time
3 - cycle through odd and even LED's
4 - random single LED

*/

#include <stdlib.h>

// define digital and analog pins
int led[3] = {31, 35, 39};
int button = 43;
int potentiometer = 6;

// define counters
int buttonState = 0;

// sets the mode of the LED.  Mode will range from 0-4 for the 5 modes.
int mode = 0;

// state keeps track of where we are inside a particular mode
int state = 0;

// used in mode 4 to turn on an off random LED's
int randInt = 0;

// time related
unsigned long interval = 200;
unsigned long time;
unsigned long prev_time = 0;

void mode0(void);
void mode1(void);
void mode2(void);
void mode3(void);
void mode4(void);

// the setup routine runs on startup
void setup() {
  // start serial
  Serial.begin(9600);

  // initialize the digital button
  pinMode(button, INPUT);

  // initialize the analog potentiometer
  pinMode(potentiometer, INPUT);

  // initalize the digital LED's
  for (int i = 0; i < 3; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // debug println to see what mode
  Serial.println(mode);

  // set interval to potentiometer input (0 - 1024) ms
  interval = analogRead(potentiometer);

  // set button state to button input
  buttonState = digitalRead(button);

  // begin interval time state
  time = millis();

  // update mode if button was pressed down
  if(buttonState == 1)
  {
    mode = (mode + 1) % 5;
    delay(500); // limit button presses to once per half second
  }

  // use switch statement to determine which mode to call
  switch (mode) {
    case 0 : mode0(); break;
    case 1 : mode1(); break;
    case 2 : mode2(); break;
    case 3 : mode3(); break;
    case 4 : mode4(); break;
    }
}

void mode0(void)
// blink all LED's
{
  for (int j = 0; j < 2; j++)
  {
    // this statement is how we keep track of time.  Abstractly, it allows us
    // to simulate delays while still sampling for button presses
    if ((state == j) && (time - prev_time > interval))
    {
      prev_time = time;
      state = (state + 1) % 2;
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(led[i], HIGH);   // turn the LED on
      }
    }
    else if ((state != j) && (time - prev_time > interval))
    {
      prev_time = time;
      state = (state + 1) % 2;
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(led[i], LOW);   // turn the LED off
      }
    }
  }
}

void mode1(void)
// turn all LED's on
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(led[i], HIGH);   // turn the LED on
  }
}

void mode2(void)
// cycle LED's one at a time
{
  for (int j = 0; j < 3; j++)
  // 3 possible states, one for each LED
  {
    if ((state == j) && (time - prev_time > interval))
    {
      prev_time = time;
      state = (state + 1) % 3;
      for (int i = 0; i < 3; i++) // loop through 3 LED's
      {
        if(i == j)
        {
          digitalWrite(led[i], HIGH);   // turn the LED on
        }
        else
        {
          digitalWrite(led[i], LOW);   // turn the LED off
        }
      }
    }
  }
}

void mode3(void)
// cycle through odd and even LED's
{
  for (int j = 0; j < 2; j++)
  {
    if ((state == j) && (time - prev_time > interval))
    {
      prev_time = time;
      state = (state + 1) % 2;
      for (int i = 0; i < 3; i++)
      {
        if(j % 2 == 0)
        {
          if (i % 2 == 0)
          {
            digitalWrite(led[i], HIGH);   // turn the LED on
          }
          else
          {
            digitalWrite(led[i], LOW);   // turn the LED off
          }
        }
        else
        {
          if (i % 2 == 1)
          {
            digitalWrite(led[i], HIGH);   // turn the LED on
          }
          else
          {
            digitalWrite(led[i], LOW);   // turn the LED off
          }
        }
      }
    }
  }
}

void mode4(void)
// random single LED
{
  if (time - prev_time > interval)
  {
    randInt = random(3);
    prev_time = time;
    for (int i = 0; i < 3; i++)
    {
      if (randInt== i)
      {
        digitalWrite(led[i], HIGH);   // turn the LED on
      }
      else
      {
        digitalWrite(led[i], LOW);   // turn the LED off
      }
    }
  }
}
