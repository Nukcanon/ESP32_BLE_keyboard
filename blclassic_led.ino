#include "BluetoothSerial.h"
BluetoothSerial SerialBT; // 블루투스 객체 생성
const int ledPin = 2; // 내장 LED 및 외부 LED
void setup() {
  Serial.begin(115200);
  
  // 블루투스 장치 이름 설정
  // 영문, 숫자, _, - 만 사용하여 32자 이내로 작성하세요.
  SerialBT.begin("ESP32_LED_Control_01"); 
  
  Serial.println("블루투스가 시작되었습니다. PC와 페어링하세요.");
  
  pinMode(ledPin, OUTPUT);
}void loop() {
  // 블루투스로부터 데이터가 들어왔는지 확인
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read(); // 데이터 읽기
    if (incomingChar == '1') {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED ON"); // 블루투스로 응답 보내기
      Serial.println("BT: LED ON"); // 시리얼 모니터에 로그 남기기
    }
    else if (incomingChar == '0') {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED OFF");
      Serial.println("BT: LED OFF");
    }
  }
  delay(20);
}