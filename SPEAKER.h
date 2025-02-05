#ifndef SPEAKER_H
#define SPEAKER_H
#include <SoftwareSerial.h>

extern SoftwareSerial dfPlayerSerial;

void setupSpeaker();
void playTone(int tone, long duration);
void stopTone();
bool isPlaying();
void playFile(int fileNumber);
// void handleTonePlayback();

#endif