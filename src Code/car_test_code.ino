#include <Servo.h>

#define en 3
#define a 4
#define b 2

Servo servo;

#define Speed 100

#define greenPin 6
#define redPin 5

void setup() {
  pinMode(en, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(greenPin, INPUT);
  pinMode(redPin, INPUT);
  servo.attach(5);
  servo.write(80);

  digitalWrite(en, LOW);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);

  delay(1000);

  moveLeft();
  delay(100);
  moveRight();
  delay(100);
  Stop();

}

void loop() {
  //  if (isGreen()) {
  //    moveLeft();
  //  } else if (isRed()) {
  //    moveRight();
  //  } else {
  //    moveForward();
  //  }
}


void moveLeft() {
  servo.write(120);
  analogWrite(en, 80);
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);

  delay(400);
  analogWrite(en, 70);
  for (int i = 120; i > 80; i--) {
    servo.write(i);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    delay(5);
  }

  for (int i = 80; i > 40; i--) {
    servo.write(i);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    delay(12);
  }
  
  servo.write(80);
}

void moveRight() {
  analogWrite(en, 80);
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);

  delay(400);
  analogWrite(en, 70);
  for (int i = 40; i < 80; i++) {
    servo.write(i);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    delay(5);
  }

  for (int i = 80; i < 120; i++) {
    servo.write(i);
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    delay(12);
  }

  servo.write(80);
}

void moveForward() {
}


void Stop() {
  servo.write(80);
  analogWrite(en, 0);
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  delay(50);
  digitalWrite(b, LOW);
}

bool isGreen() {
  bool state = !digitalRead(greenPin);
  if (state == true)
    return true;
  return false;
}

bool isRed() {
  bool state = !digitalRead(redPin);
  if (state == true)
    return true;
  return false;
}
