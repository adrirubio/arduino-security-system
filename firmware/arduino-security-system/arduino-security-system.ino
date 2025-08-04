// c++
const byte buzzerPin = 3;
const int laserPin = 7;
const int buttonPin = 2;

// 0 = disarmed, 1 = armed, 2 = alert
int systemState = 0;
unsigned long buttonPressTime = 0;
bool buttonWasPressed = false;

// Alert timing variables
unsigned long alertStartTime = 0;
unsigned long lastToneChange = 0;
int currentTone = 0;
const unsigned long alertDuration = 5000; // 5 seconds alarm duration

void setup() {
  // buzzer
  pinMode(buzzerPin, OUTPUT);

  // laser receiver
  pinMode(laserPin, INPUT_PULLUP);

  // leds
  pinMode(6, OUTPUT); // green
  pinMode(5, OUTPUT); // red
  pinMode(4, OUTPUT); // yellow

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
        digitalWrite(6, HIGH);
        startupBeep();
        // wait for startup to finish
        delay(500);
        systemState = 1;
      }
    }
  }

  else if (systemState == 1) {
    int beamBroken = digitalRead(laserPin);
    Serial.print("Armed - Pin 7 reads: ");
    Serial.print(beamBroken);
    Serial.print(" (");
    Serial.print(beamBroken == HIGH ? "HIGH" : "LOW");
    Serial.println(")");

    digitalWrite(6, HIGH);

    if (beamBroken == HIGH) {
      Serial.println("BEAM BROKEN - Triggering alert!");
      // turn red led on
      digitalWrite(6, LOW); // green off
      digitalWrite(5, HIGH); // red on

      systemState = 2;
      alertStartTime = millis(); // Start alert timer
      currentTone = 0;
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
        noTone(buzzerPin);
        digitalWrite(buzzerPin, LOW); // ensure buzzer is off

        // flash yellow light
        digitalWrite(6, LOW);
        digitalWrite(4, HIGH);

        // shutdown sound
        delay(700);
        shutdownBeep();

        delay(300);
        digitalWrite(4, LOW);

        systemState = 0;
      } else {
        Serial.print("Three second shutdown...");
        noTone(buzzerPin);
        digitalWrite(buzzerPin, LOW); // ensure buzzer is off

        // yellow light
        digitalWrite(6, LOW);
        digitalWrite(4, HIGH);

        // shutdown sound 2
        delay(700);
        shutdownBeep2();

        delay(2300);
        digitalWrite(4, LOW);

        systemState = 1;
      }
    }
  }

  else if (systemState == 2) {
    // alert state, non-blocking alert while beam broken
    int beamBroken = digitalRead(laserPin);
    Serial.println(beamBroken);

    // Check if 5 seconds have passed since alert started
    unsigned long currentTime = millis();
    if (currentTime - alertStartTime >= alertDuration) {
      // Stop alarm after 5 seconds
      noTone(buzzerPin);
      digitalWrite(5, LOW); // red off
      digitalWrite(6, HIGH); // green on
      systemState = 1; // return to armed
    } else {
      // Continue non-blocking alert
      if (currentTime - lastToneChange >= 200) {
        if (currentTone == 0) {
          tone(buzzerPin, 3500);
          currentTone = 1;
        } else {
          tone(buzzerPin, 4500);
          currentTone = 0;
        }
        lastToneChange = currentTime;
      }
    }
    // Allow button press to shutdown during alert
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
        noTone(buzzerPin); // stop alert
        digitalWrite(buzzerPin, LOW); // ensure buzzer is off

        // flash yellow light
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);

        // shutdown sound
        delay(700);
        shutdownBeep();

        delay(300);
        digitalWrite(4, LOW);

        systemState = 0;
      } else {
        Serial.println("Three second shutdown...");
        noTone(buzzerPin); // stop alert
        digitalWrite(buzzerPin, LOW); // ensure buzzer is off

        // yellow light
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);

        // shutdown sound 2
        delay(700);
        shutdownBeep2();

        delay(2300);
        digitalWrite(4, LOW);

        systemState = 1;
      }
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

// shutdown sound 2
void shutdownBeep2() {
  tone(buzzerPin, 400, 300);
  delay(300);
  noTone(buzzerPin);
}
