#ifndef _LINESENSOR_H
#define _LINESENSOR_H

#include "utils.h"

class lineSensor_c {

  public :
    int pin;
    int bias;

    // Constructor, accepts a pin number as arg and sets this as input.
    lineSensor_c( int which_pin ) {
      Serial.print( " In constructor " );
      pin = which_pin;
      pinMode(pin, INPUT);
    };


    // calibration routine here to remove bias offset
    void calibrate();
    // Write a routine here to check if your sensor is on a line (true or false).
    boolean onLine( float threshold );
    // gets the value i.e voltage of analogRead() for pin represented in class
    int getVoltage();
    int readCalibrated();

};

int lineSensor_c::getVoltage() {
  return analogRead(pin);
}

int lineSensor_c::readCalibrated() {
  return analogRead(pin) - bias;
}

void lineSensor_c::calibrate(){
  Serial.print( "calibrating... " );
  float value;
  int samples = 1;
  float sum = 0.0;
  float mean = 0.0;

  // mean of 100 readings
  while (samples <= 100){

    float next = analogRead(pin);
    //the current reading divided by the total number of samples
    mean = (mean * samples + next) / (samples + 1);

    samples+=1;
  }

   // add beeep
   Serial.print( "caliberation complete. \n" );
//   play_tone(80, 1000);
}

void weightedCalc(){
  
}


boolean lineSensor_c::onLine(float threshold){
    if (analogRead(pin) > threshold){ //then it sees blacks
      return true;   
    }
    else{
      return false;
    }
}

#endif
