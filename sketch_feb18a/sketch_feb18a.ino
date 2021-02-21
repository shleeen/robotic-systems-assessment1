#define LINE_LEFT_PIN A4
#define LINE_CENTRE_PIN A3
#define LINE_RIGHT_PIN A2

void setup() {
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

}

void loop() {

  // To store result.
  int l_value; // left sensor
  int c_value; // centre sensor
  int r_value; // right sensor

  // Read analog voltages
  l_value = analogRead( LINE_LEFT_PIN );
  c_value = analogRead( LINE_CENTRE_PIN );
  r_value = analogRead( LINE_RIGHT_PIN );

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
