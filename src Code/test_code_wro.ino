#include <Servo.h>

#define led 13
#define irfront 11

#define MiddleUltraPin 8
#define LeftUltraPin 10
#define RightUltraPin 6

#define in1 2
#define in2 4
#define en 3

#define servoPin 5
#define irfront 11
#define irleft 9
#define irright 10

Servo steering;

int lastvalue = 5;

uint16_t distance_middle = 0;
uint16_t distance_left = 0;
uint16_t distance_right = 0;

uint16_t readUltrasonic(uint8_t EchoAndTrigPins);
void readDistance(uint8_t M, uint16_t *M_distance,
                  uint8_t L, uint16_t *L_distance, uint8_t R, uint16_t *R_distance);

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
  digitalWrite(led, LOW);
  readDistance(MiddleUltraPin, &distance_middle,
               LeftUltraPin, &distance_left, RightUltraPin, &distance_right);
  delay(1000);
}

void loop() {
  readDistance(MiddleUltraPin, &distance_middle,
               LeftUltraPin, &distance_left, RightUltraPin, &distance_right);

  Serial.print("  M: "); Serial.print(distance_middle);
  Serial.print("  L: "); Serial.print(distance_left);
  Serial.print("  R: "); Serial.print(distance_right); Serial.println();


  if (digitalRead(irfront) == 1 ) {
    delay(10);
    if (digitalRead(irfront) == 1 ) {

      steering.write(120);
      backward(255, 300);
      steering.write(80);
      forward(255, 300);
    }
  }

  else if (digitalRead(irleft) == 1 ) {
    delay(10);
    if (digitalRead(irleft) == 1 ) {
      steering.write(120);
      forward(255, 10);
      lastvalue = 3;
    }
  }
  else if (digitalRead(irright) == 1 ) {
    delay(10);
    if (digitalRead(irright) == 1 ) {

      steering.write(40);
      forward(255, 10);
      lastvalue = 7;
    }
  }
  else {
    steering.write(80);
    forward(255, 10);
  }
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

void readDistance(uint8_t M, uint16_t *M_distance,
                  uint8_t L, uint16_t *L_distance, uint8_t R, uint16_t *R_distance) {
  *M_distance = readUltrasonic(M);
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

void backward(uint8_t _speed, uint16_t _delay) {
  analogWrite(en, _speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(_delay);
  Stop();
}


void Stop() {
  digitalWrite(en, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
