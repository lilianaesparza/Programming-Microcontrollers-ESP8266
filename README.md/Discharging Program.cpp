//------------------------------------------------------------
// Title: LiPo Battery Discharge Voltage Monitor
//------------------------------------------------------------
// Program Detail:
//------------------------------------------------------------
// Purpose: Measure and record the LiPo battery voltage during
//          the discharge experiment using the ESP8266 ADC.
//
// Inputs: Analog battery voltage applied to A0 through a
//         2 kOhm / 1 kOhm voltage-divider circuit.
//
// Outputs: Measurement number, elapsed discharge time,
//          raw ADC value, and calculated battery voltage
//          are displayed in the Serial Monitor.
//
// Date: October 5 2026
//
// Compiler: PlatformIO IDE / Arduino Framework
//
// Author: Liliana Esparza
//
// Versions:
//     V1 - Initial discharge-voltage measurement.
//     V2 - Added automatic 60-second data collection.
//
//------------------------------------------------------------
// File Dependencies:
//     Arduino.h
//------------------------------------------------------------

#include <Arduino.h>

//------------------------------------------------------------
// Constants and Variables
//------------------------------------------------------------

// R1 is the upper resistor of the voltage divider.
// It is connected between Battery+ and A0.
const float R1 = 2000.0;

// R2 is the lower resistor.
// It is connected between A0 and ground.
const float R2 = 1000.0;

// Maximum value produced by the 10-bit ADC.
const float ADC_MAX = 1023.0;

// Full-scale voltage used for A0 conversion.
const float A0_FULL_SCALE = 3.3;

// Measurement counter.
unsigned long measurementNumber = 1;


//------------------------------------------------------------
// Main Program
//------------------------------------------------------------

void setup() {

  // Start serial communication.
  Serial.begin(9600);

  // Allow Serial Monitor time to initialize.
  delay(3000);

  // Identify the experiment.
  Serial.println("LiPo Battery Discharge Test");

  // Print column headings.
  Serial.println(
    "Measurement,Time_min,ADC,Battery_Voltage_V"
  );
}


void loop() {

  // Read the raw ADC value from A0.
  int adcValue = analogRead(A0);

  // Convert the ADC reading to voltage at the A0 pin.
  float voltageA0 =
      adcValue * (A0_FULL_SCALE / ADC_MAX);

  // Calculate the actual battery voltage using the
  // external voltage-divider ratio.
  float batteryVoltage =
      voltageA0 * ((R1 + R2) / R2);

  // Print measurement number.
  Serial.print(measurementNumber);
  Serial.print(",");

  // Print elapsed discharge time in minutes.
  Serial.print(measurementNumber - 1);
  Serial.print(",");

  // Print raw ADC value.
  Serial.print(adcValue);
  Serial.print(",");

  // Print calculated battery voltage.
  Serial.println(batteryVoltage, 3);

  // Move to the next measurement.
  measurementNumber++;

  // Wait one minute before measuring again.
  delay(60000);
}
