#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
const int buttonPin = 15;
int lastState = HIGH;
void setup() {
  Serial.begin(115200);
  
  // 영문, 숫자, _, - 만 사용하여 32자 이내로 작성하세요.
  SerialBT.begin("ESP32_Button_Check_01"); 
  
  Serial.println("블루투스 시작! PC와 페어링 후 터미널을 확인하세요.");
  
  pinMode(buttonPin, INPUT_PULLUP);
}void loop() {
  int currentState = digitalRead(buttonPin);
  if (currentState != lastState) {
    if (currentState == LOW) {
      // 버튼이 눌렸을 때
      SerialBT.println("Button Pressed!"); // 블루투스로 전송
      Serial.println("Sent: Button Pressed!"); // USB 시리얼로 로그 확인
    } else {
      // 버튼이 떨어졌을 때
      SerialBT.println("Button Released");
      Serial.println("Sent: Button Released");
    }
    lastState = currentState;
    delay(50); // 디바운싱
  }
}