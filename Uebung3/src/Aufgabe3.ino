#include <Wire.h>
#include "frtrobotik_imu.h"
#include "essDisplay.h"
#include "essSerialMonitor.h"

/**
* @brief TASK 3 - IMU Sensor driver
*
* This tasks illustrates the use of the inertial sensor measurement unit (IMU).
* The access on sensor data is already implemented. You have to extend your
* existing project by :
*  - a method "viewBalance" in essDisplay.cpp
*    This additional visualization method illustrates the balance level in
*    2 directions (6 steps, 3 steps).
*
*  - a method "MPU9150_calculate_acc_SI" in frtrobotik_imu.cpp
*    The function displays the current G value for z axis in m/s^2
*
*  - a mapping algorithm for pitch and roll based on the acceleration
*    measurements
*
* Please add your essDisplay implementations to the essDisplay.cpp file.
*/

// a string to hold incoming data
String inputString = "";

// S = Display spirit level
// G = Display G value for z axis
char commandToBot = 'S';

// acceleration in m/s^2
float acc_SI_z;

// orientation of the sensor system compared to ground level
float pitch;
float roll;
float pitcharr[6];
float rollarr[6];
int counter;

/*! \brief Initialisation
 *
 *  This function initializes
 *       - serial communication (UART0)
 *       - 3x7 elements display
 *       - MPU 9250 acceleration sensor
 *  and lists user options.
 */
void setup() {

  float version = 0.4;
  Serial.begin(57600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  Serial.println("----------------------------------");
  Serial.println("PKES Wintersemester 2016/17"       );
  Serial.print  ("Vorlage 3. essBot - Version "      );
  Serial.println(version                             );
  Serial.println("----------------------------------");
  Serial.println("S = Display spirit level          ");
  Serial.println("G = Display G value for z axis    ");
  Serial.println("----------------------------------");

  initDisplay();
  // Example for illustrating the use of the display
  writeDigitsToDisplay(0b10011110, 0b10110110, 0b10110110);

  Wire.begin();
  // Clear the 'sleep' bit to start the sensor.
  MPU9150_writeSensor(MPU9150_PWR_MGMT_1, 0);
}

void loop() {
  // Exemplary output of acceleration data
  //Serial.print(MPU9150_readSensor(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H));
  //Serial.print("  ");
  //Serial.print(MPU9150_readSensor(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H));
  //Serial.print("  ");
  //Serial.print(MPU9150_readSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H));
  //Serial.println();

  if (commandToBot == 'G'){
      acc_SI_z = MPU9150_calculate_acc_SI(MPU9150_readSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H));
      float filteredvalue = filter(acc_SI_z,0);
      writeValueToDisplay(acc_SI_z, 1);
      Serial.print(filteredvalue);
      Serial.println();
  }
  if (commandToBot == 'S'){
      // TODO calculate pitch and roll based on accelaration measurements
      pitch = 0;
      roll = 0;

			float pitch_new;// = //measured value directly mapped with according function
			float pitch_ave = filter(pitch_new, 0);

			float roll_new;// = //measured value directly mapped with according function
			float roll_ave = filter(roll_new, 1);
      // TODO write a spirit level visualization
      //viewBalance(pitch_ave, roll_ave);
  }
  _delay_ms(200);
}

float filter(float raw_new, byte mode){
  //int length = sizeof(arr)/sizeof(arr[0]);
	if(mode == 0) pitcharr[counter%5]=raw_new;
	else rollarr[counter%5]=raw_new;
  float ave = 0;
  int i = 0;
  if(mode==0){
  while(pitcharr[i]!=0 ){
    ave += pitcharr[i];
    i++;
    }
  }
  else{
    while(rollarr[i]!=0 ){
      ave += rollarr[i];
      i++;
      }
  }
  counter++;
  return ave/i;
}
