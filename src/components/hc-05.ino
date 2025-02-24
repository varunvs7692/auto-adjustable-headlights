char command;

void setup() {
  Serial.begin(9600);  // Set the baud rate to your Bluetooth module
}

void loop() {
  if (Serial.available() > 0) { 
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
}

// Motor control functions (placeholders, the actual motor functions should be implemented separately)
void forward() {
  // Logic to move the car forward
}

void back() {
  // Logic to move the car backward
}

void left() {
  // Logic to turn the car left
}

void right() {
  // Logic to turn the car right
}

void Stop() {
  // Logic to stop the car
}

