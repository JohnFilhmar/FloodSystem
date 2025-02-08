#include "PINOUTS.h"
#include "VARIABLES.h"
#include "GSM.h"
#include <Arduino.h>
/*
-----------------------------------------------------------------------------------------------
SIM800L COMMANDS  |   Description                           |     Expected Response
-----------------------------------------------------------------------------------------------
AT                |   Checks if the module is responsive    |     OK
AT+CMGF=1         |   Set SMS mode to text                  |     OK
AT+CNMI=1,2,0,0,0 |   Configure new message indications     |     OK
AT+CMGS="..."     |   Send SMS to specified number          |     > (awaiting response)
AT+CREG?          |   Check network registration status     |     +CREG: 0,1 (home network)
AT+CSQ            |   Checks signal strength                |     +CSQ: 18,0 (medium signal)
AT+CPIN           |   Verify SIM Card readiness             |     +CPIN: READY
AT+CPIN?          |   Check SIM Card status                 |     +CPIN: READY
AT+CFUN=1,1       |   Reset module and enable functionality |     OK
AT+COPS?          |   Get current network operator          |     +COPS: 0,0,\"GLOBE\"
AT+CSCLK=0        |   Disable sleep mode                    |     OK
-----------------------------------------------------------------------------------------------
*/

void setupGSM()
{
  digitalWrite(RED, HIGH);
  sim800.begin(9600);
  delay(3000);
  
  resetSimModule();
  delay(500);

  while (sim800.available()) sim800.read();  // Ensure buffer is cleared

  verifySimConnection();
  
  pinMode(SIM800_RST, OUTPUT);
  digitalWrite(SIM800_RST, HIGH);
}

void resetSimModule()
{
  digitalWrite(SIM800_RST, LOW);
  delay(100);
  digitalWrite(SIM800_RST, HIGH);
  sim800.println("AT+CFUN=1,1");
  delay(5000);
  while (sim800.available()) sim800.read(); // Clear buffer
  delay(1000);
}

void readResponse(char *responseBuffer, size_t bufferSize, long timeout) {
  unsigned long startTime = millis();
  size_t index = 0;

  while (millis() - startTime < timeout) {
    while (sim800.available()) {
      char c = sim800.read();
      if (index < bufferSize - 1) { // Prevent buffer overflow
        responseBuffer[index++] = c;
      }
      startTime = millis(); // ✅ Reset timeout every time data is received
    }
  }

  responseBuffer[index] = '\0'; // Null-terminate the char array
}

