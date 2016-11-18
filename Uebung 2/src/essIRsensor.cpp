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
  while (getADSCValue(ADCSRA, ADSC) != 0) {
    _delay_ms(5);
  }
  return ADCW;
}

int readADC(int8_t channel){
   /*switch (channel) {
     case 1: ADMUX &= ~(1<<MUX0);
     case 2: ADMUX |= (1<<MUX0);
     default: ADMUX &= ~(1<<MUX0);
   }*/
   if (channel != getADSCValue(ADMUX, 0)) {
     if (channel == 1){
      ADMUX |= 1;
    }
    else{
      ADMUX &= ~1;
    }
}
   return getVoltage();
}

/**
* @brief Maps the digital voltage information on a distance
*        in cm
*/
float linearizeDistanceShort(int distanceRaw){
  /*float result;
  result = 0.000000001518132826 * distanceRaw * distanceRaw * distanceRaw *distanceRaw - 0.00000246045567 * distanceRaw * distanceRaw *distanceRaw + 0.001467881897 * distanceRaw * distanceRaw - 0.4016316825 * distanceRaw + 51.15692686;
  return result;*/
  float result;
  result = 0.000000001004101438* distanceRaw * distanceRaw * distanceRaw * distanceRaw - 0.000001770823232* distanceRaw * distanceRaw * distanceRaw + 0.001194670323 * distanceRaw * distanceRaw - 0.3830255972 * distanceRaw + 56.19891333;
  return result;
}

/**
* @brief Maps the digital voltage information on a distance
*        in cm
*/
float linearizeDistanceLong(int distanceRaw){
  /*float result; //Day function
  result = 0.000000852 * distanceRaw * distanceRaw * distanceRaw * distanceRaw - 0.000614 * distanceRaw * distanceRaw * distanceRaw + 0.167 * distanceRaw * distanceRaw - 20.62 * distanceRaw + 1018.19;
  return result;*/
  float result;  //Night Function
  result = 0.000001918708287* distanceRaw * distanceRaw * distanceRaw * distanceRaw - 0.001161694739* distanceRaw * distanceRaw * distanceRaw + 0.2644340611* distanceRaw * distanceRaw - 27.1453977 * distanceRaw + 1109.556089;
  return result;
}
