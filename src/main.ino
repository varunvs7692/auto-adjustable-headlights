#include <AFMotor.h>
#include <NewPing.h>  // Include the NewPing library for ultrasonic sensor

// Initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

char command;

// Define pins for ultrasonic sensor
const int trigPin = 12;
const int echoPin = 13;

// Define pins for LEDs to indicate distance
const int ledBelow10cm = 8;  // LED for distance <= 10 cm
const int ledAbove10cm = 9;  // LED for distance > 10 cm

// Set maximum distance for ultrasonic sensor
#define MAX_DISTANCE 200
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);  // Set the baud rate to your Bluetooth module
  
  pinMode(ledBelow10cm, OUTPUT); // Set LED pins as output
  pinMode(ledAbove10cm, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); // Initialize with motors stopped

    // Handle Bluetooth commands to control the car
    switch(command){
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
    }
  }

  // Get the distance from the ultrasonic sensor
  long distance = sonar.ping_cm();  // Get the distance in cm
  
  // Check if the distance is valid
  if (distance > 0) {
    if (distance <= 10) {
      digitalWrite(ledBelow10cm, HIGH);  // Turn on LED for distance <= 10 cm
      digitalWrite(ledAbove10cm, LOW);   // Turn off LED for distance > 10 cm
    } else {
      digitalWrite(ledBelow10cm, LOW);   // Turn off LED for distance <= 10 cm
      digitalWrite(ledAbove10cm, HIGH);  // Turn on LED for distance > 10 cm
    }
  } else {
    // If distance is not available (e.g., sensor failure), turn off LEDs
    digitalWrite(ledBelow10cm, LOW);
    digitalWrite(ledAbove10cm, LOW);
  }
}

// Motor control functions
void forward() {
  motor1.setSpeed(255);  // Maximum velocity
  motor1.run(FORWARD);   // Rotate motor clockwise
  motor2.setSpeed(255);  // Maximum velocity
  motor2.run(FORWARD);   // Rotate motor clockwise
  motor3.setSpeed(255);  // Maximum velocity
  motor3.run(FORWARD);   // Rotate motor clockwise
  motor4.setSpeed(255);  // Maximum velocity
  motor4.run(FORWARD);   // Rotate motor clockwise
}

void back() {
  motor1.setSpeed(255);  // Maximum velocity
  motor1.run(BACKWARD);  // Rotate motor anti-clockwise
  motor2.setSpeed(255);  // Maximum velocity
  motor2.run(BACKWARD);  // Rotate motor anti-clockwise
  motor3.setSpeed(255);  // Maximum velocity
  motor3.run(BACKWARD);  // Rotate motor anti-clockwise
  motor4.setSpeed(255);  // Maximum velocity
  motor4.run(BACKWARD);  // Rotate motor anti-clockwise
}

void left() {
  motor1.setSpeed(255);  // Maximum velocity
  motor1.run(BACKWARD);  // Rotate motor anti-clockwise
  motor2.setSpeed(255);  // Maximum velocity
  motor2.run(BACKWARD);  // Rotate motor anti-clockwise
  motor3.setSpeed(255);  // Maximum velocity
  motor3.run(FORWARD);   // Rotate motor clockwise
  motor4.setSpeed(255);  // Maximum velocity
  motor4.run(FORWARD);   // Rotate motor clockwise
}

void right() {
  motor1.setSpeed(255);  // Maximum velocity
  motor1.run(FORWARD);   // Rotate motor clockwise
  motor2.setSpeed(255);  // Maximum velocity
  motor2.run(FORWARD);   // Rotate motor clockwise
  motor3.setSpeed(255);  // Maximum velocity
  motor3.run(BACKWARD);  // Rotate motor anti-clockwise
  motor4.setSpeed(255);  // Maximum velocity
  motor4.run(BACKWARD);  // Rotate motor anti-clockwise
}

void Stop() {
  motor1.setSpeed(0);    // Minimum velocity
  motor1.run(RELEASE);   // Stop motor
  motor2.setSpeed(0);    // Minimum velocity
  motor2.run(RELEASE);   // Stop motor
  motor3.setSpeed(0);    // Minimum velocity
  motor3.run(RELEASE);   // Stop motor
  motor4.setSpeed(0);    // Minimum velocity
  motor4.run(RELEASE);   // Stop motor
}

