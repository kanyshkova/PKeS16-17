#include "essDisplay.h"
#include <Arduino.h>
char cDisplayBuffer[3] = {0,0,0};

void initDisplay(){
  // -------------------------------------------------------------
  // Serial bus lines
  // -------------------------------------------------------------

  //LTM8522 ESS-Bot-Configuration
  //LTM8522            | Arduino | ATMega
  //-----------------------------------------
  //PIN 14 Data Enable |  D33    | Port C4
  //PIN 15 Serial Data |  D34    | Port C3
  //PIN 16 Clock       |  D35    | Port C2

  // Pin 35 = PORT C 2 = clock
  DDRC |= (1<<DDC2);
  // Pin 34 = PORT C 3 = data
  DDRC |= (1<<DDC3);
  // Pin 33 = PORT C 4 = enable
  DDRC |= (1<<DDC4);
}

/**
* @brief Visualizes 3x8bit values on the 3x7 segments
*
* First of all try to understand the mapping of individual bits on
* a specific segment. Why does the input 0b10110110 for instance generates
* an "S" and 0b10110111 an "S."?
* Afterwards, take a view to the data sheet of the display for understanding
* the communication protocoll.
*/

void setPinLow(int pin){
  PORTC &= ~(1<<pin);
}

void setPinHigh(int pin){
  PORTC |= (1<<pin);
}

void writeDigitsToDisplay(char digit1, char digit2, char digit3){
  char stream[36]; //
  stream[0]=1;
  int i;
  for ( i=1; i<36; i++ ) {
    stream[i]=0;
  }

  for ( i=0; i<8; i++ ) {
    if (digit1 & (1<<(7-i))) stream[i+ 1]=1;
    if (digit2 & (1<<(7-i))) stream[i+ 9]=1;
    if (digit3 & (1<<(7-i))) stream[i+17]=1;
  }

  for( int k = 0; k<36; k++) {
    if(stream[k]==1){setPinHigh(3);}
    if(stream[k]==0){setPinLow(3);}
    _delay_ms(1);
    setPinHigh(2);
    _delay_ms(1);
    setPinLow(2);
    _delay_ms(1);
  }
  // Serial transmission of the display content

}

uint8_t displayMask(char val){
  switch(val){
    case ' ': return 0b00000000;
    case '0': return 0b11111100;

    case '1': return 0b01100000;
    case '2': return 0b11011010;
    case '3': return 0b11110010;
    case '4': return 0b01100110;
    case '5': return 0b10110110;
    case '6': return 0b10111110;
    case '7': return 0b11100000;
    case '8': return 0b11111110;
    case '9': return 0b11110110;

    case 'a':
    case 'A': return 0b11101110;
    case 'b':
    case 'B': return 0b00000000;
    case 'c': return 0b00011010;
    case 'C': return 0b10011100;
    case 'd':
    case 'D': return 0b01111010;
    case 'e':
    case 'E': return 0b10011110;
    case 'f':
    case 'F': return 0b10001110;
    case 'r': return 0b00000000;

    case '-': return 0b00000010;
    case '.': return 0b00000001;

    default: return 0b00000001;
  }
}

uint8_t displayDot(char val){
  switch(val){
    case ' ': return 0b00000000;
    case '0': return 0b11111101;

    case '1': return 0b01100001;
    case '2': return 0b11011011;
    case '3': return 0b11110011;
    case '4': return 0b01100111;
    case '5': return 0b10110111;
    case '6': return 0b10111111;
    case '7': return 0b11100001;
    case '8': return 0b11111111;
    case '9': return 0b11110111;

    case 'a':
    case 'A': return 0b01100010;
    case 'b':
    case 'B': return 0b00000001;
    case 'c': return 0b00011010;
    case 'C': return 0b10011100;
    case 'd':
    case 'D': return 0b01111010;
    case 'e':
    case 'E': return 0b10011110;
    case 'f':
    case 'F': return 0b10001110;
    case 'r': return 0b00000001;

    case '-': return 0b00000010;
    case '.': return 0b00000001;

    default: return 0b00000001;
  }
}
/**
* @brief Write an integer value to the 3x7 segments
*
*/

