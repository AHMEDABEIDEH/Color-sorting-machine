#include <Servo.h>

#define triggerPin 3
#define echoPin 2

long duration, distance;
long angle1, angle2;
Servo servoMotorRED;
Servo servoMotorBLUE;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoMotorRED.attach(5); // Pin 5 for servo motor RED
  servoMotorBLUE.attach(6); // Pin 6 for servo motor BLUE

  Serial.begin(9600);

  // Set the initial servo motor values to 0
  angle1 = 0.0;
  angle2 = 0.0;
  servoMotorRED.write(angle1); //print the angle to the serial monitor
  servoMotorBLUE.write(angle2);//print the angle to the serial monitor
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance in CM
  distance = ((duration / 29) / 2);
  delay(50);
//if we have distance as less than 100 we have no color and we keep the servo at 0
  if (distance < 100) {
    Serial.println("COLOR: NO COLOR DETECTED");//print the to the serial monitor
    Serial.println("ANGLE 1: 0");
    Serial.println("ANGLE 2: 0");
    angle1 = 0.0;
    angle2 = 0.0;
    servoMotorRED.write(angle1);
    servoMotorBLUE.write(angle2);
    //if we have distance as less than 100 we have red color and we keep the servo at 90 and the other servo at 0
  } else if (distance >= 100 && distance < 200) {
    Serial.println("COLOR: RED DETECTED"); //print red to the serial monitor
    Serial.println("ANGLE 1: 90");
    Serial.println("ANGLE 2: 0");
    angle1 = 90.0;
    angle2 = 0.0;
    servoMotorRED.write(angle1);
    servoMotorBLUE.write(angle2);
    //if we have distance as less than 100 we have blue color and we keep the servo at 0 and the other servo at 180
  } else if (distance >= 200 && distance < 300) {
    Serial.println("COLOR: BLUE DETECTED");//print blue to the serial monitor
    Serial.println("ANGLE 1: 0");
    Serial.println("ANGLE 2: 180");
    angle1 = 0.0;
    angle2 = 180.0;
    servoMotorRED.write(angle1);
    servoMotorBLUE.write(angle2);
  }
  //if we have distance as less than 100 we have unknown color and we keep the both servo motors at 0
 else if  (distance >= 300 && distance < 1000) {
    Serial.println("UNKNOWN COLOR"); //print unknown to the serial monitor
    Serial.println("ANGLE 1: 0");
    Serial.println("ANGLE 2: 0");
    angle1 = 0.0;
    angle2 = 0.0;
    servoMotorRED.write(angle1);
    servoMotorBLUE.write(angle2);
  }

  delay(1000); // Wait one second and do the same operations
}
