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
