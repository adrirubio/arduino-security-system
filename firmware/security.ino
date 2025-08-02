// c++
const byte piezoPin = 3;
const int photoPin = A0;

void setup() {
  // buzzer
  pinMode(piezoPin, OUTPUT);

  // photoresistor
  pinMode(photoPin, INPUT);

  // leds
  pinMode(4, OUTPUT); // green
  pinMode(5, OUTPUT); // red
  pinMode(6, OUTPUT); // yellow

  // pushbutton
  pinMode(2, INPUT_PULLUP);

  Serial.begin(9600); // start serial communication
  startupBeep(); // Play startup sound
}

void loop() {
  int lightVal = analogRead(photoPin);
  Serial.println(lightVal);

  if (lightVal < 300) {
    intruderAlert(); // Avoid repeated alarms
    delay(3000);
  }
}

// startup beep
void startupBeep() {
  tone(buzzerPin, 800, 150);
  delay(150);
  tone(buzzerPin, 1200, 150);
  delay(150);
  tone(buzzerPin, 1600, 150);
  delay(150);
  noTone(buzzerPin);
}

// intruder alert sound
void intruderAlert() {
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    tone(buzzerPin, 3500);
    delay(200);
    tone(buzzerPin, 4500);
    delay(200);
  }
  noTone(buzzerPin);
}

// shutdown sound
void shutdownBeep() {
  tone(buzzerPin, 1200, 150);
  delay(150);
  tone(buzzerPin, 800, 150);
  delay(150);
  tone(buzzerPin, 400, 200);
  delay(200);
  noTone(buzzerPin);
}

