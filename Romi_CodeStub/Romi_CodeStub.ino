/*
       @@@@@@@@@@@&*           %@@@@@%       @@@@@@@@@    @@@@@@@@@  @@@@@@@@
       @@@@@@@@@@@@@@@     #@@@@@@@@@@@@    @@@@@@@@@@   @@@@@@@@@* @@@@@@@@@
       @@@@@@   @@@@@@   /@@@@@%  .@@@@@@    @@@/@@@@@ @@@@@@@@@@    @@@@@@
      &@@@@@##&@@@@@@   @@@@@@(   @@@@@@@   @@@,.@@@@@@@@,.@@@@@    @@@@@@
      @@@@@@@@@@@@@    &@@@@@@    @@@@@@   @@@@  @@@@@@@  @@@@@    (@@@@@
     @@@@@@  @@@@@@*   @@@@@@    @@@@@@   .@@@   @@@@@#  @@@@@@    @@@@@&
   @@@@@@@@   @@@@@@%  .@@@@@@@@@@@@@    @@@@@%  @@@@  @@@@@@@@  @@@@@@@@
  %@@@@@@@&   @@@@@@     #@@@@@@@@      @@@@@@   @@@   @@@@@@@/ @@@@@@@@%

  Provided by Paul O'Dowd Oct 2020
*/

#include "lineSensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "motor.h"
#include "pid.h"

// states 
#define STATE_INITIAL         0
#define STATE_DRIVE_FORWARDS  1
#define STATE_FOUND_LINE      2

#define LINE_LEFT_PIN A2 //Pin for the left line sensor
#define LINE_CENTRE_PIN A3 //Pin for the centre line sensor
#define LINE_RIGHT_PIN A4 //Pin for the right line sensor
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15
#define POWER_MAX 5

const int THRESHOLD = 500;
unsigned long timestamp;
int state = 0;

LineSensor_c sensor_L (LINE_LEFT_PIN); //a line sensor object for the left sensor
LineSensor_c sensor_C (LINE_CENTRE_PIN);
LineSensor_c sensor_R (LINE_RIGHT_PIN);

Motor_c motor_L (L_PWM_PIN, L_DIR_PIN);
Motor_c motor_R (R_PWM_PIN, R_DIR_PIN);


void MoveStraight() {
  if( sensor_L.onLine(THRESHOLD) || sensor_C.onLine(THRESHOLD) || sensor_R.onLine(THRESHOLD) ) {
      // stop moving!!
//      motor_L.setMotorPower(0);
//      motor_R.setMotorPower(0);
      Serial.println("on line! \n");
      // flash LED
      FlashLED(1000);
      // Trigger State Transition
      state = STATE_FOUND_LINE;
  } 
  else { 
      Serial.println("NOT line! \n");
      //keep going straight
      motor_L.setMotorPower(20);
      motor_R.setMotorPower(20);
  }
}

//Weighted Line Sensing
float WeightedCalc(){
  float I_l = sensor_L.getVoltage();
  float I_c = sensor_C.getVoltage();
  float I_r = sensor_R.getVoltage();

  float I_total = I_l + I_c + I_r;
  float prob[3];
  prob[0] = I_l/I_total;
  prob[1] = I_c/I_total;
  prob[2] = I_r/I_total;

  // check that prob sum to 1?
  float M = prob[0] - prob[1];
  Serial.print(M);
  Serial.print("\n");

  return M;
}

// BangBang controller with power scaling
void PowerScaling(float M){  
  float power_right = M * POWER_MAX * (-1);
  float power_left = M * POWER_MAX * (1);

//  motor_R.setMotorPower(power_right);
//  motor_L.setMotorPower(power_left);

//use this in bang bang?  
}

