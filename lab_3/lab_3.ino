#include "lineSensor.h"
#include "motor.h"

#define LINE_LEFT_PIN A2 //Pin for the left line sensor
#define LINE_CENTRE_PIN A3 //Pin for the centre line sensor
#define LINE_RIGHT_PIN A4 //Pin for the right line sensor
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

const int THRESHOLD = 500;

lineSensor_c left(LINE_LEFT_PIN); //a line sensor object for the left sensor
lineSensor_c centre(LINE_CENTRE_PIN);
lineSensor_c right(LINE_RIGHT_PIN);

motor_c motorL(L_PWM_PIN, L_DIR_PIN);
motor_c motorR(R_PWM_PIN, R_DIR_PIN);


void DriveStraight(){
  motorL.setMotorPower(20);
  motorR.setMotorPower(20);
}


void BangBang(){
  Serial.print("in bang bang \n");
  
  if (left.onLine(THRESHOLD) && centre.onLine(THRESHOLD) && right.onLine(THRESHOLD) ){
    Serial.print("hello \n");
    // move forward
    motorL.setMotorPower(20);
    motorR.setMotorPower(20);
  }
  else if(left.onLine(THRESHOLD) && !right.onLine(THRESHOLD) ) {
    //if only Left is on line, move LEFT???
    Serial.print("there \n");
    motorR.setMotorPower(15);
    motorL.setMotorPower(0);
  }
  else {
    motorL.setMotorPower(0);
    motorR.setMotorPower(0);
  }
//  else if(){
//    //if only CENTRE is on line
//    //move STRAIGHT???
//  }
//  else if(){
//    //if only RIGHT is on line
//    //move RIGHT???
//  }
}



void setup() {  
  // Start up the Serial for debugging.
  Serial.begin(9600);
  delay(1000);

//  pinMode(A2, INPUT);
//  pinMode(A3, INPUT);
//  pinMode(A4, INPUT);

  // Calibrate the three line sensors.
  left.calibrate();
  centre.calibrate();
  right.calibrate();

  // Print reset so we can catch any reset error.
  Serial.println(" ***Reset*** ");
}



void loop() {
  
}

// -------------- OLD LOOP
// To store result.
  int l_value; // left sensor
  int c_value; // centre sensor
  int r_value; // right sensor

  // Read analog voltages
  l_value = left.getVoltage();
  c_value = centre.getVoltage();
  r_value = right.getVoltage();

  // To send data back to your computer.
  // You can open either Serial monitor or plotter.
  if (left.onLine(500)){
    Serial.print( "left " );
    Serial.print( l_value );
    Serial.print( "\n" );
  }
  if (centre.onLine(500)){
    Serial.print( "centre " );
    Serial.print( c_value );
    Serial.print( "\n" );
  }
  if (right.onLine(500)){
    Serial.print( "right " );
    Serial.print( r_value );
    Serial.print( "\n" );
  }

  Serial.print( "\n" );

  // call bang bang
  BangBang();

  delay(50);

// -------- use serial plotter thingy
// //  Serial.print( l_value );
//  Serial.print( ", " );
//  Serial.print( c_value );
//  Serial.print( ", " );
//  Serial.print( r_value );
