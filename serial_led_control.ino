const int ledPin = 2; 
void setup() {
  Serial.begin(115200);        // 시리얼 통신 시작 (통신속도 115200)
  pinMode(ledPin, OUTPUT);     // LED 핀 설정
  Serial.println("LED 제어 시작: 1을 누르면 ON, 0을 누르면 OFF");
}void loop() {
  // 시리얼 포트에 수신된 데이터가 있는지 확인
  if (Serial.available() > 0) {
    char input = Serial.read(); // 1바이트 읽기
    if (input == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED가 켜졌습니다.");
    }
    else if (input == '0') {
      digitalWrite(ledPin, LOW);
      Serial.println("LED가 꺼졌습니다.");
    }
  }
}
