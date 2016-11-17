#ifndef ESSIRSENSOR_H
#define ESSIRSENSOR_H

#include <avr/io.h>

void configADC();
float linearizeDistanceShort(int distanceRaw);
float linearizeDistanceLong(int distanceRaw);
int readADC(int8_t channel);

#endif
