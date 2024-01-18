#include <Servo.h>

Servo servoRed;   // Create a servo object for the red color
Servo servoBlue;  // Create a servo object for the blue color
//defining the color sensor pins
#define outPin 8
#define s0 9
#define s1 10
#define s2 11
#define s3 12

boolean DEBUG = true;

// Variables
int red, grn, blu;
String color = "";
long startTiming = 0;
long elapsedTime = 0;

void setup(){
  Serial.begin(9600);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT); // out from sensor becomes input to Arduino

  servoRed.attach(6);   // Attach the servo for the red color to pin 6
  servoBlue.attach(3);  // Attach the servo for the blue color to pin 3
  
  // Setting frequency scaling to 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  startTiming = millis();
}

void loop(){
  getColor();

  if (DEBUG) printData(); 
  elapsedTime = millis() - startTiming; 
  if (elapsedTime > 1000) {
    if (color == "RED") { //the color is detected as red we will call the moveservoblue function
      moveServoRed();
    } else if (color == "BLUE") {
      moveServoBlue();
    }
    startTiming = millis();
  }
}

// read RGB components 
void readRGB(){
  red = 0, grn = 0, blu = 0;
  
  int n = 10;
  for (int i = 0; i < n; ++i){
    //read red component
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = red + pulseIn(outPin, LOW);
  
    //read green component
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    grn = grn + pulseIn(outPin, LOW);
    
    //read blue component
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    blu = blu + pulseIn(outPin, LOW);
  }
  red = red / n;
  grn = grn / n;
  blu = blu / n;
}


//Showing captured data at Serial Monitor
void printData(void){
  Serial.print("red= ");
  Serial.print(red);
  Serial.print("   green= ");
  Serial.print(grn);
  Serial.print("   blue= ");
  Serial.print(blu);
  Serial.print(" - ");
  Serial.print(color);
  Serial.println(" detected!");
}
 //here we will determine which color is being detected base on the values we have prefined 
void getColor(){  
  readRGB();

  if (red > 70  && red < 90  && grn > 330 && grn < 450 && blu > 230 && blu < 320) color = "RED";
  else if (red > 290 && red < 380  && grn > 140 && grn < 190 && blu > 240 && blu < 290) color = "GREEN";
  else if (red > 220 && red < 430  && grn > 140 && grn < 270 && blu > 40  && blu < 95) color = "BLUE";
  else  color = "NO_COLOR";
  
  delay(500);
}
//servo for red color
void moveServoRed() {
  servoRed.write(180);  // Move the red servo to 180 degrees
  delay(2000);          // Wait for 2 seconds
  servoRed.write(0);    // Move the red servo back to 0 degrees
}
//servo for blue color
void moveServoBlue() {
  servoBlue.write(90);   // Move the blue servo to 90 degrees
  delay(2000);           // Wait for 2 seconds
  servoBlue.write(0);    // Move the blue servo back to 0 degrees
}
