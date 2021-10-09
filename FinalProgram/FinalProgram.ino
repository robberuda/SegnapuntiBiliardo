#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define less10a 2 //2
#define less1a  4 //3
#define plus1a  5 //4
#define plus10a 3 //5
#define less10b 8 //8
#define less1b  10 //7
#define plus1b  9 //10
#define plus10b 7 //9

#define zero 6
#define LEDS 13
#define NUMPIXELS 28

int antiB = 300;

struct score{
  int dozen;
  int unit;
  int nmonitor;
  }score;
  
Adafruit_NeoPixel pixels(NUMPIXELS, LEDS, NEO_GRB + NEO_KHZ800);

void sevenseg(int , int , uint8_t, uint8_t, uint8_t);
void increment(int , int , struct score *);
void decrement(int , int , struct score *);

void resetAllDysplay(struct score *, struct score *);

void easterEgg1();
void easterEgg4();
void easterEgg5();
void easterEgg7();
void easterEgg8();

struct score scoreA;
struct score scoreB;
struct score *pScoreA = &scoreA;
struct score *pScoreB = &scoreB;


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
    decrement(1, 0, pScoreA);
    while(digitalRead(less10a));
    delay(antiB);
  }
 
  if ( digitalRead(less1a)) {
    Serial.println("-1 monitor A");
    decrement(0, 1, pScoreA);
    while(digitalRead(less1a));
    delay(antiB);
  }
  
  if ( digitalRead(plus1a)) {
    Serial.println("+1 monitor A");
    increment(0, 1, pScoreA);
    while(digitalRead(plus1a));
    delay(antiB);
  }
  
  if ( digitalRead(plus10a)) {
    Serial.println("+10 monitor A");
    increment(1, 0, pScoreA);
    while(digitalRead(plus10a));
    delay(antiB);
  }



  if ( digitalRead(less10b)) {
    Serial.println("-10 monitor B");
    decrement(1, 0, pScoreB);
    while(digitalRead(less10b));
    delay(antiB);
  }
  
  if ( digitalRead(less1b)) {
    Serial.println("-1 monitor B");
    decrement(0, 1, pScoreB);
    while(digitalRead(less1b));
    delay(antiB);
  }
  
  if ( digitalRead(plus1b)) {
    Serial.println("+1 monitor B");
    increment(0, 1, pScoreB);
    while(digitalRead(plus1b));
    delay(antiB);
  }
  
  if ( digitalRead(plus10b)) {
    Serial.println("+10 monitor B");
    increment(1, 0, pScoreB);
    while(digitalRead(plus10b));
    delay(antiB);
  }


  if ( digitalRead(zero)) {
    Serial.println("AZZERA TUTTO");
    
    while(digitalRead(zero)){
      if ( digitalRead(less10a)){
        easterEgg1();
        while(digitalRead(less10a));
        delay(antiB);
        }
        
      if ( digitalRead(plus1a)){
        easterEgg4();
        while(digitalRead(plus1a));
        delay(antiB);
        }

      if ( digitalRead(less10b)){
        easterEgg5();
        while(digitalRead(less10b));
        delay(antiB);
        }
        
      if ( digitalRead(less1b)){
        easterEgg7();
        while(digitalRead(less1b));
        delay(antiB);
        }

      if ( digitalRead(plus1b)){
        easterEgg8();
        while(digitalRead(plus1b));
        delay(antiB);
        }
      };
    
    resetAllDysplay(pScoreA, pScoreB);
    delay(antiB);
  }
 
}

void increment(int dozens, int units, struct score *PlayerScores){
  
  if(dozens){
    if(PlayerScores->dozen == 10){
      PlayerScores->dozen = 10;
      PlayerScores->unit = 11;
      }
    else PlayerScores->dozen += 1;
    }
    
  else if(units){
    if(PlayerScores->unit == 9){
      if(PlayerScores->dozen == 10){
        PlayerScores->dozen = 10;
        PlayerScores->unit = 10;
        }
      else{
        PlayerScores->dozen += 1;
        PlayerScores->unit = 0;
        }
    }
    else if (PlayerScores->unit > 10){
      PlayerScores->unit = 11;
    }
    else PlayerScores->unit += 1;
    }

  if(PlayerScores->nmonitor == 1) {
    sevenseg(0, PlayerScores->dozen, 200, 0, 0);
    sevenseg(1, PlayerScores->unit, 200, 0, 0);
    } 
  else if(PlayerScores->nmonitor == 2) {
    sevenseg(2, PlayerScores->dozen, 0, 200, 0);
    sevenseg(3, PlayerScores->unit, 0, 200, 0);
    } 
  pixels.show();
}


