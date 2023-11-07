#include <Servo.h>

#define raspred 6
#define raspgreen 7

#define in1 4
#define in2 2
#define en 3

#define run_pin 13

#define s0_pin 12
#define s1_pin 11
#define s2_pin 10
#define s3_pin 8
#define out_pin 9

#define servoPin 5
#define irfront A4
#define irleft A5
#define irright A3

Servo steering;

bool start = true;
int lastvalue = 5;
int speed = 120;
int mid = 75;
int left = 40;
int right = 112;
int turns = 0;
int finish_timer = 0;
int clockwise = 0;

uint16_t distance_middle = 0;
uint16_t distance_left = 0;
uint16_t distance_right = 0;

void forward(uint8_t _speed, uint16_t _delay);
void Stop();

void setup() {
  Serial.begin(9600);
  steering.attach(servoPin);
  steering.write(80);

  pinMode(run_pin, INPUT_PULLUP);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(raspred, INPUT_PULLUP);
  pinMode(raspgreen, INPUT_PULLUP);

  
  pinMode(s0_pin, OUTPUT);
  pinMode(s1_pin, OUTPUT);
  pinMode(s2_pin, OUTPUT);
  pinMode(s3_pin, OUTPUT);
  pinMode(out_pin, INPUT);
  digitalWrite(s0_pin,HIGH);
  digitalWrite(s1_pin,LOW);
  
  //left 40
  //right 120

  delay(1000);
}

void loop() {
// int test(){

  if(start){
    start = false;
    while(digitalRead(run_pin) == HIGH){
      Serial.print("waiting\n");
    }
  }

  if(turns >= 12){
    finish_timer++;
    if(finish_timer == 30){
      Stop();
      while(true){

      }
    }
  }

  Serial.print("  M: ");
  Serial.print(distance_middle);
  Serial.print("  L: ");
  Serial.print(distance_left);
  Serial.print("  R: ");
  Serial.print(distance_right);
  Serial.println();

  if (digitalRead(raspred) == 1) {
    Serial.print("Red");
    //move right
    steering.write(right);
    forward(speed, 500);
    steering.write(left);
    forward(speed, 500);
  }

  if (digitalRead(raspgreen) == 1) {
    Serial.print("Green");
    //move left
    steering.write(left);
    forward(speed, 500);
    steering.write(right);
    forward(speed, 500);
  }

  

  //clockwise
  if(clockwise >= 0 && direction() == 1){
    if(clockwise == 0) {
      clockwise = 1;
    }
  }

  //counter clockwise
  if(clockwise <= 0 && direction() == 2){
    if(clockwise == 0) {
      clockwise = -1;
    }
  }

  if (digitalRead(irfront) == 0) {
    delay(10);
    if (digitalRead(irfront) == 0) {
        steering.write(mid);
        backward(speed, 700);
        if(digitalRead(raspgreen) == 1){
          steering.write(left);
          forward(speed, 500);
          steering.write(right);
          forward(speed, 200);
        }
        else if(digitalRead(raspred) == 1){
          steering.write(right);
          forward(speed, 500);
          steering.write(left);
          forward(speed, 200);
        }
        else{
          turns++;
          if(clockwise == -1){
            steering.write(left);
            forward(speed, 700);
            steering.write(right);
            backward(speed, 1300);
          }
          else{
            steering.write(right);
            forward(speed, 700);
            steering.write(left);
            backward(speed, 1300);
          }
          steering.write(mid);
          backward(speed, 500);
        }
        steering.write(mid);
    }
    if (digitalRead(irfront) == 0 and digitalRead(irright) == 0) {
      //move left
      steering.write(mid);
      backward(speed, 500);
      steering.write(left);
      forward(speed, 500);
    }
    if (digitalRead(irfront) == 0 and digitalRead(irleft) == 0) {
      //move right
      steering.write(mid);
      backward(speed, 500);
      steering.write(right);
      forward(speed, 500);
    }
  }

  else if (digitalRead(irleft) == 0) {
    delay(10);
    if (digitalRead(irleft) == 0) {
      steering.write(right);
      forward(speed, 100);
      
      lastvalue = 3;
    }
  } else if (digitalRead(irright) == 0) {
    delay(10);
    if (digitalRead(irright) == 0) {
      steering.write(left);
      forward(speed, 100);
      
      lastvalue = 7;
    }
  } else {
    steering.write(mid);
    forward(speed, 30);
  }
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


////////////////////////

// void loop(){
int direction() {

  digitalWrite(s2_pin,LOW);
  digitalWrite(s3_pin,LOW);
  int red = pulseIn(out_pin, LOW);
 red = map(red, 25,72,255,0);

  Serial.print(red);
  Serial.print(" ");


  digitalWrite(s2_pin,HIGH);
  digitalWrite(s3_pin,HIGH);
  int green = pulseIn(out_pin, LOW);
 green = map(green, 30,90,255,0);

  Serial.print(green);
  Serial.print(" ");


  digitalWrite(s2_pin,LOW);
  digitalWrite(s3_pin,HIGH);
  int blue  = pulseIn(out_pin, LOW);
 blue = map(blue, 25,70,255,0);

  Serial.print(blue);
  Serial.print(" ");


  Serial.println("");

  int ave = (red + green + blue) / 3;
  if(ave > 100){
    return 0;
  }
  if(red > blue && red > green){
    return 1;
  }
  if(blue > red && blue > green){
    return 2;
  }
}
