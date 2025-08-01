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

  Serial.begin(9600);
  startupBeep();
}

void loop() {}
