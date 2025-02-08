#ifndef PINOUTS_H
#define PINOUTS_H

/* 
  Arduino UNO Pins
  ----------------
  Digital Pins: 0-13
  Analog Pins: A0-A5
  PWM Pins: 3, 5, 6, 9, 10, 11
  Interrupt Pins: 2, 3
  SPI Pins: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK)
  I2C Pins: A4 (SDA), A5 (SCL)
  Reset Pin: RESET
 */

// JSN-SR04T Waterproof Ultrasonic Sensor Pinouts
#define JSN_TRIG_PIN 2 // Trigger pin
#define JSN_ECHO_PIN 3 // Echo pin

// RGB LED Pinouts
#define RED_LED 5 // Red LED pin
#define GREEN_LED 6 // Green LED pin
#define BLUE_LED 9 // Blue LED pin

// SIM800L GSM Module Pinouts
#define SIM800_RX 11 // RX pin
#define SIM800_TX 10 // TX pin
#define SIM800_RST 12 // Reset pin

// DFPlayer Mini MP3 Player Module Pinouts
#define DF_PLAYER_RX 4
#define DF_PLAYER_TX 7

#define RED A0
#define GREEN A1
#define BLUE A2

#endif