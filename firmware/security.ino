// c++
const byte buzzerPin = 3;
const int photoPin = A0;
const int buttonPin = 2;

// 0 = disarmed, 1 = armed, 2 = alert
int systemState = 0;
unsigned long buttonPressTime = 0;
bool buttonWasPressed = false;

void setup() {
  // buzzer
  pinMode(buzzerPin, OUTPUT);

  // photoresistor
  pinMode(photoPin, INPUT);

  // leds
  pinMode(4, OUTPUT); // green
  pinMode(5, OUTPUT); // red
  pinMode(6, OUTPUT); // yellow

  // pushbutton
  pinMode(2, INPUT_PULLUP);

  Serial.begin(9600); // start serial communication
}

void loop() {
  if (systemState == 0) {
    // check for button press
    if (digitalRead(buttonPin) == LOW) {
      delay(50); // debounce
      if (digitalRead(buttonPin) == LOW) {
        digitalWrite(4, HIGH);
        startupBeep();
        // wait for startup to finish
        delay(5000);
        systemState = 1;
      }
    }
  }

  else if (systemState == 1) {
    int lightVal = analogRead(photoPin);
    Serial.println(lightVal);

    if (lightVal < 300) {
      // turn red led on
      digitalWrite(4, LOW); // green off
      digitalWrite(5, HIGH); // red on

      systemState = 2;
    }

    // shutdown or reset
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW && !buttonWasPressed) {
      // button just pressed
      buttonPressTime = millis();
      buttonWasPressed = true;
    }

    // button release
    if (buttonState == HIGH && buttonWasPressed) {
      unsigned long pressDuration = millis() - buttonPressTime;
      buttonWasPressed = false;

      if (pressDuration >= 2000) {
        Serial.println("Shutting down...");

        // flash yellow light
        digitalWrite(4, LOW);
        digitalWrite(6, HIGH);
        delay(1000);
        digitalWrite(6, LOW);

        systemState = 0;
      } else {
        Serial.print("Three second shutdown...");

        // yellow light
        digitalWrite(4, LOW);
        digitalWrite(6, HIGH);
        delay(3000);
        digitalWrite(6, LOW);

        systemState = 1;
      }
    }
  }

  else if (systemState == 2) {
    // alert state, keep buzzing until beam restored
    int lightVal = analogRead(photoPin);
    Serial.println(lightVal);

    if (lightVal < 300) {
      intruderAlert();
    } else {
      // beam restored
      digitalWrite(5, LOW); // red off
      digitalWrite(4, HIGH); // green on
      systemState = 1;
    }
  }

  delay(200);
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

