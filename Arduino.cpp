void setup() {
  // Start communication with the computer for debugging
  Serial.begin(115200);

  Serial1.begin(115200);

  // Initialize UART1 for the first HC-05
  Serial3.begin(115200); // Connect to HC-05 #1 (e.g., transmitting to a paired device)

  // Initialize UART2 for the second HC-05
  Serial2.begin(115200); // Connect to HC-05 #2 (e.g., receiving from another HC-05)

  Serial.println("Dual HC-05 Communication Ready");
}

void loop() {
  if (Serial1.available()) {
    while (Serial1.available()) { // Read all available data
      char receivedByte = Serial1.read(); // Read byte-by-byte
      Serial2.write(receivedByte);
      Serial3.write(receivedByte);        // Forward directly to HC-05 #1
      Serial.write(receivedByte);         // Debug output to Serial Monitor
    }
    Serial.println(); // Add a newline for better readability in the Serial Monitor
  }

  // Check if data is received from HC-05 #2
  if (Serial2.available()) {
    while (Serial2.available()) { // Read all available data
      char receivedByte = Serial2.read(); // Read byte-by-byte
      Serial1.write(receivedByte);
      Serial3.write(receivedByte);        // Forward directly to HC-05 #1
      Serial.write(receivedByte);         // Debug output to Serial Monitor
    }
    Serial.println(); // Add a newline for better readability in the Serial Monitor
  }

  // Check if data is received from HC-05 #1
  if (Serial3.available()) {
    while (Serial3.available()) { // Read all available data
      char receivedByte = Serial3.read(); // Read byte-by-byte
      Serial1.write(receivedByte);
      Serial2.write(receivedByte);        // Forward directly to HC-05 #2
      Serial.write(receivedByte);         // Debug output to Serial Monitor
    }
    Serial.println(); // Add a newline for better readability in the Serial Monitor
  }
}
