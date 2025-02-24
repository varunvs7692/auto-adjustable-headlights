#include <NewPing.h>  // Include the NewPing library for ultrasonic sensor

// Define pins for ultrasonic sensor
const int trigPin = 12;
const int echoPin = 13;

// Set maximum distance for ultrasonic sensor (in cm)
#define MAX_DISTANCE 200
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// Define pin for LED (indicating nearby vehicle detection)
const int ledPin = 8;  

void setup() {
  Serial.begin(9600);   // Start the serial communication
  pinMode(ledPin, OUTPUT);  // Set the LED pin as output
}

void loop() {
  // Get the distance from the ultrasonic sensor
  long distance = sonar.ping_cm();  // Get the distance in cm
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If a vehicle is detected within 10 cm range, turn on LED (representing V2V detection)
  if (distance > 0 && distance <= 10) {
    digitalWrite(ledPin, HIGH);  // Turn on LED to indicate nearby vehicle
    Serial.println("Vehicle Detected!");
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED when no vehicle is detected
  }

  delay(500);  // Delay to avoid rapid pinging
}

