#include "PINOUTS.h"
#include "VARIABLES.h"
#include "GSM.h"
#include "SPEAKER.h"
#include "DFRobotDFPlayerMini.h"
#include <Arduino.h>

DFRobotDFPlayerMini myDFPlayer;

void setupSpeaker()
{
  dfPlayerSerial.begin(9600);
  Serial.println("Initializing DFPlayer Mini...");
  if (myDFPlayer.begin(dfPlayerSerial))
  {
    Serial.println("OK");
  }
  else
  {
    {
      while (true)
      {
        Serial.println("Connecting to DFPlayer Mini...");
        if (myDFPlayer.begin(dfPlayerSerial))
        {
          Serial.println("OK");
          break;
        }
        else
        {
          delay(1000); // Wait for a second before retrying
        }
      }
    }
  }
  myDFPlayer.volume(DFPLAYER_VOLUME_MAX);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
}

unsigned long previousMPMillis = 0;
unsigned long toneStepMillis = 0;
int toneStep = 0;
int currentTone = 1;
bool playingTone6 = true;
bool waitingForNextCycle = false;

void playTone(int tone, long duration)
{
  unsigned long currentMillis = millis();
  Serial.println("Audio Interval: " + String((currentMillis - previousMPMillis) / 1000) + " seconds");

  // **Check if the tone has changed**
  if (tone != currentTone) {
    currentTone = tone;  // Update current tone
    previousMPMillis = currentMillis;  // Reset interval timer
    toneStepMillis = currentMillis;
    toneStep = 0;  // Reset step-based state machine
    playingTone6 = true;
    waitingForNextCycle = false; // Prevent delay from blocking new tone
  }

  // **Wait for the interval before restarting the tone cycle**
  if (waitingForNextCycle)
  {
    if (currentMillis - previousMPMillis >= TONE_INTERVAL)
    {
      waitingForNextCycle = false; // Reset flag
      toneStep = 0;                // Restart the sequence
      playingTone6 = true;
      previousMPMillis = currentMillis;
      toneStepMillis = currentMillis;
    }
    else
    {
      return; // **Do nothing while waiting for interval**
    }
  }

  // Step-based non-blocking audio control
  switch (toneStep)
  {
  case 0: // **Play "Wang-Wang" (Tone 6) for 11 seconds**
    if (playingTone6 && currentMillis - toneStepMillis >= 0)
    {
      myDFPlayer.play(6);
      toneStepMillis = currentMillis;
      toneStep++;
    }
    break;

  case 1: // **Wait 11 seconds before switching to the specified tone**
    if (currentMillis - toneStepMillis >= 11000)
    {
      playingTone6 = false; // Stop playing Wang-Wang
      toneStepMillis = currentMillis;
      toneStep++;
    }
    break;

  case 2: // **Play the specified tone**
    if (currentMillis - toneStepMillis >= 0)
    {
      myDFPlayer.play(tone); // Play the user-defined tone
      toneStepMillis = currentMillis;
      toneStep++;
    }
    break;

  case 3: // **Wait for the duration of the chosen tone**
    if (currentMillis - toneStepMillis >= duration)
    {
      previousMPMillis = millis(); // **Record time when tone cycle ends**
      toneStep++;
      waitingForNextCycle = true; // **Set flag to wait for interval**
    }
    break;
  }
}

void stopTone()
{
  myDFPlayer.stop();
}

bool isPlaying()
{
  return myDFPlayer.readState() == 1;
}

void playFile(int fileNumber)
{
  myDFPlayer.play(fileNumber);
}