/*
 *  LED_Goggles_Xmas
 *  
 *  Example by Scott Kildall
 *  
 *  A special one for the holidays. This will appear to spin
 *  the LEDs, mixing between red and green and creating a trailing effect
 *  
 *  Improves on the LED_Goggles_Spin sketch
 */
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
 
#define PIN 0
#define RAND_FREQUENCY 20
#define RAND_OFFSET_FRQUENCY 100

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);
 
uint8_t  offset       = 0;              // Position of spinny eyes
uint32_t redColor     = 0xFF0000;       // RED COLOR
uint32_t greenColor   = 0x00FF00;       // GREEN COLOR
uint32_t noColor      = 0x000000;       // BLACK COLOR

uint32_t leftColor;
uint32_t rightColor;

int delaySpeed = 30;
int delayIncrement = -1;

int offsetDirection = 1;    // 1 or -1

#define MAX_EYE_PIXELS (16)    // number of pixels in one eye
 
void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness

  // seed random number generator
  randomSeed(analogRead(0));
  leftColor = redColor;
  rightColor = greenColor;
}
 
void loop() {
  uint8_t  i;

  for(i=0; i<MAX_EYE_PIXELS; i++) {
     int extraOffset;

      // blank out all pixels
      pixels.setPixelColor(i, noColor); // First eye
      pixels.setPixelColor(MAX_EYE_PIXELS+i,  noColor );

      //-- this could be cleaner, but bascially will do a pixel change
      if( offset == i ) {
        pixels.setPixelColor(i, rightColor); // First eye
        pixels.setPixelColor(MAX_EYE_PIXELS+i, leftColor); // Second eye (flipped)

        //-- this creates a sort of 'trailing' effect that is nice
        extraOffset = offset + random(MAX_EYE_PIXELS-1);
        if( extraOffset >= MAX_EYE_PIXELS )
          extraOffset -= MAX_EYE_PIXELS;

         pixels.setPixelColor(extraOffset, rightColor); // First eye
         pixels.setPixelColor(MAX_EYE_PIXELS+extraOffset, leftColor); // Second eye (flipped)
      }
  }
    
    pixels.show();

    //-- Increment the for the start location
    offset += offsetDirection;
    if( offset == MAX_EYE_PIXELS )
      offset = 0;
    else if( offset == -1 )
       offset = MAX_EYE_PIXELS - 1;

    // Change delay to simulate movement
    causeDelay();
    
    // change left color
    if( random(RAND_FREQUENCY) == 2) 
      leftColor = flipColor(leftColor);

    // change right color
    else if( random(RAND_FREQUENCY) == 1 ) 
      rightColor = flipColor(rightColor);
}

//-- Red becomes Green, Green becomes Red
uint32_t flipColor( uint32_t currentColor ) {
  return (currentColor == greenColor) ? redColor : greenColor;
}

//-- first does a small delay and then will do a delay ramp
void causeDelay() {
  delay(delaySpeed);
  delaySpeed += delayIncrement;
  if( delaySpeed > 30 || delaySpeed < 1 ) {
      delayIncrement = -delayIncrement;
      // now, alter the delay speed, for kicks
      delaySpeed = 20 + random(20);
   }
}


