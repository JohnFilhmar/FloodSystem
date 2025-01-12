#include "PINOUTS.h"
#include "LED.h"
#include <Arduino.h>

void setupLED()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void setLEDColor(int red, int green, int blue)
{
  analogWrite(RED_LED, red); // Set the color using PWM
  analogWrite(GREEN_LED, green); // Set the color using PWM
  analogWrite(BLUE_LED, blue); // Set the color using PWM
}