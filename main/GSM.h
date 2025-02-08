#ifndef GSM_H
#define GSM_H
#include <SoftwareSerial.h>

extern SoftwareSerial sim800;

void setupGSM();
void resetSimModule();
void readResponse(char *responseBuffer, size_t bufferSize, long timeout);
void verifySimConnection();
void testSimFunctions();
String sendCommand(const char *command, const char *logMessage);
String retryCommand(const char *command, const char *logMessage, uint8_t maxRetries = 3);
bool sendSMS(const char *number, const char *message);
void directSMS(float waterLevel);
String createMessage(float waterLevel);

#endif