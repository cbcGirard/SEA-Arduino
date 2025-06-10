
#include <Servo.h>

Servo servo_A2;

int pinTrigger = A1;
int pinEcho = A0;

float Left_Distance = 0;
float Right_Distance = 0;
float Front_Distance = 0;

// Pin definitions for motor control
int pinRightN = 2;
int pinRightP = 4;
int pinLeftN = 7;
int pinLeftP = 8;
int pinRightSpeed = 5;
int pinLeftSpeed = 6;


void driveForward(int car_speed)
{
  digitalWrite(pinRightN, LOW);
  digitalWrite(pinRightP, HIGH);
  digitalWrite(pinLeftN, LOW);
  digitalWrite(pinLeftP, HIGH);
  analogWrite(pinRightSpeed, car_speed);
  analogWrite(pinLeftSpeed, car_speed);
}

void driveBackward(int car_speed)
{
  digitalWrite(pinRightN, HIGH);
  digitalWrite(pinRightP, LOW);
  digitalWrite(pinLeftN, HIGH);
  digitalWrite(pinLeftP, LOW);
  analogWrite(pinRightSpeed, car_speed);
  analogWrite(pinLeftSpeed, car_speed);
}

void driveLeft(int car_speed)
{
  digitalWrite(pinRightN, LOW);
  digitalWrite(pinRightP, HIGH);
  digitalWrite(pinLeftN, HIGH);
  digitalWrite(pinLeftP, LOW);
  analogWrite(pinRightSpeed, car_speed);
  analogWrite(pinLeftSpeed, car_speed);
}

void driveRight(int car_speed)
{
  digitalWrite(pinRightN, HIGH);
  digitalWrite(pinRightP, LOW);
  digitalWrite(pinLeftN, LOW);
  digitalWrite(pinLeftP, HIGH);
  analogWrite(pinRightSpeed, car_speed);
  analogWrite(pinLeftSpeed, car_speed);
}

void STOP()
{
  digitalWrite(pinRightN, HIGH);
  digitalWrite(pinRightP, HIGH);
  digitalWrite(pinLeftN, HIGH);
  digitalWrite(pinLeftP, HIGH);
  analogWrite(pinRightSpeed, 0);
  analogWrite(pinLeftSpeed, 0);
}

float checkDistance()
{
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  float distance = pulseIn(pinEcho, HIGH) / 58.00;
  delay(10);
  return distance;
}

void setup()
{
  pinMode(pinRightN, OUTPUT);
  pinMode(pinRightP, OUTPUT);
  pinMode(pinLeftN, OUTPUT);
  pinMode(pinLeftP, OUTPUT);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  servo_A2.attach(A2);
}

void loop()
{
  // Check for obstacles in front
  servo_A2.write(90);
  float Front_Distance = checkDistance();

  if (0 < Front_Distance && Front_Distance <= 20)
  {
    // Obstacle detected in front, stop the car
    STOP();
    delay(100);

    // Look left and measure nearest distance...
    servo_A2.write(180);
    delay(500);
    Left_Distance = checkDistance();
    delay(100);

    // Look right and measure nearest distance...
    servo_A2.write(0);
    delay(500);
    Right_Distance = checkDistance();
    delay(100);

    // Compare distances and turn accordingly
    if (Right_Distance <= Left_Distance)
    {
      driveLeft(130);
      delay(600);
    }
    else
    {
      driveRight(130);
      delay(600);
    }
  }
  else
  {
    driveForward(150);
  }
}
