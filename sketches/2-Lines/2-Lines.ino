
int irLeft;
int irCenter;
int irRight;

const int Black = 1;


int pinSensorLeft = 9;
int pinSensorCenter = 10;
int pinSensorRight = 11;

int pinRightN = 2;
int pinRightP = 4;
int pinLeftN = 7;
int pinLeftP = 8;

void driveForward(int car_speed) {
  digitalWrite(pinRightN,LOW);
  digitalWrite(pinRightP,HIGH);
  digitalWrite(pinLeftN,LOW);
  digitalWrite(pinLeftP,HIGH);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void driveBackward(int car_speed) {
  digitalWrite(pinRightN,HIGH);
  digitalWrite(pinRightP,LOW);
  digitalWrite(pinLeftN,HIGH);
  digitalWrite(pinLeftP,LOW);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void driveLeft(int car_speed) {
  digitalWrite(pinRightN,LOW);
  digitalWrite(pinRightP,HIGH);
  digitalWrite(pinLeftN,HIGH);
  digitalWrite(pinLeftP,LOW);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void driveRight(int car_speed) {
  digitalWrite(pinRightN,HIGH);
  digitalWrite(pinRightP,LOW);
  digitalWrite(pinLeftN,LOW);
  digitalWrite(pinLeftP,HIGH);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void STOP() {
  digitalWrite(pinRightN,HIGH);
  digitalWrite(pinRightP,HIGH);
  digitalWrite(pinLeftN,HIGH);
  digitalWrite(pinLeftP,HIGH);
  analogWrite(5,0);
  analogWrite(6,0);
}

void setup(){

  pinMode(pinSensorLeft, INPUT);
  pinMode(pinSensorCenter, INPUT);
  pinMode(pinSensorRight, INPUT);
  pinMode(pinRightN, OUTPUT);
  pinMode(pinRightP, OUTPUT);
  pinMode(pinLeftN, OUTPUT);
  pinMode(pinLeftP, OUTPUT);

}

void loop(){
    
  irLeft = digitalRead(pinSensorLeft);
  irCenter = digitalRead(pinSensorCenter);
  irRight = digitalRead(pinSensorRight);

  if (irLeft != Black && (irCenter == Black && irRight != Black)) {
    // _ * _
    driveForward(130);
  } else if (irLeft == Black && (irCenter == Black && irRight != Black)) {
    // * * _
    driveLeft(180);
  } else if (irLeft == Black && (irCenter != Black && irRight != Black)) {
    // * _ _
    driveLeft(160);
  } else if (irLeft != Black && (irCenter != Black && irRight == Black)) {
    // _ _ *
    driveRight(160);
  } else if (irLeft != Black && (irCenter == Black && irRight == Black)) {
    // _ * *
    driveRight(180);
  } else if (irLeft == Black && (irCenter == Black && irRight == Black)) {
    STOP();
  }

  delay(100);

}
