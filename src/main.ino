#include <Arduino.h>
#include <AFMotor.h>  // Include Adafruit Motor Shield library

// Define pins for ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

// Define pins for LEDs
const int ledBelow10cm = 8;  // LED for distance <= 10 cm
const int ledAbove10cm = 9;   // LED for distance > 10 cm

// Create motor objects
AF_DCMotor motor1(1, MOTOR12_64KHZ); // Motor 1 on M1
AF_DCMotor motor2(2, MOTOR12_64KHZ); // Motor 2 on M2
AF_DCMotor motor3(3, MOTOR34_64KHZ); // Motor 3 on M3
AF_DCMotor motor4(4, MOTOR34_64KHZ); // Motor 4 on M4

int motorSpeed = 200; // Set motor speed (range: 0-255)

// Variables for distance measurement
long duration;
int distance;

// Function prototypes
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void stopCar();
void measureDistance();
void executeCommand(char command);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set up pins for ultrasonic sensor and LEDs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledBelow10cm, OUTPUT);
  pinMode(ledAbove10cm, OUTPUT);

  // Set initial motor speed
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);

  // Initial motor state (stopped)
  stopCar();

  // Welcome message
  Serial.println("Setup complete. Enter commands to control the car:");
  Serial.println("'f' - Forward, 'b' - Backward, 'l' - Left, 'r' - Right, 's' - Stop");
}

void loop() {
  // Check for serial input
  if (Serial.available() > 0) {
    char command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'f':
      moveForward();
      break;
    case 'b':
      moveBackward();
      break;
    case 'l':
      turnLeft();
      break;
    case 'r':
      turnRight();
      break;
    case 's':
      stopCar();
      break;
    default:
      Serial.println("Invalid command. Use 'f', 'b', 'l', 'r', or 's'.");
      break;
  }
}

// Function to move forward
void moveForward() {
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  Serial.println("Moving forward...");
}

// Function to move backward
void moveBackward() {
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  Serial.println("Moving backward...");
}

// Function to turn right
void turnRight() {
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);

  motor1.run(FORWARD);   // Right motors forward
  motor2.run(FORWARD);
  motor3.run(BACKWARD);  // Left motors backward
  motor4.run(BACKWARD);

  Serial.println("Turning right...");
}

// Function to turn left
void turnLeft() {
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);

  motor1.run(BACKWARD);  // Right motors backward
  motor2.run(BACKWARD);
  motor3.run(FORWARD);   // Left motors forward
  motor4.run(FORWARD);

  Serial.println("Turning left...");
}

// Function to stop the car
void stopCar() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  Serial.println("Car stopped.");
}

// Function to measure distance using the ultrasonic sensor
void measureDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  // Handle out-of-range readings
  if (distance == 0 || distance > 400) {
    Serial.println("Out of range");
    distance = 400; // Set to max distance
  } else {
    // Print distance to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Control LEDs based on distance
  if (distance <= 10) {
    digitalWrite(ledBelow10cm, HIGH);  // Turn on LED for distance <= 10 cm
    digitalWrite(ledAbove10cm, LOW);   // Turn off LED for distance > 10 cm
  } else {
    digitalWrite(ledBelow10cm, LOW);   // Turn off LED for distance <= 10 cm
    digitalWrite(ledAbove10cm, HIGH);  // Turn on LED for distance > 10 cm
  }
}
