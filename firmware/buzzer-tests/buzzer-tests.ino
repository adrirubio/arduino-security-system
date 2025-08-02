// c++
const byte buzzerPin = 2;
const byte buttonPin = 3;
int buttonPressCount = 0;
bool lastButtonState = HIGH;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    delay(50);

    switch (buttonPressCount % 3) {
    case 0:
      Serial.println("Playing startup beeps");
      startupBeep1();
      delay(500);
      startupBeep2();
      break;

    case 1:
      Serial.println("Playing intruder beeps");
      intruderAlert1();
      delay(500);
      intruderAlert2();
      break;

    case 2:
      Serial.println("Playing shutdown beeps");
      shutdownBeep1();
      delay(500);
      shutdownBeep2();
      break;
    }

    buttonPressCount++;
  }

  lastButtonState = currentButtonState;
}

// startup beep 1 (original)
void startupBeep1() {
  tone(buzzerPin, 1000, 200);
  delay(250);
  noTone(buzzerPin);
}

// startup beep 2 (ascending tones)
void startupBeep2() {
  tone(buzzerPin, 800, 150);
  delay(150);
  tone(buzzerPin, 1200, 150);
  delay(150);
  tone(buzzerPin, 1600, 150);
  delay(150);
  noTone(buzzerPin);
}

// intruder alert 1 (original)
void intruderAlert1() {
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    tone(buzzerPin, 2000);
    delay(150);
    noTone(buzzerPin);
    delay(50);
  }
}

// intruder alert 2 (alternating frequencies)
void intruderAlert2() {
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    tone(buzzerPin, 1500);
    delay(200);
    tone(buzzerPin, 2500);
    delay(200);
  }
  noTone(buzzerPin);
}

// shutdown beep 1 (original)
void shutdownBeep1() {
  tone(buzzerPin, 400, 300);
  delay(300);
  noTone(buzzerPin);
}

// shutdown beep 2 (descending tones)
void shutdownBeep2() {
  tone(buzzerPin, 1200, 150);
  delay(150);
  tone(buzzerPin, 800, 150);
  delay(150);
  tone(buzzerPin, 400, 200);
  delay(200);
  noTone(buzzerPin);
}
