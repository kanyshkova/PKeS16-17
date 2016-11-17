#ifndef ESSDISPLAY_H
#define ESSDISPLAY_H

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

void initDisplay();
void writeDigitsToDisplay(char digit1, char digit2, char digit3);
void writeValueToDisplay(int value);
void writeValueToDisplay(float value, char dec);
uint8_t displayMask(char val);

#endif
