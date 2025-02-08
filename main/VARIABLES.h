#include <Arduino.h>
#ifndef VARIABLES_H
#define VARIABLES_H

const bool TEST_BEFORE_RUN = true;

// JSN-SR04T Waterproof Ultrasonic Sensor Constants
// Maximum range of the JSN-SR04T module is 4.5 meters
const float JSN_MODULE_HEIGHT = 4.5;       // Height of the JSN-SR04T module in meters from the ground
const int SCAN_INTERVAL = 5;        // Interval in milliseconds between each scan
const int TIMES_TO_SCAN = 5;       // Number of times to scan for mean calculation

// DFPLAYER Mini MP3 Player Constants
const int DFPLAYER_VOLUME_MAX = 20;
const int DFPLAYER_EQ_NORMAL = 0;
const long FILE_LENGTHS[] = {37000, 38000, 33000, 33000, 44000};
const int FILE_COUNT = 5;

// SIM MODULE/GSM Constants
const char INITIAL_MESSAGE[] = "Hi, this is your Arduino UNO's GSM Module messaging you. The Project WANGWANG is initialized, and ready for operation!";
// NUMBER THE INITIAL MESSAGE WILL BE SENT TO
const char OWNER_NUMBER[] = "+639701703168";
// NUMBERS TO SEND THE MESSAGE TO TO ALERT
const char NUMBERS_TO_MESSAGE[][11] = {
    "09665475203",
    "09624631239",
    "09701703168"
};
// COUNT OF NUMBERS TO SEND THE MESSAGE TO
const int NUMBERS_TO_MESSAGE_COUNT = 3;

// GSM Module Constants
const long GSM_TIMEOUT = 1000; // Timeout for GSM commands
const long GSM_DELAY = 1000; // Delay for GSM commands

// INTERVALS
const long SMS_INTERVAL = 180000; // 3 minute interval - sends SMS every 3 minutes or when the water level changes
const long TONE_INTERVAL = 120000; // 2 minutes interval - plays tone every 2 minutes or when the water level changes
const char MESSAGE_FORMAT[] = "Water level is at %f meters. Please check the water level immediately."; 

#endif