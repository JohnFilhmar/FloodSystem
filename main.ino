#include "PINOUTS.h"
#include "VARIABLES.h"
#include "GSM.h"
#include "JSN.h"
#include "LED.h"
#include "SPEAKER.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

/*
 * Initializes the SIM800L module connection through DPIN 11 (TX) and DPIN 10 (RX).
 */
SoftwareSerial sim800(SIM800_RX, SIM800_TX);
/*
 * Initializes the DFPlayer Mini MP3 Player module connection through DPIN 6 (RX) and DPIN 9 (TX).
 */
SoftwareSerial dfPlayerSerial(DF_PLAYER_RX, DF_PLAYER_TX); // RX, TX

// 1 time
void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  Serial.begin(9600);
  delay(1000);

  setupGSM();
  setupLED();
  setupJSN();
  setupSpeaker();

  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);
}

void loop()
{
  unsigned long currentTime = millis();
  
  float waterLevel = getWaterLevel();

  if (waterLevel > 0 && waterLevel <= 0.5) {
    playTone(1, FILE_LENGTHS[0]);
    setLEDColor(0, 0, 255);
    directSMS(waterLevel);
    Serial.println("Blue ALERT - Water Level is at " + String(waterLevel) + " meters");

  } else if (waterLevel > 0.5 && waterLevel <= 1.5) {
    playTone(2, FILE_LENGTHS[1]);
    setLEDColor(0, 255, 0);
    directSMS(waterLevel);
    Serial.println("Green ALERT - Water Level is at " + String(waterLevel) + " meters");

  } else if (waterLevel > 1.5 && waterLevel <= 2.5) {
    playTone(3, FILE_LENGTHS[2]);
    setLEDColor(255, 255, 0);
    directSMS(waterLevel);
    Serial.println("Yellow ALERT - Water Level is at " + String(waterLevel) + " meters");

  } else if (waterLevel > 2.5 && waterLevel <= 4.0) {
    playTone(4, FILE_LENGTHS[3]);
    setLEDColor(255, 127, 0);
    directSMS(waterLevel);
    Serial.println("Orange ALERT - Water Level is at " + String(waterLevel) + " meters");

  } else if (waterLevel > 4.0) {
    playTone(5, FILE_LENGTHS[4]);
    setLEDColor(255, 0, 0);
    directSMS(waterLevel);
    Serial.println("Red ALERT - Water Level is at " + String(waterLevel) + " meters");

  } else {
    stopTone();
  }
  
}
