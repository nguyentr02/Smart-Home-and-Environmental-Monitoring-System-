const int pirPin = 2;
const int buzzerPin = 3;
unsigned long lastMotionTime = 0;
unsigned long inactivityThreshold = 60000; // Default 1 minute

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    Serial.println("Motion");
    lastMotionTime = millis();
    digitalWrite(buzzerPin, LOW);
  } else {
    unsigned long now = millis();
    if (now - lastMotionTime > inactivityThreshold) {
      Serial.println("Inactivity");
      digitalWrite(buzzerPin, HIGH);
    } else {
      Serial.println("No Motion");
      digitalWrite(buzzerPin, LOW);
    }
  }

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("THRESHOLD:")) {
      String valueStr = input.substring(10);
      inactivityThreshold = valueStr.toInt();
      Serial.print("New threshold: ");
      Serial.println(inactivityThreshold);

      // ✅ Print the updated threshold to Serial Monitor
      Serial.print("🛠 Threshold updated to: ");
      Serial.print(inactivityThreshold);
      Serial.println(" ms");
    }
  }

  delay(500);
}
