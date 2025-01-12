#ifndef GSM_H
#define GSM_H
#include <SoftwareSerial.h>

extern SoftwareSerial sim800;

String readResponse(unsigned long timeout);
void setupGSM();
void verifySimConnection();
void testSimFunctions();

#endif