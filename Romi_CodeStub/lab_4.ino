//
//#include "lineSensor.h"
//#include "motor.h"
//
//
//#define LINE_LEFT_PIN A2 //Pin for the left line sensor
//#define LINE_CENTRE_PIN A3 //Pin for the centre line sensor
//#define LINE_RIGHT_PIN A4 //Pin for the right line sensor
//#define L_PWM_PIN 10
//#define L_DIR_PIN 16
//#define R_PWM_PIN  9
//#define R_DIR_PIN 15
//
////const int THRESHOLD = 500;
//
////int state = 0;
//
//lineSensor_c sensor_L (LINE_LEFT_PIN); //a line sensor object for the left sensor
//lineSensor_c sensor_C (LINE_CENTRE_PIN);
//lineSensor_c sensor_R (LINE_RIGHT_PIN);
//
//Motor_c motor_L (L_PWM_PIN, L_DIR_PIN);
//Motor_c motor_R (R_PWM_PIN, R_DIR_PIN);
//
//
///*
// * 
// */
//void DriveStraight() {
//  motor_L.setMotorPower(20);
//  motor_R.setMotorPower(20);
//}
//
//
///*
// * Setup, only runs once when the power is turned on.
// * However, if your Romi gets reset, it will run again
// */
//void setup() {
//  // Start up the serial port.
//  Serial.begin(9600);
//
//  // Delay to connect properly.
//  delay(1000);
//
//  // Calibrate the three line sensors.
//  sensor_L.calibrate();
//  sensor_C.calibrate();
//  sensor_R.calibrate();
//
//  //
//
//  // Print a debug, so we can see a reset on monitor.
//  Serial.println("***RESET***");
//
//} // end of setup()
//
//
//
//void loop() {
//
//  Serial.println(" loop ");
//  delay(20);
//
//} // end of loop()
