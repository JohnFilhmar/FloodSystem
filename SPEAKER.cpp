#include "PINOUTS.h"
#include "SPEAKER.h"
#include "DFRobotDFPlayerMini.h"
#include <Arduino.h>

DFRobotDFPlayerMini myDFPlayer;

void setupSpeaker()
{
  Serial.println("Initializing DFPlayer Mini...");
  if (!myDFPlayer.begin(dfPlayerSerial))
  {
    Serial.println("Unable to begin: ");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while (true);
  }
  Serial.println("DFPlayer Mini online.");
  myDFPlayer.volume(DFPLAYER_VOLUME_MAX);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL); // Corrected the typo here
}

void playTone(int tone, int duration)
{
  myDFPlayer.play(tone);

  int fileLength = myDFPlayer.readFileCounts(); // Get file length in seconds

  if (fileLength > 0) {
    Serial.print("File length: ");
    Serial.print(fileLength);
    Serial.println(" seconds");

    delay(fileLength * 1000); // Delay based on file length
  } else {
    Serial.println("Could not retrieve file length. Using default delay.");
    delay(duration); // Fallback delay if length cannot be retrieved
  }
  myDFPlayer.stop();
}
