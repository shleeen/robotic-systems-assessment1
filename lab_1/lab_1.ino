/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

int number_of_led_flashes = 0;
bool toggle = false;

void flash_leds (int delay_ms){
    if( number_of_led_flashes < 5 ) {
      // do flashing LED behaviour AND COUNTING
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(delay_ms);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(delay_ms);

      number_of_led_flashes += 1;
      Serial.print("Number of flashes: ");  // no newline character
      Serial.println(number_of_led_flashes);
    }
    else {
      // delay for a bit, then restart
      delay(delay_ms*2);
      number_of_led_flashes = 0;
    }
} //function call


void fast_flashing(){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}


void play_tone(int volume, int delay_ms){
    analogWrite(6, volume);
    delay(delay_ms);
    analogWrite(6, 0);
//    delay(delay_ms);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  // LED_BUILTIN -> pin connected to a built in LED
  // Pin 13 almost always LED thats built in
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, OUTPUT); //Buzzer pin

  //Start a serial connection
  Serial.begin(9600);

  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");
  
}

// the loop function runs over and over again forever
void loop() {
//  flash_leds(1000);
////  play_tone(10, 5000);

//   Serial.println("Hello, from the Romi");

  //This line checks whether there is anything to read
  if ( Serial.available() ) {
      char inChar = Serial.read(); //This reads one byte

      if (inChar =='l') {
          flash_leds(500);
//          toggle = false;
      }
      else if (inChar == 'r'){
        Serial.println(" in r");
        if (toggle == true) {
          Serial.println(" in toggle is true ");
          toggle = false;
          flash_leds(100);
        }
        else if(toggle == false){
          Serial.println(" in toggle is false ");
          toggle = true;
          fast_flashing();
        }
      }
  }
  
}
