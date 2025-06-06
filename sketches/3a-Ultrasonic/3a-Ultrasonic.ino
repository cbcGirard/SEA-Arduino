// Pin definitions for the ultrasonic sensor
int pinTrigger = A1;
int pinEcho = A0;

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
  Serial.begin(9600);

  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop()
{
  // Check for obstacles in front
  float distance = checkDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Delay for a second so *we* can read the output
    delay(1000);

}
