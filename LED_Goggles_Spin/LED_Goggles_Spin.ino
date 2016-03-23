/*
 *  LED_Goggles_Spin
 *  
 *  Example by Scott Kildall
 *  
 *  Very simple red-and-blue spinny eyes
 */
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
 
#define PIN 0

 #define MAX_EYE_PIXELS (16)    // number of pixels in one eye
int startPixel = 0;
int r = 0;
int g = 0;
int b = 255;

int delaySpeed = 30;
int delayIncrement = -1;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);
 
uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
 
void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
}
 
void loop() {
  // Left Eye and Right Eye are mirrored
  for( int i = 0; i < MAX_EYE_PIXELS; i++ ) {
    if( startPixel == i ) {
      pixels.setPixelColor(i, r, g, b);
      pixels.setPixelColor(i + 16, 255, 0,0);
    }
    else {
      pixels.setPixelColor(i,0);
      pixels.setPixelColor(i + 16,0);
    }
  }

  // startPixel will cause the rotate to happen
  startPixel++;
  if( startPixel == MAX_EYE_PIXELS ) {
    startPixel = 0;
  }
  
  pixels.show();

  //-- change the delay spped
  delay(delaySpeed);
  delaySpeed += delayIncrement;
  if( delaySpeed > 30 || delaySpeed < 1 )
    delayIncrement = -delayIncrement;
}
