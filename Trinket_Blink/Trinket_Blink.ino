/*
 *  TrinketBlnk
 *  
 *  by Scott Kildall
 *  
 *  Easy modification of the blink example. Run this first to
 *  make sure the trinket is working properly. The built-in LED
 *  will blink.
 *  
 *  By changing the delayTime, you will change the blink rate,
 *  good check to see if your sketch has taken.
 */

#define delayTime (500)

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 1 as an output.
  pinMode(1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delayTime);              // wait for a second
  digitalWrite(1, LOW);    // turn the LED off by making the voltage LOW
  delay(delayTime);              // wait for a second
}
