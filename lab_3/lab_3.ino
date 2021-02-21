#include "lineSensor.h"

#define LINE_LEFT_PIN A4 //Pin for the left line sensor
#define LINE_CENTRE_PIN A3 //Pin for the centre line sensor
#define LINE_RIGHT_PIN A2 //Pin for the right line sensor

const int THRESHOLD = 500;

lineSensor_c left(LINE_LEFT_PIN); //Create a line sensor object for the left sensor;
lineSensor_c centre(LINE_CENTRE_PIN);
lineSensor_c right(LINE_RIGHT_PIN);


void BangBang(int l_value, int c_value, int r_value){
   if (l_value.onLine() && c_value.onLine() && r_value.onLine() ){
   
   }
   else if(l.value.onLine() && !c_value.onLine() && !r_value.onLine() ) {
      //if only Left is on line
      //move LEFT???
   }
   else if(){
      //if only CENTRE is on line
      //move STRAIGHT???
   }
   else if(){
      //if only RIGHT is on line
      //move RIGHT???
   }
}



void setup() {  
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  
  // Calibrate the three line sensors.
  left.calibrate();
  centre.calibrate();
  right.calibrate();

}



void loop() {
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
  Serial.print( l_value );
  Serial.print( ", " );
  Serial.print( c_value );
  Serial.print( ", " );
  Serial.print( r_value );
  Serial.print( "\n" );

  delay(50);
}
