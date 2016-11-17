#include "essIRsensor.h"
#include <math.h>
#include <Arduino.h>


/**
* @brief Configures the ADC related to mode, clock speed, gain
*        resolution and refrence voltage
*
* In order to reach a maximum resolution it is necessary to
* chose the reference voltage carfully related to the output
* range of the sensor.
*/
void configADC(){
  ADCSRA = 0b11000111;
  ADMUX = 0b01000000;
}
/**
* @brief Starts a single conversion and receives a result
*/
int getADSCValue(int number, int k) {
  // Wir verunden an der richtigen Stelle und schieben das einzige Bit, was
  // überbleibt,
  // an den Anfang des Registers, dass es nen vernünftiger Int ist.
  return (number & (1 << k)) >> k;
}

int getVoltage(){
  ADCSRA |= (1 << ADSC);
  if(getADSCValue(ADCSRA, ADSC) != 0){
    Serial.println("success");
  }
  while (getADSCValue(ADCSRA, ADSC) != 0) {
    _delay_ms(5);
  }
  return ADCW;
}

int readADC(int8_t channel){
   switch (channel) {
     case 1: ADMUX &= ~(1<<MUX0);
     case 2: ADMUX |= (1<<MUX0);
     default: ADMUX &= ~(1<<MUX0);
   }
   return getVoltage();
}

/**
* @brief Maps the digital voltage information on a distance
*        in cm
*/
float linearizeDistanceShort(int distanceRaw){
  float result = 0;
  // TODO
  return result;
}

/**
* @brief Maps the digital voltage information on a distance
*        in cm
*/
float linearizeDistanceLong(int distanceRaw){
  float result = 0;
  // TODO
  return result;
}
