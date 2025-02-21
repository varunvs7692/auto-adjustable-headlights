#include <Arduino.h>
#include <SoftwareSerial.h>  // Include SoftwareSerial for Bluetooth
#include <AFMotor.h>         // Include Adafruit Motor Shield library

// Define pins for ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

// Define pins for LEDs
const int ledBelow10cm = 8;  // One LED for below 10 cm
const int ledAbove10cm = 9;  // One LED for above 10 cm

// Define pins for HC-05 Bluetooth module
const int bluetoothTx = 0; // Tx of Arduino (not used for SoftwareSerial)
const int bluetoothRx = 1; // Rx of Arduino (not used for SoftwareSerial)

// Create a SoftwareSerial object for Bluetooth
SoftwareSerial BTSerial(10, 11);  // RX, TX pins for Bluetooth communication

// Create motor objects
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

char value;
int Speed = 200; // Set motor speed

void setup() {
  // Initialize serial communication
  Serial.begin(9600);   // Serial Monitor communication
  BTSerial.begin(9600); // Bluetooth communication

  // Set up pins for ultrasonic sensor and LEDs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledBelow10cm, OUTPUT);
  pinMode(ledAbove10cm, OUTPUT);

  // Set motor speed
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

  // Debugging message
  Serial.println("Setup complete. Waiting for Bluetooth commands...");
}

void loop() {
  // Wait for Bluetooth control input
  Bluetoothcontrol();
}

void Bluetoothcontrol() {
  if (BTSerial.available() > 0) {
    value = BTSerial.read();  // Read Bluetooth input
    Serial.println(value);    // Debugging: print received value

    // Control movement based on input
    if (value == 'F') {       // Forward
      forward();
    } else if (value == 'B') {  // Backward
      backward();
    } else if (value == 'L') {  // Turn left
      left();
    } else if (value == 'R') {  // Turn right
      right();
    } else if (value == 'S') {  // Stop
      Stop();
    } else if (value == 'U') {  // Measure distance with ultrasonic sensor
      measureDistance();
    }
  }
}

// Functions for motor control
void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
  Serial.println("Moving Forward...");
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
  Serial.println("Moving Backward...");
}

void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
  Serial.println("Turning Right...");
}

void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
  Serial.println("Turning Left...");
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
  Serial.println("Car Stopped.");
}

void measureDistance() {
  long duration;
  int distance;

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Check if the duration is valid
  if (duration == 0) {
    Serial.println("Error: No echo received");
    return;
  }

  // Calculate distance (in cm)
  distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send distance data via Bluetooth
  BTSerial.print("Distance: ");
  BTSerial.print(distance);
  BTSerial.println(" cm");

  // Control LEDs based on distance
  if (distance <= 10) {
    digitalWrite(ledBelow10cm, HIGH);  // Turn on LED for distance <= 10 cm
    digitalWrite(ledAbove10cm, LOW);   // Turn off LED for distance > 10 cm
  } else {
    digitalWrite(ledBelow10cm, LOW);   // Turn off LED for distance <= 10 cm
    digitalWrite(ledAbove10cm, HIGH);  // Turn on LED for distance > 10 cm
  }
}
