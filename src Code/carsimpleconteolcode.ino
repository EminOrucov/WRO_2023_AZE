#include <Servo.h>

// Motor control pins
const int motorPin1 = 2;  // Input 1 of L293D
const int motorPin2 = 4;  // Input 2 of L293D
const int enablePin = 3;  // Enable pin (speed control) of L293D

// Servo motor control pin
const int servoPin = 5;

// Create a Servo object
Servo servoMotor;

void setup() {
  // Setup motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Attach the servo motor to its control pin
  servoMotor.attach(servoPin);
}

void loop() {
  // Call functions to control the car movement and turning
  moveCarForward(); // Move the car forward
  delay(2000); // Wait for 2 seconds

  turnLeft(); // Turn the car left
  delay(1000); // Wait for 1 second

  moveCarBackward(); // Move the car backward
  delay(2000); // Wait for 2 seconds

  turnRight(); // Turn the car right
  delay(1000); // Wait for 1 second
}

void moveCarForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 200); // Full speed (255 is the maximum value)
}

void moveCarBackward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, 200); // Full speed (255 is the maximum value)
}

void stopCar() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void turnLeft() {
  servoMotor.write(180); // 90 degrees is the middle position, adjust as needed for your setup
}

void turnRight() {
  servoMotor.write(0); // 0 degrees is the rightmost position, adjust as needed for your setup
}
