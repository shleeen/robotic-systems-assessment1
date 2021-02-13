// Pin definitions, to make the
// code easier to read.
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

#define L_DIR_FWD LOW
#define L_DIR_BCK HIGH
#define R_DIR_FWD LOW
#define R_DIR_BCK HIGH

int flag = 1; //1 -> increment

// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255
byte l_power;
byte r_power;

// Setup, only runs once when powered on.
void setup() {

  // Set our motor driver pins as outputs.
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );

  // Set initial direction for l and r
  // Which of these is foward, or backward?
  digitalWrite( L_DIR_PIN, L_DIR_FWD );
  digitalWrite( R_DIR_PIN, R_DIR_FWD );

  // Set initial l_power and r_power values.
  l_power = 0;
  r_power = 0;

  // Start up the Serial for debugging.
  Serial.begin(9600);
  delay(1000);
  // Print reset so we can catch any reset error.
  Serial.println(" ***Reset*** ");

}


void loop() {

  Serial.print("l_power: "); Serial.println(l_power);
  Serial.print("r_power: "); Serial.println(r_power);

  
  if (flag){ //increment 
    l_power = l_power + 1;
    r_power = r_power + 1;
    if (l_power >= 100){ //if reaches the limit, change flag
      flag = 0;
    }
  }
  else { // decrement
    l_power = l_power - 1;
    r_power = r_power - 1;
    if (l_power <=0){ //if reaches 0, change flaga
      flag = 1;
    }
  }


  // Send power PWM to pins, to motor drivers.
  analogWrite( L_PWM_PIN, l_power );
  analogWrite( R_PWM_PIN, r_power );

  // Brief pause
  delay(2000);

}
