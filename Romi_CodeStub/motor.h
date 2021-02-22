#ifndef _MOTOR_H
#define _MOTOR_H

#define DIR_FWD LOW
#define DIR_BCK HIGH
//#define R_DIR_FWD LOW
//#define R_DIR_BCK HIGH

// A class to neatly contain commands for the motors, to take care of +/- values,
//  a min/max power value, & pin setup.

class Motor_c {
  public:
    int pwm_pin;
    int dir_pin;

    Motor_c( int pwm, int dir);

    void setMotorPower(float power);
};

// constructor
Motor_c::Motor_c(int pwm, int dir ) {
  pwm_pin = pwm;
  dir_pin = dir;
  // Set our motor driver pins as outputs.
  pinMode( pwm_pin, OUTPUT );
  pinMode( dir_pin, OUTPUT );
}

//check between 255 and -255 !!!!!!!!!!!!!!!!!1


/*
   This function writes the value power_in
   using digitalWrite() to the specified pin.
   This function checks for bad values.
*/
void Motor_c::setMotorPower(float power ) {
  float new_power = 0.0;

  //if negative, move BCK
  if (power < 0) {
    digitalWrite( dir_pin, DIR_BCK );
    new_power = 255 - power;
  }
  else { //move FWD
    digitalWrite( dir_pin, DIR_FWD );
    new_power = power;
  }

  analogWrite( pwm_pin, new_power );
}

#endif
