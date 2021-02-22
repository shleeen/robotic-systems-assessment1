#ifndef _MOTOR_H
#define _MOTOR_H

// A class to neatly contain commands for the motors, to take care of +/- values, 
//  a min/max power value, & pin setup.

class motor_c {
  public:
    int pwm_pin;
    int dir_pin;

    motor_c( int pwm, int dir);

    void setMotorPower(float power);
};

// constructor
motor_c::motor_c(int pwm, int dir ) {
  pwm_pin = pwm;
  dir_pin = dir;
  // Set our motor driver pins as outputs.
  pinMode( pwm_pin, OUTPUT );
  pinMode( dir_pin, OUTPUT );
}

//check between 255 and -255 !!!!!!!!!!!!!!!!!1

void motor_c::setMotorPower(float power ){
  float new_power = 0.0;

 //if negative, move BCK
  if (power < 0){
    digitalWrite( dir_pin, HIGH );
    new_power = 255 - power;
  }
  else{ //move FWD
    digitalWrite( dir_pin, LOW );
    new_power = power;
  }
  
  analogWrite( pwm_pin, new_power );
}

#endif
