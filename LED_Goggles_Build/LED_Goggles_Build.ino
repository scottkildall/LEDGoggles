/*
 *  LED_Goggles_Build
 *  
 *  Example by Scott Kildall
 *  
 *  Slowly builds up leds
 */
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
 
#define PIN 0

byte leftBitmask = 0x0;
byte rightBitmask = 0x0;

uint32_t eyeColor = 0x0000FF;       // RED COLOR

int cycleNum = 0;
#define MAX_CYCLES (50)

#define delayTime (250)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);
 
 
void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  randomSeed(analogRead(0));

  clearGoggles();
  eyeColor = random(0xFFFFFF);
}
 
void loop() {
  
  pixels.setPixelColor(random(32), eyeColor);
  pixels.show();
   
  delay(delayTime);
  cycleNum++;

  if( cycleNum >= MAX_CYCLES ) {
    cycleNum = 0;
    clearGoggles();
    delay(5000);
    eyeColor = random(0xFFFFFF);
  }
}

//-- set all to black
void clearGoggles() {
  for(int i=0; i<16; i++) {
      pixels.setPixelColor(i, 0x000000); // Second eye (flipped
      pixels.setPixelColor(i+16, 0x000000); // Second eye (flipped)
  }
  pixels.show();
}

