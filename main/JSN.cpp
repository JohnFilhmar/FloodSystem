#include "PINOUTS.h"
#include "JSN.h"
#include "LED.h"
#include "VARIABLES.h"
#include <Arduino.h>

void setupJSN()
{
  pinMode(JSN_TRIG_PIN, OUTPUT);
  pinMode(JSN_ECHO_PIN, INPUT);
  Serial.println("JSN-SR04T Ultrasonic Sensor Initialized!");
}

long triggerEcho()
{
  digitalWrite(JSN_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(JSN_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(JSN_TRIG_PIN, LOW);
  long duration = pulseIn(JSN_ECHO_PIN, HIGH, 50000);
  return duration > 0 ? duration : 26262;
}

float getWaterLevel()
{
  float total_range = 0;
  for (int i = 0; i < TIMES_TO_SCAN; i++)
  {
    long distance = triggerEcho();
    float range = (distance * 0.0343 / 2) / 100;
    total_range += range;
    delay(SCAN_INTERVAL);
  }

  float mean_range = total_range / TIMES_TO_SCAN;
  float waterLevel = JSN_MODULE_HEIGHT - mean_range;
  return waterLevel;
}