void decrement(int dozens, int units, struct score *PlayerScores){
  if(dozens){
    if(PlayerScores->dozen == 0){
      PlayerScores->dozen = 0;
      PlayerScores->unit = 0;
      }
    else PlayerScores->dozen -= 1;
    }
  else if(units){
    if(PlayerScores->unit == 0){
      if(PlayerScores->dozen == 0){
        PlayerScores->dozen = 0;
        PlayerScores->unit = 0;
        }
      else{
        PlayerScores->dozen -= 1;
        PlayerScores->unit = 9;
        }
      }
    else PlayerScores->unit -= 1;
    }
    
  if(PlayerScores->nmonitor == 1) {
    sevenseg(0, PlayerScores->dozen, 200, 0, 0);
    sevenseg(1, PlayerScores->unit, 200, 0, 0);
    } 
    
  else if(PlayerScores->nmonitor == 2) {
    sevenseg(2, PlayerScores->dozen, 0, 200, 0);
    sevenseg(3, PlayerScores->unit, 0, 200, 0);
    } 
  pixels.show();
}


void resetAllDysplay(struct score *PlayerScoresA, struct score *PlayerScoresB){
  PlayerScoresA->dozen = 0;
  PlayerScoresA->unit = 0;
  PlayerScoresB->dozen = 0;
  PlayerScoresB->unit = 0;
  
  sevenseg(0, PlayerScoresA->dozen, 200, 0, 0);
  sevenseg(1, PlayerScoresA->unit, 200, 0, 0);
    
  sevenseg(2, PlayerScoresB->dozen, 0, 200, 0);
  sevenseg(3, PlayerScoresB->unit, 0, 200, 0);
  
  pixels.show();
  };

void easterEgg1(){
  for(int i=0; i<9;i++){
    sevenseg(0, i, 200,200,200); 
    sevenseg(1, i, 200,200,200); 
    sevenseg(2, i, 200,200,200); 
    sevenseg(3, i, 200,200,200);
    pixels.show(); 
    delay(200);
    }
  for(int i=20; i<31;i++){
    sevenseg(0, i, 200,200,200); 
    sevenseg(1, i, 200,200,200); 
    sevenseg(2, i, 200,200,200); 
    sevenseg(3, i, 200,200,200);
    pixels.show(); 
    delay(200);
    }
  for(int i=10; i<12;i++){
    sevenseg(0, i, 200,200,200); 
    sevenseg(1, i, 200,200,200); 
    sevenseg(2, i, 200,200,200); 
    sevenseg(3, i, 200,200,200);
    pixels.show(); 
    delay(200);
    }
  };

void easterEgg4(){
  sevenseg(0, 20, 150, 0, 255); //A
  sevenseg(1, 29, 150, 0, 255); //n
  sevenseg(2, 30, 150, 0, 255); //t
  sevenseg(3, 28, 150, 0, 255); //0
  pixels.show();
  };

void easterEgg5(){
  sevenseg(0, 22, 255,200,0); //C
  sevenseg(1, 1 , 255,200,0); //1
  sevenseg(2, 20, 255,200,0); //A
  sevenseg(3, 0 , 255,200,0); //0
  pixels.show();
  };
  
void easterEgg7(){
  sevenseg(0, 26, 0,100,200); //r
  sevenseg(1, 28,  0,100,200); //0
  sevenseg(2, 21, 0,100,200); //b
  sevenseg(3, 21, 0,100,200); //b
  pixels.show(); 
  };
  
void easterEgg8(){
  sevenseg(0, 26, 0,100,200); //r
  sevenseg(1, 27, 0,100,200); //u
  sevenseg(2, 23, 0,100,200); //d
  sevenseg(3, 20, 0,100,200); //A
  pixels.show(); 
  };


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

    case 10: //H
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) );
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) );
    break;

    
    case 20: //A
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) ); //RIGHT-UP
    break;
    case 21: //B
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;
    case 22: //C
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(0,0,0) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;
    case 23: //D
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(r,b,g) ); //RIGHT-UP
    break;
    case 24: //E
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;
    case 25: //F
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;
    
    case 26: //r
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(0,0,0) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(r,b,g) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;
    
    case 27: //u
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(0,0,0) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;

    case 28: //o
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;

    case 29: //n
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(r,b,g) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;

    case 30: //t
    pixels.setPixelColor( offset+0, pixels.Color(r,b,g) ); //LEFT-DOWN
    pixels.setPixelColor( offset+1, pixels.Color(r,b,g) ); //DOWN
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) ); //RIGHT-DOWN
    pixels.setPixelColor( offset+3, pixels.Color(r,b,g) ); //CENTER
    pixels.setPixelColor( offset+4, pixels.Color(r,b,g) ); //LEFT-UP
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) ); //UP
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) ); //RIGHT-UP
    break;
    
    default:
    pixels.setPixelColor( offset+0, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+1, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+2, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+3, pixels.Color(255,200,0) );
    pixels.setPixelColor( offset+4, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+5, pixels.Color(0,0,0) );
    pixels.setPixelColor( offset+6, pixels.Color(0,0,0) );
    break;
    
    }
}
