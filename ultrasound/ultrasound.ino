// defines pins numbers
#include<Servo.h>
#include <NewPing.h>
Servo name_servo;
const int trigPin = 5;
const int echoPin = 6;

#define MAX_DISTANCE_POSSIBLE 1000 
// defines variables
NewPing sonar( trigPin, echoPin, MAX_DISTANCE_POSSIBLE);
long duration;
int distance;


int pos = 0; 
int maxDist = 0;
int maxAngle = 0;
int maxRight = 0;
int maxLeft = 0;
int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;
#define COLL_DIST 20
#define TURN_DIST COLL_DIST+10 
void setup() {
  name_servo.attach(2);
  name_servo.write(90);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);

   delay(2000);
  checkPath(); 
  motorSet = "FORWARD"; 
  name_servo.write(90);
  moveForward();
  
}

void loop() {
   checkForward();  
  checkPath();
  /*
  name_servo.write(90);
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if(distance > 35)
{
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11,80);
}
else
{
 name_servo.write(144); 
 int d1;
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
d1= duration*0.034/2;
name_servo.write(36);
int d2; 
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
d2= duration*0.034/2;
if(d1>d2){
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11,80);
}
else{
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(11,80);
}
delay(100);
}*/
}
void checkPath() {
  int curLeft = 0;
  int curFront = 0;
  int curRight = 0;
  int curDist = 0;
  name_servo.write(144);
  delay(120); 
  for(pos = 144; pos >= 36; pos-=18)
  {
    name_servo.write(pos);
    delay(90);
    checkForward(); 
    curDist = readPing();
    if (curDist < COLL_DIST) {
      checkCourse();
      break;
    }
    if (curDist < TURN_DIST) {
      changePath();
    }
    if (curDist > curDist) {maxAngle = pos;}
    if (pos > 90 && curDist > curLeft) { curLeft = curDist;}
    if (pos == 90 && curDist > curFront) {curFront = curDist;}
    if (pos < 90 && curDist > curRight) {curRight = curDist;}
  }
  maxLeft = curLeft;
  maxRight = curRight;
  maxFront = curFront;
}
void setCourse() {
    if (maxAngle < 90) {turnRight();}
    if (maxAngle > 90) {turnLeft();}
    maxLeft = 0;
    maxRight = 0;
    maxFront = 0;
}

void checkCourse() {
  moveBackward();
  delay(500);
  moveStop();
  setCourse();
}
void changePath() {
  if (pos < 90) {lookLeft();} 
  if (pos > 90) {lookRight();}
}
int readPing() {
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}
void checkForward() { if (motorSet=="FORWARD") {digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80); } }

  void checkBackward() { if (motorSet=="BACKWARD") {digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9,80); 
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11,80); } }

  void moveStop() {digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11,80);}

  void moveForward() {
    motorSet = "FORWARD";
    digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80);
  
}
void moveBackward() {
    motorSet = "BACKWARD";
   digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9,80); 
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11,80);
}  
void turnRight() {
  motorSet = "RIGHT";
 digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11,80);
  delay(400);
  motorSet = "FORWARD";
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80);    
}  
void turnLeft() {
  motorSet = "LEFT";
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80);
  delay(400);
  motorSet = "FORWARD";
 digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80);    
}  

void lookRight() {  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9,80); delay(400); digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80);    }
void lookLeft() {digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9,80); delay(400); digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9,80); 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11,80); }
