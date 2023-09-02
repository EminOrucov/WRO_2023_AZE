#include <Servo.h>

#define en 3
#define a 4
#define b 2

Servo servo;

#define Speed 100

void setup() {
  pinMode(en, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);

  servo.attach(5);
  servo.write(80);

  digitalWrite(en, LOW);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);

  delay(1000);

  //  forward(100);
  //  delay(300);
  //  left(100);
  //  delay(300);
  //  right(105);
  //  delay(450);
  //  right(120);
  //  delay(300);
  servo.write(120);
  analogWrite(en, 100);
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);

  delay(300);
  analogWrite(en, 80);

  for (int i = 120; i > 60; i--) {
    servo.write(i);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    delay(7);
  }  
  for (int i = 60; i < 80; i++) {
    servo.write(i);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    delay(25);
  }

  Stop();
  servo.write(80);
}

void loop() {
}

void forward(int _speed) {
  analogWrite(en, _speed);
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
}

void backward(int _speed) {
  // backward
  analogWrite(en, _speed);
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
}

void left(int _speed) {
  servo.write(120);
  forward(_speed);
  delay(100);
}

void right(int _speed) {
  servo.write(40);
  forward(_speed);
  delay(100);
}

void Stop(void) {
  digitalWrite(en, LOW);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
}
