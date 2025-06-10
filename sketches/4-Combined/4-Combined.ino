
#include <Servo.h>

Servo servo_A2;

int pinTrigger = A1;
int pinEcho = A0;

int pinSensorLeft = 9;
int pinSensorCenter = 10;
int pinSensorRight = 11;

int pinRightN = 2;
int pinRightP = 4;
int pinLeftN = 7;
int pinLeftP = 8;
int pinRightSpeed = 5;
int pinLeftSpeed = 6;

int Black=1;

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
    pinMode(pinSensorLeft, INPUT);
    pinMode(pinSensorCenter, INPUT);
    pinMode(pinSensorRight, INPUT);
    pinMode(pinRightN, OUTPUT);
    pinMode(pinRightP, OUTPUT);
    pinMode(pinLeftN, OUTPUT);
    pinMode(pinLeftP, OUTPUT);
    pinMode(pinRightSpeed, OUTPUT);
    pinMode(pinLeftSpeed, OUTPUT);

    pinMode(pinTrigger, OUTPUT);
    pinMode(pinEcho, INPUT);

    servo_A2.attach(A2);
    servo_A2.write(90); // Set servo to initial position
}

void loop()
{
    // Read the line sensors
    int Left_Tra_Value = digitalRead(9);
    int Center_Tra_Value = digitalRead(10);
    int Right_Tra_Value = digitalRead(11);

    if (Left_Tra_Value != Black && (Center_Tra_Value  && Right_Tra_Value != Black))
    {
        driveForward(100);
    }
    else if (Left_Tra_Value  && (Center_Tra_Value  && Right_Tra_Value != Black))
    {
        driveLeft(180);
    }
    else if (Left_Tra_Value  && (Center_Tra_Value != Black && Right_Tra_Value != Black))
    {
        driveLeft(160);
    }
    else if (Left_Tra_Value != Black && (Center_Tra_Value != Black && Right_Tra_Value ))
    {
        driveRight(160);
    }
    else if (Left_Tra_Value != Black && (Center_Tra_Value  && Right_Tra_Value ))
    {
        driveRight(180);
    }
    else if (Left_Tra_Value && (Center_Tra_Value && Right_Tra_Value))
    {
        driveForward(75);
    }
    else
    {
        // No line detected, check for obstacles
        servo_A2.write(90);
        float Front_Distance = checkDistance();

        if (0 < Front_Distance && Front_Distance <= 20)
        {
            STOP();
            delay(100);
            // Look left and measure nearest distance...
            servo_A2.write(180);
            delay(500);
            float Left_Distance = checkDistance();
            delay(100);
            // Look right and measure nearest distance...
            servo_A2.write(0);
            delay(500);
            float Right_Distance = checkDistance();
            delay(100);
            // Compare distances and decide which way to turn
            if (Right_Distance <= Left_Distance)
            {
                driveLeft(255);
                servo_A2.write(90);
                delay(300);
            }
            else
            {
                driveRight(255);
                servo_A2.write(90);
                delay(300);
            }
        }
        else
        {
            // No obstacles detected, move forward
            driveForward(150);
        }
    }
}
