#ifndef _KINEMATICS_H
#define _KINEMATICS_H

#define PI 3.1415926535897932384626433832795

//You may want to use some/all of these variables
//const float DIAMETER = 69.0f;
const float RADIUS = 35.0;
//const float L ; //

// for 1 revolution of wheel -> 1440 counts
const float MM_PER_COUNT = ((2*PI) / 1440.0) * RADIUS; // dist travelled (in mm) for 1 count
// this should be 0.15mm...


class kinematics_c {
  public:

    // Function Prototypes
    kinematics_c();   // constructor 
    void update();    // update kinematics
    float getX();
    float getY();
    float getTheta();

   private:
   
    float x;
    float y;
    float theta;

    float prev_e0;
    float prev_e1;
};


kinematics_c::kinematics_c() {
  x = 0;
  y = 0;
  theta = 0;
  prev_e0 = 0;
  prev_e1 = 0;  
} 


// Routine to execute the update to kinematics 
void kinematics_c::update() {
  // Calculate the change in encoder count since the last update
  float change_in_e0 = count_e0 - prev_e0;
  float change_in_e1 = count_e1 - prev_e1;
  prev_e0 = count_e0;
  prev_e1 = count_e1;
  
  // Convert this change to an appropriate unit (mm or cm)
//  ???   

  float angular_v_L = change_in_e0 * MM_PER_COUNT;
  float angular_v_R = change_in_e1 * MM_PER_COUNT;

  // mean change in encoder count
  float d = (angular_v_L + angular_v_R)/2.0;
  
  x += d * cos(theta);
  y += d * sin(theta);
//  theta +=
  Serial.print( x );
  Serial.print( "," );
  Serial.println( y );
  
}

float kinematics_c::getX(){
  return x;
}

float kinematics_c::getY(){
  return y;
}

float kinematics_c::getTheta(){
  return theta;
}

#endif
