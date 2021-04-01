/* test pulsanti, PINOUT:
  D0 = -10A
  D1 = -1A
  D2 = +1A
  D3 = +10A
  D4 = -10B
  D5 = -1B
  D6 = +1B
  D7 = +10B
  D8 = all zeros
  D9 = DISPLAY 
  
*/

#define less10a 2
#define less1a  3
#define plus1a  4
#define plus10a 5
#define less10b 8
#define less1b  7
#define plus1b  10
#define plus10b 9
#define zero    6

int antiB = 300;

void setup() {
  Serial.begin(115200);
  pinMode(less10a, INPUT);
  pinMode(less1a, INPUT);
  pinMode(plus1a, INPUT);
  pinMode(plus10a, INPUT);
  pinMode(less10b, INPUT);
  pinMode(less1b, INPUT);
  pinMode(plus1b, INPUT);
  pinMode(plus10b, INPUT);
  pinMode(zero, INPUT);
}

void loop() {

  if ( digitalRead(less10a)) {
    Serial.println("-10 monitor A");
    while(digitalRead(less10a));
    delay(antiB);
  }
 
  if ( digitalRead(less1a)) {
    Serial.println("-1 monitor A");
    while(digitalRead(less1a));
    delay(antiB);
  }
  
  if ( digitalRead(plus1a)) {
    Serial.println("+1 monitor A");
    while(digitalRead(plus1a));
    delay(antiB);
  }
  
  if ( digitalRead(plus10a)) {
    Serial.println("+10 monitor A");
    while(digitalRead(plus10a));
    delay(antiB);
  }



  if ( digitalRead(less10b)) {
    Serial.println("-10 monitor B");
    while(digitalRead(less10b));
    delay(antiB);
  }
  
  if ( digitalRead(less1b)) {
    Serial.println("-1 monitor B");
    while(digitalRead(less1b));
    delay(antiB);
  }
  
  if ( digitalRead(plus1b)) {
    Serial.println("+1 monitor B");
    while(digitalRead(plus1b));
    delay(antiB);
  }
  
  if ( digitalRead(plus10b)) {
    Serial.println("+10 monitor B");
    while(digitalRead(plus10b));
    delay(antiB);
  }




  if ( digitalRead(zero)) {
    Serial.println("AZZERA TUTTO");
    while(digitalRead(zero));
    delay(antiB);
  }
 
}
