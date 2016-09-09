/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#include <stdlib.h>

int led[3] = {31, 35, 39};
int button = 43;

int potentiometer = 6;
unsigned long pot_val = 0;

int buttonState = 0;
int lastbuttonState = 0;
int count = 0;
unsigned long interval = 200;
unsigned long time;
unsigned long prev_time = 0;
int int_counter = 0;
int randInt = 0;

// the setup routine runs once when you press reset:
void setup() {        
  Serial.begin(9600);  
  // initialize the digital pin as an output.
  pinMode(button, INPUT);
  pinMode(potentiometer, INPUT);
  for (int i = 0; i < 3; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  interval = analogRead(potentiometer);
  time = millis();  
  buttonState = digitalRead(button);
  if(buttonState == 1)
  {
    count = (count + 1) % 5;
    delay(500);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(count == 0)
  { 
    if ((int_counter == 0) && (time - prev_time > interval))
    {
      prev_time = time;
      int_counter = (int_counter + 1) % 2;
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(led[i], HIGH);   // turn the LED on (HIGH is the voltage level)
      }
    }
    if ((int_counter == 1) && (time - prev_time > interval))
    {
      prev_time = time;
      int_counter = (int_counter + 1) % 2;
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(led[i], LOW);   // turn the LED on (LOW is the voltage level)
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(count == 1)
  {
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(led[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////
  if(count == 2)
  {
    for (int j = 0; j < 3; j++)
    {
      if ((int_counter == j) && (time - prev_time > interval))
      {
        prev_time = time;
        int_counter = (int_counter + 1) % 3;
        for (int i = 0; i < 3; i++)
        {
          if(i == j)
          {
            digitalWrite(led[i], HIGH);   // turn the LED on (HIGH is the voltage level)
          }
          else
          {
            digitalWrite(led[i], LOW);
          }
        }
      }
    }  
  }
  ////////////////////////////////////////////////////////////////////////////////////
  if(count == 3)
  {
    for (int j = 0; j < 2; j++)
    {                                                      
      if ((int_counter == j) && (time - prev_time > interval))
      {
        prev_time = time;
        int_counter = (int_counter + 1) % 2;
        for (int i = 0; i < 3; i++)
        {
          if(j % 2 == 0)
          {
            if (i % 2 == 0)
            {
              digitalWrite(led[i], HIGH);
            }
            else
            {
              digitalWrite(led[i], LOW);
            }
          }
          else
          {
            if (i % 2 == 1)
            {
              digitalWrite(led[i], HIGH);
            }
            else
            {
              digitalWrite(led[i], LOW);
            }
          }
        }
      }
    }  
  }
  ////////////////////////////////////////////////////////////////////////////////////
  if(count == 4)
  {         
    if (time - prev_time > interval)
    {
      randInt = random(3);
      prev_time = time;
      for (int i = 0; i < 3; i++)
      {
        if (randInt== i)
        {
          digitalWrite(led[i], HIGH);
        }
        else
        {
          digitalWrite(led[i], LOW);
        }
      }
    }  
  }
}




