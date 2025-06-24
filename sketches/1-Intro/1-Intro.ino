/*
Intro: hello car

Purpose:
Illustrate the basics of Arduino by driving the car in a sorta-circle.


*/

int turnTime = 500;
int straightTime = 1000;

int pinRightN = 2;
int pinRightP = 4;
int pinLeftN = 7;
int pinLeftP = 8;
int pinRightSpeed = 5;
int pinLeftSpeed = 6;



void setup() {
    pinMode(pinRightN, OUTPUT);
    pinMode(pinRightP, OUTPUT);
    pinMode(pinLeftN, OUTPUT);
    pinMode(pinLeftP, OUTPUT);

    pinMode(pinRightSpeed,OUTPUT);
    pinMode(pinLeftSpeed,OUTPUT);
    analogWrite(pinRightSpeed, 128);
    analogWrite(pinLeftSpeed, 128); 
}

void loop() {
    // drive forward 1 second
    digitalWrite(pinRightN, LOW);
    digitalWrite(pinRightP, HIGH);
    digitalWrite(pinLeftN, LOW);
    digitalWrite(pinLeftP, HIGH);
    delay(straightTime);

    //turn right for 1/2 second
    digitalWrite(pinRightN, HIGH);
    digitalWrite(pinRightP,LOW);
    digitalWrite(pinLeftN, LOW);
    digitalWrite(pinLeftP, HIGH);
    delay(turnTime);

    //Stop moving for a second
    digitalWrite(pinRightN, LOW);
    digitalWrite(pinRightP, LOW);
    digitalWrite(pinLeftN, LOW);
    digitalWrite(pinLeftP, LOW);
    delay(1000);

}
