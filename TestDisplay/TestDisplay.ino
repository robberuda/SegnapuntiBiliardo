// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which LEDS on the Arduino is connected to the NeoPixels?
#define LEDS 13 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 28// Popular NeoPixel ring size

void sevenseg(int displ, int number, uint8_t r, uint8_t g, uint8_t b);

// When setting up the NeoPixel library, we tell it how many pixels,
// and which LEDS to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, LEDS, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

uint8_t r=0;  //150
uint8_t g=50;  //0
uint8_t b=150;//0
  
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED) 
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  /*
  for(int i=0; i<10; i++) { 
    sevenseg(0, i, r, g, b);
    sevenseg(1, i, g, r, b);
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(1000);
  }*/
  
  for(int i=0; i<11; i++) { 
    sevenseg(0, i, 200, 0, 0);
    sevenseg(2, i, 0, 200, 0);
    for(int j=0; j<10; j++) {
      sevenseg(1, j, 200, 0, 0);
      sevenseg(3, j, 0, 200, 0);
      pixels.show();   // Send the updated pixel colors to the hardware.
      delay(100);
    }
    
    //pixels.show();   // Send the updated pixel colors to the hardware.
    //delay(100);
  }
  
  
    
}





void sevenseg(int displ, int number, uint8_t r, uint8_t g, uint8_t b){
  int offset = displ*7;
  switch(number){
    case 0:
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 1:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 2:
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 3:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 4:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 5:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) );
    break;
    case 6:
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) );
    break;
    case 7:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 8:
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 9:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;
    case 10:
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;

    default:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+3, pixels.Color(228,22,198) );
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) );
    break;
    
    }
}
