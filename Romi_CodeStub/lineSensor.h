#ifndef _LINESENSOR_H
#define _LINESENSOR_H

class LineSensor_c {

  public :
    int pin;
    int bias;

    // Constructor, accepts a pin number as arg and sets this as input.
    LineSensor_c( int which_pin ) {
      Serial.print( " In constructor " );
      pin = which_pin;
      pinMode(pin, INPUT);
      bias = 0;
    };

    // Member functions for class
    void calibrate();
    boolean onLine( float threshold );
    int getVoltage();
    int readCalibrated();

};


// Returns the voltage of analogRead() for pin represented in class
int LineSensor_c::getVoltage() {
  return analogRead(pin);
}


// Returns the calibrated value of voltage
int LineSensor_c::readCalibrated() {
  return analogRead(pin) - bias;
}


// Calibration routine to remove bias offset.
void LineSensor_c::calibrate(){
  Serial.print( "calibrating... " );
  float value;
  int samples = 1;
  float sum = 0.0;
  float mean = 0.0;

  // mean of 100 readings
  while (samples <= 100){

    float next = analogRead(pin);
    //the current reading divided by the total number of samples
    mean = mean + (( next - mean) / (samples + 1));

    samples+=1;
  }

   bias = mean;
   Serial.print( "calibration complete. \n" );
   delay(2000);
}


// Checks if sensor is on a line (returns true or false).
boolean LineSensor_c::onLine(float threshold){
    if (analogRead(pin) > threshold){ //then it sees blacks
      return true;   
    }
    else{
      return false;
    }
}

#endif
