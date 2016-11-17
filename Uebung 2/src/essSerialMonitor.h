#ifndef ESSSERIALMONITOR_H
#define ESSSERIALMONITOR_H

#include <Arduino.h>

void serialEvent();
extern String inputString;         // a string to hold incoming data
extern byte sensor;
#endif
