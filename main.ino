#include "PINOUTS.h"
#include "GSM.h"
#include "JSN.h"
#include "LED.h"
#include "SPEAKER.H"
#include <SoftwareSerial.h>
/*
 * Initializes the SIM800L module connection through DPIN 11 (TX) and DPIN 10 (RX).
 */
// SoftwareSerial sim800(SIM800_TX, SIM800_RX);
/* 
  * Initializes the DFPlayer Mini MP3 Player module connection through DPIN 6 (RX) and DPIN 9 (TX).
 */
SoftwareSerial dfPlayerSerial(DF_PLAYER_RX, DF_PLAYER_TX); // RX, TX

void setup()
{
  Serial.begin(9600);
  delay(1000);
  setupSpeaker();
  Serial.println("DFPlayer Mini MP3 Player Module Initialized!");
  // setupJSN();
  // Serial.println("JSN-SR04T Ultrasonic Sensor Initialized!");
  // setupLED();
  // Serial.println("RGB LED Initialized!");
  // setupGSM();
  // Serial.println("SIM800L GSM Module Initialized!");
}

void loop()
{
  playTone(1, 1000);
  // readDistanceWithMean();
  // delay(500);
}