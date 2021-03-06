#include <Arduino.h>

/**
* @brief TASK 2 - IR Sensor driver
*
* This tasks illustrates the aggregation of a infrared distance measurements
* their processing and visulalization. All robots are equipted with a long
* and a short distance sensor. Both sensor types have different characteristics
* Please take a view to the data sheets to get more information related to
* covered distances. Additionally, dont miss to check the ADC channel related
* to the chosen plugs.!
*
* The essSerialMonitor provides a switch function between both sensor types.
* Transmit a 'SE' for this purpose.
*
* During the initialisation phase the ADC has to be configured. The main loop
* generates, linearize and filter the ADC data. Find an appropriate threshold
* to guarantee an responsible output (otherwise the display should show an
* error). In detail, you have to implement:
* + in essIRsensor.cpp
*     -void configADC();
*     -linearizeDistanceShort(int distanceRaw);
*     -linearizeDistanceLong(int distanceRaw);
*     -readADC(int8_t channel);
* + Aufgabe2.ino
*     -filter()  We do not define a function header here, feel free to
*                find an appropriate solution.
*     -checkTreshold()
*/

#include "essDisplay.h"
#include "essSerialMonitor.h"
#include "essIRsensor.h"

// a string to hold incoming data
String inputString = "";

// status variable
byte sensor = 0;

// distance variables
int distance_raw;
float distance_lin;
float distance_avr;
int counter=0;
<<<<<<< HEAD
=======
int arr[21];
>>>>>>> d4b1f7da966c61100267152e9bedd38ef521b729

// level variables
static float xyz_GyrAccMag[9];

/*! \brief Initialisation
 *
 *  This function initializes
 *       - serial communication (UART0)
 *       - 3x7 elements display
 *       - MPU 9250 acceleration sensor
 *       - ADC configuration
 *  and lists user options.
 */
void setup() {

  float version = 0.4;
  Serial.begin(57600);  	// changed
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  Serial.println("----------------------------------");
  Serial.println("PKES Wintersemester 2016/17"       );
  Serial.print  ("Vorlage 2. essBot - Version "      );
  Serial.println(version                             );
  Serial.println("----------------------------------");
  Serial.println("S = switch between long and short ");
  Serial.println("    distance sensor"               );
  Serial.println("----------------------------------");

  initDisplay();
  // Example for illustrating the use of the display

  writeDigitsToDisplay(0b10011110, 0b10110110, 0b10110110);

  configADC();
}

/*! \brief Coordinates sensor measurements and visualization
 *
 *  The loop function is executed 20 times per second. It manipulates the
 *  display depending on the choosen sensor.
 */
void loop() {
<<<<<<< HEAD
  if (sensor == 0){
      distance_raw = readADC(1);  // <- Check the channel ID for your
      int distance_temp = filter(distance_raw);
      // TODO: Include a filter here
      }
  else{
      distance_raw = readADC(2); // <- Check the channel ID
      int distance_temp = filter(distance_raw);
      //distance_lin = linearizeDistanceLong(distance_raw);
      // TODO: Include a filter here
  }
  writeValueToDisplay(distance_raw);
=======
  int distance_temp;
  bool over = false;
  if (sensor == 0){
      distance_raw = readADC(1);  // <- Check the channel ID for your
      distance_temp = filter(distance_raw);
      distance_lin = linearizeDistanceLong(distance_temp);
      if(distance_lin > 60.0){
        writeDigitsToDisplay(displayMask('E'), displayMask('r'), displayMask('r'));
        over = true;
      }
      if(distance_lin < 30.0){
        writeDigitsToDisplay(displayMask('E'), displayMask('r'), displayMask('r'));
        over = true;
      }
      }
  else{
      distance_raw = readADC(2); // <- Check the channel ID
      distance_temp = filter(distance_raw);
      distance_lin = linearizeDistanceShort(distance_temp);
      if(distance_lin > 31.0){
        writeDigitsToDisplay(displayMask('E'), displayMask('r'), displayMask('r'));
        over = true;
      }
      if(distance_lin < 4.0){
        writeDigitsToDisplay(displayMask('E'), displayMask('r'), displayMask('r'));
        over = true;
      }
  }
  //Serial.println(distance_lin);
  //Serial.print("Temp: ");
  //Serial.println(distance_temp);
  //Serial.print("Lin: ");
  Serial.println(distance_lin);
  if(over==false){
    writeValueToDisplay(distance_lin,1);
  }
>>>>>>> d4b1f7da966c61100267152e9bedd38ef521b729
  delay(50);
}

int filter(int distance_new){
<<<<<<< HEAD
  int arr[5];
  arr[counter%5]=distance_new;
  int ave = 0;
  int length = sizeof(arr)/sizeof(arr[0]);
  for(int i = 0; i<length-1; i++){
    if(arr[i]!= NULL){
      ave += arr[i];
    }
  }
  counter++;
  return ave/length;
=======
  //int length = sizeof(arr)/sizeof(arr[0]);
  arr[counter%20]=distance_new;
  int ave = 0;
  int i = 0;
  while(arr[i]!=0){
    ave += arr[i];
    i++;
  }
  counter++;
  return ave/i;
>>>>>>> d4b1f7da966c61100267152e9bedd38ef521b729
}
