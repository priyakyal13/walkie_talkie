//esp code
#define bpin 21
#define spin 25
#define mpin 32

void setup() {
  Serial.begin(115200);  // Debugging on Serial Monitor
  Serial1.begin(115200, SERIAL_8N1, 4, 5); // Communication with HC-05 module on UART1
  pinMode(spin, OUTPUT);
  pinMode(bpin, INPUT_PULLUP);
  Serial.println("ESP initialized");
}

void loop() {
  int buttonState = digitalRead(bpin);

  if (buttonState == LOW) {
    // Transmit audio
    int micValue = analogRead(mpin) >> 4; // Scale 12-bit to 8-bit
    micValue+=60;
    Serial1.write(micValue);             // Send raw byte
    Serial.println("Sent: ");
    Serial.print("0,255,");
    Serial.println(micValue);
    //delayMicroseconds(125);              // ~8 kHz sampling rate
  } else {
    // Play received audio
    if (Serial1.available()) {
      int receivedValue = Serial1.read(); // Read raw byte from HC-05
      Serial.println("Received: ");
      Serial.print("0,255,");
      Serial.println(receivedValue);
      if (receivedValue<225){receivedValue=0;}
      dacWrite(spin, receivedValue);      // Output to speaker
    }
  }
}
