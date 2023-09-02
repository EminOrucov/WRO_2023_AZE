#include <Servo.h>

#define led 13

#define LeftCornerUltraPin 9
#define MiddleUltraPin 8 
#define RightCornerUltraPin 7 

#define LeftUltraPin 10
#define RightUltraPin 6

#define in1 2
#define in2 4
#define en  3

#define servoPin 5

Servo steering;

uint16_t distance_leftCorner = 0;
uint16_t distance_middle = 0;
uint16_t distance_rightCorner = 0;
uint16_t distance_left = 0;
uint16_t distance_right = 0;

bool clockwise = false;
bool counterClockwise = false;

uint16_t readUltrasonic(uint8_t EchoAndTrigPins);
void readDistance(uint8_t *LC, uint16_t *LC_distance, uint8_t *M, uint16_t *M_distance, uint8_t *RC, uint16_t *RC_distance,
                  uint8_t *L, uint16_t *L_distance, uint8_t *R, uint16_t *R_distance);

void forward(uint8_t _speed, uint16_t _delay);
void Stop();

void setup() {
  Serial.begin(9600);
  steering.attach(servoPin);
  steering.write(80);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);
  
  pinMode(led, OUTPUT);
//  for (int i = 0; i <= 3; i++) {
//    digitalWrite(led, !digitalRead(led));
//    delay(1000);
//  }
  digitalWrite(led, LOW);
  readDistance(LeftCornerUltraPin, distance_leftCorner, MiddleUltraPin,
                 distance_middle, RightCornerUltraPin, distance_rightCorner,
                 LeftUltraPin, distance_left, RightUltraPin, distance_right);
}

void loop() {

  readDistance(LeftCornerUltraPin, &distance_leftCorner, MiddleUltraPin,
                 &distance_middle, RightCornerUltraPin, &distance_rightCorner,
                 LeftUltraPin, &distance_left, RightUltraPin, &distance_right);

  Serial.print("  LC: "); Serial.print(distance_leftCorner);
  Serial.print("  M: "); Serial.print(distance_middle); 
  Serial.print("  RC: "); Serial.print(distance_rightCorner);
  
  Serial.print("  L: "); Serial.print(distance_left);
  Serial.print("  R: "); Serial.print(distance_right);Serial.println();

  if (distance_left > 100 && distance_right < 200) {
     
  }
  
  if (distance_leftCorner < 40 || distance_middle < 40 || distance_rightCorner < 40) {

     
     if (distance_middle < 25 and distance_middle !=0) {
      Serial.println("sdad");
      steering.write(40);
      forward(120, 500);
      steering.write(120);
      forward(120, 500);
      steering.write(80);
    } 


//    // left middle right
//    if (distance_leftCorner < 50 && distance_middle < 50 && distance_rightCorner < 50) {
//    } 
//    // left, middle    
//    else if (distance_leftCorner < 50 && distance_middle < 50 && distance_rightCorner > 50) {
//    } 
//    // middle, right
//    else if (distance_leftCorner > 50 && distance_middle < 50 && distance_rightCorner < 50) {
//    } 
//    // left, right
//    else if (distance_leftCorner < 50 && distance_middle > 50 && distance_rightCorner < 50) {
//    } 
//    // only left
//    else if (distance_leftCorner < 50 && distance_middle > 50 && distance_rightCorner > 50) {
//    } 
//    // only middle
//    else if (distance_leftCorner > 40 && distance_middle < 20 && distance_rightCorner > 40) {
//    } 
//    // only right
//    else if (distance_leftCorner > 50 && distance_middle > 50 && distance_rightCorner < 50) {
//    } 
  }else {
    steering.write(80);
  }
  delay(500);
}


uint16_t readUltrasonic(uint8_t EchoTrigPins) {
  long duration = 0;
  long distance = 0;
  pinMode(EchoTrigPins, OUTPUT);
  digitalWrite(EchoTrigPins, LOW);
  delayMicroseconds(2);
  digitalWrite(EchoTrigPins, HIGH);
  delayMicroseconds(10);
  digitalWrite(EchoTrigPins, LOW);

  pinMode(EchoTrigPins, INPUT);
  duration = pulseIn(EchoTrigPins, HIGH, 20000);
  distance = duration * 0.0343 / 2;
 
  return distance;
}


void readDistance(uint8_t LC, uint16_t *LC_distance, uint8_t M, uint16_t *M_distance, uint8_t RC, uint16_t *RC_distance,
                  uint8_t L, uint16_t *L_distance, uint8_t R, uint16_t *R_distance) {

  *LC_distance = readUltrasonic(LC);
  *M_distance = readUltrasonic(M);
  *RC_distance = readUltrasonic(RC);
  *L_distance = readUltrasonic(L);
  *R_distance = readUltrasonic(R);

}

void forward(uint8_t _speed, uint16_t _delay) {
  analogWrite(en, _speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(_delay);  
  Stop();
}

void Stop() {
  digitalWrite(en, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
}