// bang bang controller for romi to follow line
void BangBang(float M){
  if (M < 0){
    //move right
//    motor_R.setMotorPower(10);
    motor_L.setMotorPower(15);
  }
  else if (M > 0){
    //move left
    motor_R.setMotorPower(15);
//    motor_L.setMotorPower(10);
  }
  else if (M == 0){
    //move straight
    motor_R.setMotorPower(15);
    motor_L.setMotorPower(15);
  }
  else{
    //move straight
    motor_R.setMotorPower(15);
    motor_L.setMotorPower(15);
  }
}


// Setup, only runs once when the power is turned on.
//However, if your Romi gets reset, it will run again.
void setup() {
  // These two function set up the pin change interrupts for the encoders.
  setupEncoder0();
  setupEncoder1();
  
  // Start up the serial port.
  Serial.begin(9600);

  // Delay to connect properly.
  delay(1000);

  //set up pins for Buzzer and LED
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, OUTPUT); //Buzzer pin

//  // Calibrate the three line sensors.
//  sensor_L.calibrate();
//  sensor_C.calibrate();
//  sensor_R.calibrate();

  // beep?

  // Set initial state, before robot begins to operate.
  state = STATE_INITIAL;

  // Record an initial timestamp.
  timestamp = millis();


  // Print a debug, so we can see a reset on monitor.
  Serial.println("***RESET***");

}


void loop() {
  float M = WeightedCalc();

//  MoveStraight();
//  // call bang bang
//  BangBang(M);

// Based on the value of STATE variable, run code for the appropriate robot behaviour.
  if( state == STATE_INITIAL ) {
    Serial.println( "in initial state" );
     InitialisingBeeps();

  } else if( state == STATE_DRIVE_FORWARDS ) {
    Serial.println( "in move forwards state" );
     MoveStraight();

  } else if( state == STATE_FOUND_LINE ) {
    Serial.print( " in found line state " );
     foundLineBeeps();
//      BangBang(M);

  } else {
      Serial.print("System Error, Unknown state: ");
      Serial.println( state );
  }
//  Serial.print( count_e0 );
//  Serial.print( ", ");
//  Serial.println( count_e1 );

//   Small delay so plotter graph keeps history
//  delay(2);
  delay(20);
}

// Function where Romi beeps 5 times, across a total of 5 seconds.
void InitialisingBeeps() {
  PlayBeep(3, 500);
  // Read any sensors...
  // ...any filtering or processing...
  // ...check any global variables...

  // Calibrate the three line sensors.
  sensor_L.calibrate();   PlayBeep(3, 500);
  sensor_C.calibrate();   PlayBeep(3, 500);
  sensor_R.calibrate();   PlayBeep(3, 500);

  PlayBeep(3, 500);

//  Serial.println(" LEFT ");
//  Serial.println(sensor_L.readCalibrated());
//  Serial.println(sensor_L.getVoltage());
//  delay(2000);
//  Serial.println(" CENTRE ");
//  Serial.println(sensor_C.readCalibrated());
//  Serial.println(sensor_C.getVoltage());
//  delay(2000);
//  Serial.println(" RIGHT ");
//  Serial.println(sensor_R.readCalibrated());
//  Serial.println(sensor_R.getVoltage());
//  delay(2000);
  
//  if( ????  ) {
    // calibrate ???

    // State behaviour code to run
    // when the conditions are still
    // correct. 

//  } else if( ????? ) {

    // Transition code.
    // ... tidy up any global variables.

    // Trigger State Transition
    state = STATE_DRIVE_FORWARDS;
//  }
}

//
void foundLineBeep() {
  motor_L.setMotorPower(0);
  motor_R.setMotorPower(0);
  PlayBeep(3, 500);
  PlayBeep(3, 500);
}

// Function to play a beep once at given volume, for delay_ms long
void PlayBeep(int volume, int delay_ms){
    analogWrite(6, volume);
    delay(delay_ms);
    analogWrite(6, 0);
    delay(delay_ms);
}

// Function to flash the built in LED once for delay_ms long
void FlashLED(int delay_ms){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delay_ms);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(delay_ms);
}
