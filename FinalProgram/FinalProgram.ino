#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define less10a 2
#define less1a  3
#define plus1a  4
#define plus10a 5
#define less10b 8
#define less1b  7
#define plus1b  10
#define plus10b 9
#define zero    6
#define LEDS 13
#define NUMPIXELS 28

int antiB = 300;

struct score{
  int dozen;
  int unit;
  int nmonitor;
  }score;
  
Adafruit_NeoPixel pixels(NUMPIXELS, LEDS, NEO_GRB + NEO_KHZ800);

void sevenseg(int displ, int number, uint8_t r, uint8_t g, uint8_t b);
void increment(int dozens, int units, struct score PlayerScores);
void decrement(int dozens, int units, struct score PlayerScores);

struct score scoreA;
struct score scoreB;



void setup() {
  Serial.begin(115200);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  delay(500);
  pixels.clear();

  pinMode(less10a, INPUT);
  pinMode(less1a, INPUT);
  pinMode(plus1a, INPUT);
  pinMode(plus10a, INPUT);
  pinMode(less10b, INPUT);
  pinMode(less1b, INPUT);
  pinMode(plus1b, INPUT);
  pinMode(plus10b, INPUT);
  pinMode(zero, INPUT);

  scoreA.nmonitor = 1;
  scoreA.dozen = 0;
  scoreA.unit = 0;
  scoreB.nmonitor = 2;
  scoreB.dozen = 0;
  scoreB.unit = 0;

  sevenseg(0, scoreA.dozen, 200, 0, 0);
  sevenseg(1, scoreA.unit, 200, 0, 0);
  sevenseg(2, scoreB.dozen, 0, 200, 0);
  sevenseg(3, scoreB.unit, 0, 200, 0);
  pixels.show();
}






void loop() {

  if ( digitalRead(less10a)) {
    Serial.println("-10 monitor A");
    decrement(1, 0, scoreA);
    while(digitalRead(less10a));
    delay(antiB);
  }
 
  if ( digitalRead(less1a)) {
    Serial.println("-1 monitor A");
    decrement(0, 1, scoreA);
    while(digitalRead(less1a));
    delay(antiB);
  }
  
  if ( digitalRead(plus1a)) {
    Serial.println("+1 monitor A");
   increment(0, 1, scoreA);
    while(digitalRead(plus1a));
    delay(antiB);
  }
  
  if ( digitalRead(plus10a)) {
    Serial.println("+10 monitor A");
    increment(1, 0, scoreA);
    while(digitalRead(plus10a));
    delay(antiB);
  }



  if ( digitalRead(less10b)) {
    Serial.println("-10 monitor B");
    decrement(1, 0, scoreB);
    while(digitalRead(less10b));
    delay(antiB);
  }
  
  if ( digitalRead(less1b)) {
    Serial.println("-1 monitor B");
    decrement(0, 1, scoreB);
    while(digitalRead(less1b));
    delay(antiB);
  }
  
  if ( digitalRead(plus1b)) {
    Serial.println("+1 monitor B");
    increment(0, 1, scoreB);
    while(digitalRead(plus1b));
    delay(antiB);
  }
  
  if ( digitalRead(plus10b)) {
    Serial.println("+10 monitor B");
    increment(1, 0, scoreB);
    while(digitalRead(plus10b));
    delay(antiB);
  }




  if ( digitalRead(zero)) {
    Serial.println("AZZERA TUTTO");
    while(digitalRead(zero));
    delay(antiB);
  }
 
}


void increment(int dozens, int units, struct score PlayerScores){
  if(dozens){
    if(PlayerScores.dozen == 10){
      PlayerScores.dozen = 10;
      PlayerScores.unit = 11;
      }
    else PlayerScores.dozen += 1;
    }
  else if(units){
    if(PlayerScores.unit == 9){
      if(PlayerScores.dozen == 10){
        PlayerScores.dozen = 10;
        PlayerScores.unit = 11;
        }
      else{
        PlayerScores.dozen += 1;
        PlayerScores.unit = 0;
        }
      }
    else PlayerScores.unit += 1;
    }

  if(PlayerScores.nmonitor == 1) {
    sevenseg(0, PlayerScores.dozen, 200, 0, 0);
    sevenseg(1, PlayerScores.unit, 200, 0, 0);
    } 
  else if(PlayerScores.nmonitor == 2) {
    sevenseg(2, PlayerScores.dozen, 0, 200, 0);
    sevenseg(3, PlayerScores.unit, 0, 200, 0);
    } 
  pixels.show();
}


void decrement(int dozens, int units, struct score PlayerScores){
  if(dozens){
    if(PlayerScores.dozen == 0){
      PlayerScores.dozen = 0;
      PlayerScores.unit = 0;
      }
    else PlayerScores.dozen -= 1;
    }
  else if(units){
    if(PlayerScores.unit == 0){
      if(PlayerScores.dozen == 0){
        PlayerScores.dozen = 0;
        PlayerScores.unit = 0;
        }
      else{
        PlayerScores.dozen -= 1;
        PlayerScores.unit = 9;
        }
      }
    else PlayerScores.unit -= 1;
    }
    
  if(PlayerScores.nmonitor == 1) {
    sevenseg(0, PlayerScores.dozen, 200, 0, 0);
    sevenseg(1, PlayerScores.unit, 200, 0, 0);
    } 
    
  else if(PlayerScores.nmonitor == 2) {
    sevenseg(2, PlayerScores.dozen, 0, 200, 0);
    sevenseg(3, PlayerScores.unit, 0, 200, 0);
    } 
  pixels.show();
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