void writeNegativeValue(int value){
  value = value*(-1);
  char stream[3];
  stream[0] ='B';
  stream[1]='B'; stream[2]='B';
  int i = 0;
  while(value!=0){
    stream[i++] = value % 10;
    value /= 10;
  }
  writeDigitsToDisplay(0b00000010,displayMask(stream[1]+48),displayMask(stream[0]+48));
}

void writeValueToDisplay(int value){
  //funktioniert soweit kanns okay
  //tobe solved: 0 ´nur notwendig darstellen
  //Serial.println(value);
  if(value==0){return writeDigitsToDisplay(0b00000000,0b00000000,displayMask(48));}
  if(value < 0){
    writeNegativeValue(value);
  }
  else{
    char stream[3];
    stream[0] = 'B';
    stream[1]='B'; stream[2]='B';
    int i = 0;
    while(value!=0){
      stream[i++] = value % 10;
      value /= 10;
    }
    writeDigitsToDisplay(displayMask(stream[2]+48),displayMask(stream[1]+48),displayMask(stream[0]+48));

  }
}
/**
* @brief Write a float value to the 3x7 segments
*
*/
void writeValueToDisplay(float value, char dec){
  //haut ab und zu noch falsche zahlen und defaults raus
  if(value==0.0){return writeDigitsToDisplay(0b00000000,displayDot(48),displayMask(48));}
  bool wasnegative = false;
  if(value<0){
    wasnegative = true; value = value * (-1);
  }
  value = value * 10;
  int intvalue = value;

  char stream[3];
  stream[0]='B';
  stream[1]='B'; stream[2]='B';
  int i = 0;
  while(intvalue!=0){
    stream[i++] = intvalue % 10;
    intvalue /= 10;
  }
  if(wasnegative){
    if(stream[2]==1){
      writeDigitsToDisplay(displayDot('A'),displayDot(stream[1]+48),displayMask(stream[0]+48));
    }
    else{
      writeDigitsToDisplay(displayDot(45),displayDot(stream[1]+48),displayMask(stream[0]+48));
    }
  }
  else{
    writeDigitsToDisplay(displayMask(stream[2]+48),displayDot(stream[1]+48),displayMask(stream[0]+48));
  }
}

void geeetToTheDISPLAY(float roll, float pitch){
  //Serial.println(pitch);
  uint8_t pos1 = 0b00000000;
  uint8_t pos2 = 0b00000000;
  uint8_t pos3 = 0b00000000;
  if(pitch < -25.0){
    pos1 |= 0b00001100;
  }
  if(pitch < -15.0 && pitch > -25.0){
    pos1 |= 0b01100000;
  }
  if(pitch < -5.0 && pitch > -15.0){
    pos2 |= 0b00001100;
  }
  if(pitch < 5.0 && pitch > -5.0){ // mittlere Pitchposition
    pos2 |= 0b01101100;
  }
  if(pitch > 5.0 && pitch < 15.0){
    pos2 |= 0b01100000;
  }
  if(pitch > 15.0 && pitch < 25.0){
    pos3 |= 0b00001100;
  }
  if(pitch > 25.0){
    pos3 |= 0b01100000;
  }
  if(roll < -20.0){ // links Rollposition
    pos1 |= 0b10000000;
    pos2 |= 0b10000000;
    pos3 |= 0b10000000;
  }
  if(roll < 20.0 && roll > -20.0){ // mittlere Rollposition
    pos1 |= 0b00000010;
    pos2 |= 0b00000010;
    pos3 |= 0b00000010;
  }
  if(roll > 20.0 ){ // rechts Rollposition
    pos1 |= 0b00010000;
    pos2 |= 0b00010000;
    pos3 |= 0b00010000;
  }

  writeDigitsToDisplay(pos1,pos2,pos3);
}
