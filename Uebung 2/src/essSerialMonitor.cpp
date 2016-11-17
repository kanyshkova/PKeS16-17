#include "essSerialMonitor.h"

/*
  Interpretation of serial commands for task 2
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 'E') {
      if (inputString[0]== 'U' || inputString[0]== 'D' || inputString[0]== 'S'){
          if (sensor == 0 && inputString[0]== 'S'){
            sensor = 1;
            Serial.println("Switch to left distance sensor");}
          else  if (sensor == 1 && inputString[0]== 'S'){
            sensor = 0;
            Serial.println("Switch to right distance sensor");}          
      }
      else{
        Serial.println("Invalid command!");
      }
      inputString = "";
    }
  }
}

