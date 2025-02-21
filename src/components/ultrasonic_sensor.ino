#include <Arduino.h>

// Define pins for ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

// Define pins for LEDs
const int ledBelow10cm = 8;  // LED for distance <= 10 cm
const int ledAbove10cm = 9;   // LED for distance > 10 cm

// Variables for distance measurement
long duration;
int distance;

// Function prototypes
void measureDistance();

void setupUltrasonicSensor() {
  // Set up pins for ultrasonic sensor and LEDs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledBelow10cm, OUTPUT);
  pinMode(ledAbove10cm, OUTPUT);
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

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control LEDs based on distance
  if (distance <= 10) {
    digitalWrite(ledBelow10cm, HIGH);  // Turn on LED for distance <= 10 cm
    digitalWrite(ledAbove10cm, LOW);   // Turn off LED for distance > 10 cm
  } else {
    digitalWrite(ledBelow10cm, LOW);   // Turn off LED for distance <= 10 cm
    digitalWrite(ledAbove10cm, HIGH);  // Turn on LED for distance > 10 cm
  }
}