void verifySimConnection()
{
  digitalWrite(RED, LOW);
  Serial.println("Initializing SIM800L...");
  char responseBuffer[100];

  while (true)
  {
    while (true) {
      digitalWrite(RED, LOW);
      // Send AT command to check connection
      while (sim800.available()) sim800.read(); // Clear buffer
      sim800.println("AT");
      delay(1000);
      readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
      Serial.println("Connection Status TX/RX:");
      Serial.println(responseBuffer);
      
      if (strstr(responseBuffer, "OK") != NULL) {
        digitalWrite(GREEN, HIGH);
        break;
      }

      digitalWrite(RED, HIGH);
      Serial.println("No response from SIM Module. Retrying...");
      while (sim800.available()) sim800.read(); // Clear buffer
      delay(1000);
    }
    
    // UNCOMMENT ONLY IF THERE'S A NEW ARDUINO WITH LARGER MEMORY
    // while (true) {
    //   // Ensure sleep mode is off
    //   while (sim800.available()) sim800.read(); // Clear buffer
    //   digitalWrite(GREEN, LOW);
    //   sim800.println("AT+CSCLK?");
    //   delay(3000);
    //   readResponse(responseBuffer, sizeof(responseBuffer), 3000);
    //   Serial.println("Sleep Mode Response:");
    //   Serial.println(responseBuffer);
    //   if (strstr(responseBuffer, "0") != NULL) {
    //     digitalWrite(GREEN, HIGH);
    //     Serial.println("Sleep mode disabled!");
    //     break;
    //   } else {
    //     while (sim800.available()) sim800.read(); // Clear buffer
    //     Serial.println("Sleep mode is disabled. Enabling sleep mode...");
    //     sim800.println("AT+CSCLK=1");
    //     delay(1000);
    //     readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
    //     Serial.println("Sleep Mode Response:");
    //     Serial.println(responseBuffer);
    //     if (strstr(responseBuffer, "OK") != NULL) {
    //       Serial.println("Sleep mode enabled!");
    //     } else {
    //       Serial.println("Failed to disable sleep mode. Retrying...");
    //       digitalWrite(RED, HIGH);
    //       delay(1000);
    //     }
    //   }
    //   delay(1000);
    // }

    // Check if SIM is ready
    // while (true) {
    //   digitalWrite(RED, LOW);
    //   digitalWrite(GREEN, LOW);
    //   while (sim800.available()) sim800.read(); // Clear buffer
    //   sim800.println("AT+CPIN?");
    //   delay(1000);
    //   readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
    //   Serial.println("SIM Ready Status:");
    //   Serial.println(responseBuffer);
    //   if (strstr(responseBuffer, "READY") != NULL) {
    //     digitalWrite(GREEN, HIGH);
    //     Serial.println("SIM Card is ready!");
    //     break;
    //   } else {
    //     Serial.println("SIM Card not ready. Retrying...");
    //     digitalWrite(RED, HIGH);
    //     delay(1000);
    //   }
    //   delay(1000);
    // }


    /* 
      ########## UNCOMMENT THE FOLLOWING TO TEST SIGNAL, NETWORK, AND OPERATOR STATUS ONLY IF YOU HAVE YOUR ARDUINO REPLACED WITH A BETTER ONE BIGGER THAN 2KB ##########
     */
    // digitalWrite(GREEN, LOW);
    // digitalWrite(RED, LOW);
    // while (sim800.available()) sim800.read(); // Clear buffer
    // sim800.println("AT+CSQ");
    // delay(1000);
    // readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
    // Serial.println("Signal Strength Status:");
    // Serial.println(responseBuffer);
    // if (strstr(responseBuffer, "+CSQ: 0,0") != NULL || strstr(responseBuffer, "ERROR") != NULL) {
    //   Serial.println("No valid signal detected!");
    //   digitalWrite(RED, HIGH);
    // } else {
    //   Serial.println("Signal detected!");
    //   digitalWrite(GREEN, HIGH);
    // }
    // delay(1000);

    // digitalWrite(GREEN, LOW);
    // digitalWrite(RED, LOW);
    // while (sim800.available()) sim800.read(); // Clear buffer
    // sim800.println("AT+CREG?");
    // delay(1000);
    // readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
    // Serial.println("Network Registration Status:");
    // Serial.println(responseBuffer);
    // if (strstr(responseBuffer, "+CREG: 0,1") != NULL) {
    //   Serial.println("Network registered!");
    //   digitalWrite(GREEN, HIGH);
    // } else {
    //   Serial.println("Network not registered. Retrying...");
    //   digitalWrite(RED, HIGH);
    // }
    // delay(1000);

    // digitalWrite(GREEN, LOW);
    // digitalWrite(RED, LOW);
    // while (sim800.available()) sim800.read(); // Clear buffer
    // sim800.println("AT+COPS?");
    // delay(1000);
    // readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
    // Serial.println("Operator Status:");
    // Serial.println(responseBuffer);
    // if (strstr(responseBuffer, "+COPS: 0,0,\"GLOBE\"") != NULL) {
    //   Serial.println("Operator detected!");
    //   digitalWrite(GREEN, HIGH);
    // } else {
    //   Serial.println("Operator not detected. Retrying...");
    //   digitalWrite(RED, HIGH);
    // }
    // delay(1000);

    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    bool messageSent = false;
    while (sim800.available()) sim800.read(); // Clear buffer

    while (!messageSent) {
      messageSent = sendSMS(OWNER_NUMBER, INITIAL_MESSAGE);
      if (messageSent) {
        Serial.println("Initial SMS Sent.");
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, HIGH);
        break;
      } else {
        Serial.println("Failed to send SMS. Retrying...");
        digitalWrite(RED, HIGH);
        digitalWrite(BLUE, LOW);
        delay(1000);
      }
    }
    if (messageSent) break;
  }
}

