#include "essSerialMonitor.h"

/*
  Interpretation of serial commands for task 1
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
      if (inputString[0]== 'S' || inputString[0]== 'G'){
          if (commandToBot == 'S' && inputString[0]== 'G'){
            commandToBot = 'G';
            Serial.println("Display G value for z axis");}
          else  if (commandToBot == 'G' && inputString[0]== 'S'){
            commandToBot = 'S';
            Serial.println("Display spirit level");}        
      }
      else{
        Serial.println("Invalid command!");
      }
      inputString = "";
    }
  }
}
