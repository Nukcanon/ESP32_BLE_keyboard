const int ledPin = 2;     // GPIO 2번 사용
// PWM 설정 변수
const int freq = 5000;    // 주파수 5000Hz
const int ledChannel = 0; // 채널 0번 사용 (0~15)
const int resolution = 8; // 해상도 8비트 (0~255 단계로 조절)
void setup(){
  // 1. 채널 설정
  ledcSetup(ledChannel, freq, resolution);
  // 2. 핀을 채널에 할당
  ledcAttachPin(ledPin, ledChannel);
}
void loop(){
  // 서서히 밝아지기 (0부터 255까지 증가)
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledChannel, dutyCycle); // 해당 채널에 PWM 값 출력
    delay(10); // 밝기 변화 속도 조절
  }
  // 서서히 어두워지기 (255부터 0까지 감소)
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledChannel, dutyCycle);
    delay(10);
  }
}
