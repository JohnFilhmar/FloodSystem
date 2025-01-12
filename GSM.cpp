#include "PINOUTS.h"
#include "GSM.h"
#include <Arduino.h>
/*
-----------------------------------------------------------------------------------------------
SIM800L COMMANDS  |   Description                           |     Expected Response
-----------------------------------------------------------------------------------------------
AT                |   Checks if the module is responsive    |     OK
AT+CMGF=1         |   Set SMS mode to text                  |     OK
AT+CMGS="..."     |   Send SMS to specified number          |     > (awaiting response)
AT+CREG?          |   Check network registration status     |     +CREG: 0,1 (home network)
AT+CSQ            |   Checks signal strength                |     +CSQ: 18,0 (medium signal)
AT+CPIN           |   Verify SIM Card readiness             |     +CPIN: READY
AT+CFUN=1,1       |   Reset module and enable functionality |     OK
AT+COPS?          |   Get current network operator          |     +COPS: 0,0,\"GLOBE\"
AT+CSCLK=0        |   Disable sleep mode                    |     OK
-----------------------------------------------------------------------------------------------
*/

void setupGSM()
{
  sim800.begin(9600);
  delay(1000);
  verifySimConnection();
  testSimFunctions();
}

String readResponse(unsigned long timeout)
{
  String response = "";
  unsigned long startTime = millis();
  while (millis() - startTime < timeout)
  {
    while (sim800.available())
    {
      char c = sim800.read();
      response += c;
    }
  }
  response.trim(); // Remove leading/trailing whitespace
  return response;
}

void verifySimConnection()
{
  Serial.println(F("Initializing SIM800L..."));
  while (true)
  {
    while (sim800.available())
    {
      sim800.read(); // Clear buffer
    }

    // Send AT command to check connection
    sim800.println("AT");
    delay(2000);
    String connectionResponse = readResponse(5000);
    Serial.println("Connection Status TX/RX: " + connectionResponse);

    // Check if SIM is ready
    sim800.println("AT+CPIN?");
    delay(2000);
    String simReadyResponse = readResponse(5000);
    Serial.println("SIM Ready Status: " + simReadyResponse);

    // If SIM is ready, exit the loop
    if (simReadyResponse.indexOf("READY") != -1)
    {
      Serial.println(F("SIM Module Working & Available!"));
      break;
    }
    else
    {
      Serial.println(F("Invalid response from SIM Module. Retrying..."));
      delay(2000);
    }
  }
}
void testSimFunctions()
{
  // Reset the module
  sim800.println("AT+CFUN=1,1");
  delay(5000); // Allow time for the module to restart
  String resetResponse = readResponse(5000);
  Serial.println("Reset Response: " + resetResponse);

  // Disable sleep mode
  while (sim800.available())
  {
    sim800.read(); // Clear buffer
  }
  sim800.println("AT+CSCLK=0");
  delay(2000);
  String sleepResponse = readResponse(5000);
  Serial.println("Sleep Mode Response: " + sleepResponse);

  // Check network operator
  while (sim800.available())
  {
    sim800.read(); // Clear buffer
  }
  sim800.println("AT+COPS?");
  delay(3000);
  String operatorResponse = readResponse(5000);
  Serial.println("Operator Response: " + operatorResponse);

  // Check network registration
  while (sim800.available())
  {
    sim800.read(); // Clear buffer
  }
  sim800.println("AT+CREG?");
  delay(3000);
  String networkResponse = readResponse(5000);
  Serial.println("Network Registration Response: " + networkResponse);

  // Check signal strength
  while (sim800.available())
  {
    sim800.read(); // Clear buffer
  }
  sim800.println("AT+CSQ");
  delay(2000);
  String signalResponse = readResponse(5000);
  Serial.println("Signal Strength Response: " + signalResponse);

  // Set SMS mode
  while (sim800.available())
  {
    sim800.read(); // Clear buffer
  }
  sim800.println("AT+CMGF=1");
  delay(2000);
  String smsModeResponse = readResponse(5000);
  Serial.println("SMS Mode Response: " + smsModeResponse);

  // Send SMS
  while (sim800.available())
  {
    sim800.read(); // Clear buffer
  }
  sim800.println("AT+CMGS=\"09668649640\"");
  delay(2000);
  sim800.print("Hello! This is a message from your ARDUINO BASED IOT (FLOOD NOTIFICATION). Your SIM800L Module is working perfectly!");
  delay(1000);
  sim800.write(26); // Send Ctrl+Z
  delay(5000);
  String smsResponse = readResponse(5000);
  Serial.println("Send Message Response: " + smsResponse);
  if (smsResponse.indexOf("+CMGS") != -1)
  {
    Serial.println("Message sent successfully!");
  }
  else if (smsResponse.indexOf("ERROR") != -1)
  {
    Serial.println("Failed to send message. Response: " + smsResponse);
  }
  else
  {
    Serial.println("Unexpected response: " + smsResponse);
  }
}