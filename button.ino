const int ledPin = 2;                    // LED
const int buttonPin = 15;                // 버튼
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);     // 내부 풀업 사용
}void loop() {
  int buttonState = digitalRead(buttonPin);
  // 풀업 모드이므로 버튼을 누르면 LOW
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);         // LED 켜기
  } else {
    digitalWrite(ledPin, LOW);          // LED 끄기
  }
}