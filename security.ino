// c++
const byte piezoPin = 3;
const int photoPin = A0;
const int threshold = 500;

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
