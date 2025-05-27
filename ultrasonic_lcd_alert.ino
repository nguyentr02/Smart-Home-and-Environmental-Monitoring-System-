#include <LiquidCrystal.h>

// LCD pin mapping: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define TRIG_PIN 8
#define ECHO_PIN 9

String command = "";

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(16, 2);
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  // Send distance to Pi
  Serial.println(distance);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  // Check for command from Pi
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    if (command == "ALERT") {
      lcd.setCursor(0, 1);
      lcd.print("⚠ ALERT ZONE! ");
    } else {
      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear line
    }
  }

  delay(1000);
}
