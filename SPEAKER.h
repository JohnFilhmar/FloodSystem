#ifndef SPEAKER_H
#define SPEAKER_H
#include <SoftwareSerial.h>

#define DFPLAYER_VOLUME_MAX 20
#define DFPLAYER_EQ_NORMAL 0

extern SoftwareSerial dfPlayerSerial;

void setupSpeaker();
void playTone(int tone, int duration);

#endif