/*
 *  NeoPixel_Goggles_Fun
 *  
 *  Example by Scott Kildall
 *  
 *  This selects a random color and will fade up and fade down.
 *  The delay value also changes, randomly to make it look a little
 *  less predictive.
 */
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
 
#define PIN 0
#define MAX_EYE_PIXELS (16)    // number of pixels in one eye
#define MAX_BRIGHTNESS (85)     // 1/3rd brightness, should be plenty

int r = 0;
int g = 0;
int b = 255;


int brightIncrement = -1;

//-- brightness variable that we fade up and adown
int brightness = 50;
int delayValue = 10;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);
 
void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(brightness);   // set to inital value
}
 
void loop() {
  // Left Eye and Right Eye are mirrored
  for( int i = 0; i < MAX_EYE_PIXELS; i++ ) {
    pixels.setPixelColor(i, r, g, b);
    pixels.setPixelColor(i + 16,r,g,b);
  }

  //-- adjust brightness
  pixels.setBrightness(brightness);
  pixels.show();
  delay(delayValue);

  //-- check brightness for out of bounds
  checkBrightness();
}

//-- ramp up and then ramp down. On ramp down, we change the RGB value
void checkBrightness() {
  brightness += brightIncrement;
  
  if( brightness > MAX_BRIGHTNESS )
    brightIncrement = -brightIncrement;
  
  else if(  brightness < 1 ) {
    brightIncrement = -brightIncrement;
    
    r = random(255);
    g = random(255);
    b = random(255);

    delayValue = 1 + (random(10) * 2);
  }
}

