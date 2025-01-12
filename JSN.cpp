#include "PINOUTS.h"
#include "JSN.h"
#include "LED.h"
#include <Arduino.h>

void setupJSN()
{
  pinMode(JSN_TRIG_PIN, OUTPUT);
  pinMode(JSN_ECHO_PIN, INPUT);
}

long triggerEcho()
{
  // Send a 10-microsecond pulse to trigger pin
  digitalWrite(JSN_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(JSN_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(JSN_TRIG_PIN, LOW);
  long duration = pulseIn(JSN_ECHO_PIN, HIGH);
  if (duration >= 1200 && duration <= 26325)
  {
    return duration;
  }
  else
  {
    return 0;
  }
}

void readDistanceWithMean()
{
  double total_range = 0;
  for (int i = 0; i < 20; i++) {
    long distance = triggerEcho();
    double range = (distance * 0.034 / 2) / 100;
    total_range += range;
    delay(25);
  }
  Serial.println("Total Range: " + String(total_range) + " meters");
  float mean_range = total_range / 20;
  Serial.println("Mean Range: " + String(mean_range) + " meters");
  float waterLevel = JSN_MODULE_HEIGHT - mean_range;
  
  Serial.println("Water Level: " + String(waterLevel) + " meters");
  if (waterLevel > 0.2 && waterLevel < 0.5) // No flood or minor flood
  {
    Serial.println("Steady Consistent Scanning (No Flood or Minor Flood)!");
    setLEDColor(0, 0, 255); // Blue
  }
  else if (waterLevel >= 0.5 && waterLevel < 1.5) // Moderate flood
  {
    Serial.println("Flood Starting (Moderate Flood)!");
    setLEDColor(0, 255, 0); // Green
  }
  else if (waterLevel >= 1.5 && waterLevel < 2.5) // Severe flood
  {
    Serial.println("Severe Flood! Evacuation Needed!");
    setLEDColor(255, 255, 0); // Yellow
  }
  else if (waterLevel >= 2.5 && waterLevel < 4.0) // Critical flood
  {
    Serial.println("Critical Flood! Life Threatening!");
    setLEDColor(255, 165, 0); // Orange
  }
  else if (waterLevel >= 4.0) // Catastrophic flood
  {
    Serial.println("Catastrophic Flood! Destructive!");
    setLEDColor(255, 0, 0); // Red
  }
  else 
  {
    Serial.println("No Water Detected!");
    setLEDColor(0, 0, 0); // Off
  }
}