bool sendSMS(const char *number, const char *message) {
  while (true) {
    // Set SMS mode
    while (true) {
      while (sim800.available()) sim800.read(); // Clear buffer
      Serial.println("SMS Mode Response: ");
      sim800.println("AT+CMGF=1");
      delay(1000);
      char responseBuffer[100] = {0}; // Use static buffer
      readResponse(responseBuffer, sizeof(responseBuffer), GSM_TIMEOUT);
      Serial.println(responseBuffer);
      if (strstr(responseBuffer, "OK") == NULL) {
        Serial.println("Failed to set SMS mode. Retrying...");
        digitalWrite(RED, HIGH);
        delay(1000);
      } else {
        digitalWrite(RED, LOW);
        break;
      }
    }

    // Flush buffer to prevent old data interference
    while (sim800.available()) sim800.read();

    // Send SMS command
    sim800.print("AT+CMGS=\"");
    sim800.print(String(number));
    sim800.println("\"");
    delay(5000);

    // Wait for '>' prompt before sending the message
    char promptBuffer[10] = {0}; // Small buffer for response
    unsigned long start = millis();
    bool promptReceived = false;

    // this compares the current millis to the start time and if it is less than 3000, it will wait for the prompt
    while (millis() - start < 5000) { // Wait up to 3 seconds
      if (sim800.available()) {
        int len = sim800.readBytes(promptBuffer, sizeof(promptBuffer) - 1);
        promptBuffer[len] = '\0'; // Null-terminate
        if (strstr(promptBuffer, ">") != NULL) {
          promptReceived = true;
          break;
        }
      }
    }

    if (!promptReceived) {
      Serial.println("Error: No '>' prompt received!");
      return;
    }

    // Send message content
    sim800.print(message);
    delay(500);

    // Send Ctrl+Z to finalize
    sim800.write(26); // Ctrl+Z
    delay(3000);

    // Read response with extended timeout
    char responseBuffer[100] = {0}; // Use static buffer
    readResponse(responseBuffer, sizeof(responseBuffer), 3000);
    Serial.print("Send Message Response: ");
    Serial.println(responseBuffer);

    if (strstr(responseBuffer, "OK") != NULL) {
      Serial.println("Message sent successfully!");
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      delay(2000);
      digitalWrite(GREEN, LOW);
      return true;
    } else {
      return false;
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      delay(2000);
      digitalWrite(RED, LOW);
    }
  }
}

unsigned long previousSMSMillis = 0;
unsigned long smsStepMillis = 0;
int smsStep = 0;

void directSMS(float waterLevel) {

  unsigned long currentTime = millis();
  
  while (sim800.available()) sim800.read(); // Clear buffer
  Serial.println("SMS Interval: " + String((currentTime - previousSMSMillis) / 1000) + " seconds");
  if (currentTime - previousSMSMillis < SMS_INTERVAL) {
    return;
  }
  
  for (int i = 0; i < NUMBERS_TO_MESSAGE_COUNT; i++) {
    switch (smsStep) {
      case 0:
        if (currentTime - smsStepMillis >= 1000) {
          sim800.println("AT+CMGF=1");
          smsStepMillis = currentTime;
          smsStep++;
        }
        break;
      case 1:
        if (currentTime - smsStepMillis >= 3000) {
          sim800.print("AT+CMGS=\"");
          sim800.print(NUMBERS_TO_MESSAGE[i]);
          sim800.println("\"");
          smsStepMillis = currentTime;
          smsStep++;
        }
        break;
      case 2:
        if (currentTime - smsStepMillis >= 1000) {
          sim800.println(createMessage(waterLevel));
          smsStepMillis = currentTime;
          smsStep++;
        }
        break;
      case 3:
        if (currentTime - smsStepMillis >= 3000) {
          sim800.write(26);
          smsStepMillis = currentTime;
          smsStep++;
        }
        break;
      case 4:
        if (currentTime - smsStepMillis >= 1000) {
          smsStep = 0; // Reset step for next message
          previousSMSMillis = millis(); // Update last SMS time
          Serial.println("SMS Sent!");
        }
        break;
    }
    delay(2000);
  }
  
}

// this function will create a message that will be sent to the owner of the device
String createMessage(float waterLevel) {
  char waterLevelStr[10];  // Buffer for converted float
  dtostrf(waterLevel, 6, 2, waterLevelStr);  // Convert float to string

  char message[100];  // Final message buffer
  sprintf(message, "Water level is at %s meters. Please check the water level immediately.", waterLevelStr);

  return String(message);
}