//------------------------------------------------------------
// Title: LiPo Battery Charging Voltage Monitor
//------------------------------------------------------------
// Program Detail:
//------------------------------------------------------------
// Purpose: Measure and record the LiPo battery voltage during
//          the charging experiment using the ESP8266 ADC.
//
// Inputs: Analog battery voltage applied to A0 through a
//         2 kOhm / 1 kOhm voltage-divider circuit.
//
// Outputs: Measurement number, elapsed time, raw ADC value,
//          and calculated battery voltage are displayed in
//          the Serial Monitor.
//
// Date: October 2026
//
// Compiler: PlatformIO IDE / Arduino Framework
//
// Author: Liliana Esparza
//
// Versions:
//     V1 - Initial ADC battery-voltage measurement.
//     V2 - Added voltage-divider conversion.
//     V3 - Added automatic 60-second data collection.
//
//------------------------------------------------------------
// File Dependencies:
//     Arduino.h
//------------------------------------------------------------

#include <Arduino.h>

//------------------------------------------------------------
// Constants and Variables
//------------------------------------------------------------

// Voltage-divider resistor values.
// R1 is connected from Battery+ to A0.
const float R1 = 2000.0;

// R2 is connected from A0 to ground.
const float R2 = 1000.0;

// ESP8266 uses a 10-bit ADC.
// Therefore, the ADC range is 0 to 1023.
const float ADC_MAX = 1023.0;

// Full-scale voltage used for the NodeMCU A0 conversion.
const float A0_FULL_SCALE = 3.3;

// Keeps track of the measurement number.
unsigned long measurementNumber = 1;


//------------------------------------------------------------
// Main Program
//------------------------------------------------------------

void setup() {

  // Start serial communication at 9600 baud.
  Serial.begin(9600);

  // Allow the Serial Monitor time to initialize.
  delay(3000);

  // Print column headings for collected data.
  Serial.println(
    "Measurement,Time_min,ADC,Battery_Voltage_V"
  );
}


void loop() {

  // Read the analog voltage from the A0 pin.
  int adcValue = analogRead(A0);

  // Convert the raw ADC reading into the voltage at A0.
  float voltageA0 =
      adcValue * (A0_FULL_SCALE / ADC_MAX);

  // Undo the external voltage-divider ratio to determine
  // the actual LiPo battery voltage.
  float batteryVoltage =
      voltageA0 * ((R1 + R2) / R2);

  // Print the measurement number.
  Serial.print(measurementNumber);
  Serial.print(",");

  // Print elapsed time in minutes.
  Serial.print(measurementNumber - 1);
  Serial.print(",");

  // Print the raw ADC reading.
  Serial.print(adcValue);
  Serial.print(",");

  // Print calculated battery voltage to three decimals.
  Serial.println(batteryVoltage, 3);

  // Increase measurement counter.
  measurementNumber++;

  // Wait 60 seconds before taking the next measurement.
  delay(60000);
}
