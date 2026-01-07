const int buttonPin = 15; // 버튼 연결 핀
int lastState = HIGH;      // 이전 버튼 상태 저장 (초기값 HIGH)
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}void loop() {
  int currentState = digitalRead(buttonPin); // 현재 버튼 상태 읽기
  // 상태가 변했을 때만 출력
  if (currentState != lastState) {
    if (currentState == LOW) {
      Serial.println("버튼이 눌렸습니다!");
    } else {
      Serial.println("버튼이 떨어졌습니다.");
    }
    lastState = currentState; // 현재 상태를 저장
    delay(50); // 디바운싱 방지를 위한 짧은 지연
  }
}
