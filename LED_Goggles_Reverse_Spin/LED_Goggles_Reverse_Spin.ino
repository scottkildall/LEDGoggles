/*
 *  LED_Goggles_Random_Reverse_Spin 
 *  
 *  Example by Endri Deliu
 *  
 *  Simple spinny eyes, 
 *  
 *  Adapted from Scott Kidall LED_Goggles_Spin (https://github.com/scottkildall/LEDGoggles)
 */

#include <stdlib.h>     /* srand, rand */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
 
#define PIN 0

#define MAX_EYE_PIXELS (16)    // number of pixels in one eye

//active pixels left|right
int startPixelLeft = 0;
int startPixelRight = 16 + 8;

//active pixel colors left|right
int rgbLeft[3] = {rand()%255 + 1,rand()%255 + 1,rand()%255 + 1};
int rgbRight[3] = {rand()%255 + 1,rand()%255 + 1,rand()%255 + 1};

//non active pixel color
int rgbOff[3] = {0,0,0};
int rgbOffPulse = 10;

//these arrays just help me visualize rotation algorithms
//int leftEye[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//int rightEye[16] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};


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
  pixels.setBrightness(25); // 1/3 brightness
}

int randIncr(int limit){
  return rand() % limit + 1;  
}

int loopRound = 0;
void loop() {
  // Left Eye and Right Eye are reverse spinning

  loopRound++;

  //now go through all pixels to change color values
  for( int i = 0; i < MAX_EYE_PIXELS; i++ ) {

    //change color every two steps
    int incr = randIncr(5);
    if(i%2 == 0){
      rgbLeft[0] = rgbLeft[0] > 255 ? 0 : rgbLeft[0] + incr;  
      rgbLeft[1] = rgbLeft[1] > 255 ? 0 : rgbLeft[1] + incr;  
      rgbLeft[2] = rgbLeft[2] > 255 ? 0 : rgbLeft[2] + incr;

      rgbRight[0] = rgbRight[0] > 255 ? 0 : rgbRight[0] + incr;  
      rgbRight[1] = rgbRight[1] > 255 ? 0 : rgbRight[1] + incr;  
      rgbRight[2] = rgbRight[2] > 255 ? 0 : rgbRight[2] + incr;  
        
    }
    
    //shiftVal is right eye active pixel position in relation to left eye pixel
    //means if i > 8 set shift to 8 otherwise to 24
    int shiftVal = i>=8 ? 8 : 8 + 16;

    //now set the pixelcolors
    //left eye
    if( startPixelLeft == i ) {
      pixels.setPixelColor(i, rgbLeft[0], rgbLeft[1], rgbLeft[2], rgbOffPulse);
      pixels.setPixelColor(MAX_EYE_PIXELS - i, rgbRight[0], rgbRight[1], rgbRight[2], rgbOffPulse);
    
    }else {
      pixels.setPixelColor(i,rgbOff[0], rgbOff[1], rgbOff[2], rgbOffPulse);
    }

    //and right eye
    if(startPixelRight == i){
      pixels.setPixelColor( i + shiftVal, rgbRight[0], rgbRight[1], rgbRight[2]);
      pixels.setPixelColor(3 * MAX_EYE_PIXELS - (i + shiftVal), rgbLeft[0], rgbLeft[1], rgbLeft[2], rgbOffPulse);
    }else{
      pixels.setPixelColor(i + shiftVal ,rgbOff[0], rgbOff[1], rgbOff[2], rgbOffPulse);
      
    }
  }

  // startPixel will cause the rotate to happen
  startPixelLeft++;
  startPixelRight--;//this rotates in reverse cause of minus
  
  if( startPixelLeft == MAX_EYE_PIXELS ) {
    startPixelLeft = 0;
  }

  if( startPixelRight == 0 ) {
    startPixelRight = MAX_EYE_PIXELS;
  }
  
  
  pixels.show();

  //-- change the delay spped
  delay(delaySpeed);
  delaySpeed += delayIncrement;
  if( delaySpeed > 50 || delaySpeed < 1 )
    delayIncrement = -delayIncrement;
}
