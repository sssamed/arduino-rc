#include <Servo.h>

Servo servo;
const int servoPin = 3;

const int in1 = 5;
const int in2 = 6;

int speed = 200; // 0 - 255
int response;

const int trigPin = 12;
const int echoPin = 13;

int distance;

void setup() 
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(servoPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo.attach(servoPin);
  servo.write(90);

  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    stop();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2)

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    distance = pulseIn(echoPin, HIGH) * 0.017;

    response = Serial.read();

    switch (response)
    {
      case 'F':
        forward();
      break;
      
      case 'B':
        back();
      break;

      case 'L':
        left();
      break;
      
      case 'R':
        right();
      break;

      case 'G':
        left();
        forward();
      break;

      case 'I':
        right();
        forward();
      break;

      case 'H':
        back();
        left();
      break;

      case 'J':
        back();
        right();
      break;
    }
  }
}

void stop()
{
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  servo.write(90);
}

void forward()
{
  if (distance > 0 && distance < 4) analogWrite(in1, speed);
}

void back()
{
  analogWrite(in2, speed);
}

void right()
{
  servo.write(115);
}

void left()
{
  servo.write(65);
}
