#include <BleKeyboard.h>
#include <Keypad.h>
#include <esp_mac.h>
BleKeyboard* bleKeyboard;
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},  // 1-3:F13~F15, A:VolUp
  {'4','5','6','B'},  // 4-6:F16~F18, B:VolDown
  {'7','8','9','C'},  // 7-9:F19~F21, C:Mute
  {'*','0','#','D'}   // *:F22, 0:F23, #:F24, D:Win+D
};
byte rowPins[ROWS] = {13, 12, 14, 27}; 
byte colPins[COLS] = {26, 25, 33, 32}; 
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
bool isConnected = false; 
void setup(){
  Serial.begin(115200);
  customKeypad.setHoldTime(200); 
  customKeypad.setDebounceTime(20);
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_BT);
  char deviceName[20];
  sprintf(deviceName, "esp32-%02X%02X", mac[4], mac[5]);
  Serial.print("장치 이름: ");
  Serial.println(deviceName);
  bleKeyboard = new BleKeyboard(deviceName, "Maker", 100);
  bleKeyboard->begin();
  
  Serial.println("----------------------------------");
  Serial.println("블루투스 시작 (연결 대기 중...)");
  Serial.println("----------------------------------");
}
void loop(){
  // 1. 연결
  if (bleKeyboard->isConnected()){
    if (!isConnected){
      isConnected = true;
      Serial.println(">>> 블루투스 연결됨! (Ready)");
      bleKeyboard->releaseAll(); 
      delay(100);
    }
  }else {
    if (isConnected){
      isConnected = false;
      Serial.println("<<< 블루투스 연결 끊김 (Waiting...)");
    }
    return; 
  }
  // 2. 키패드 스캔
  bool keysChanged = customKeypad.getKeys(); 
  for (int i = 0; i < LIST_MAX; i++){
    if (customKeypad.key[i].kstate == IDLE)continue;
    char currentKey = customKeypad.key[i].kchar;
    KeyState currentState = customKeypad.key[i].kstate;
    bool stateChanged = customKeypad.key[i].stateChanged;
    if (currentKey == 'A' || currentKey == 'B'){
       if (currentState == PRESSED || currentState == HOLD){
          switch (currentKey){
              case 'A': // 볼륨 업
                Serial.println("Key: Vol Up (Repeat)");
                bleKeyboard->write(KEY_MEDIA_VOLUME_UP);
                delay(120); 
                break;
              case 'B': // 볼륨 다운
                Serial.println("Key: Vol Down (Repeat)");
                bleKeyboard->write(KEY_MEDIA_VOLUME_DOWN);
                delay(120); 
                break;
          }
       }
    }

    else if (keysChanged && stateChanged && currentState == PRESSED){
        switch (currentKey){
            // 1행
            case '1': Serial.println("Key: F13"); bleKeyboard->write(KEY_F13); break;
            case '2': Serial.println("Key: F14"); bleKeyboard->write(KEY_F14); break;
            case '3': Serial.println("Key: F15"); bleKeyboard->write(KEY_F15); break;
            
            // 2행
            case '4': Serial.println("Key: F16"); bleKeyboard->write(KEY_F16); break;
            case '5': Serial.println("Key: F17"); bleKeyboard->write(KEY_F17); break;
            case '6': Serial.println("Key: F18"); bleKeyboard->write(KEY_F18); break;
            
            // 3행
            case '7': Serial.println("Key: F19"); bleKeyboard->write(KEY_F19); break;
            case '8': Serial.println("Key: F20"); bleKeyboard->write(KEY_F20); break;
            case '9': Serial.println("Key: F21"); bleKeyboard->write(KEY_F21); break;
            
            // 4행 및 특수키
              Serial.println("Key: Mute"); 
              bleKeyboard->write(KEY_MEDIA_MUTE); 
              break;
            case '*': Serial.println("Key: F22"); bleKeyboard->write(KEY_F22); break;
            case '0': Serial.println("Key: F23"); bleKeyboard->write(KEY_F23); break;
            case '#': Serial.println("Key: F24"); bleKeyboard->write(KEY_F24); break;
            case 'D': 
              Serial.println("Key: Win+D");
              bleKeyboard->releaseAll(); 
              delay(50); 
              bleKeyboard->press(KEY_LEFT_GUI);
              delay(150); 
              bleKeyboard->press('d');
              delay(100); 
              bleKeyboard->releaseAll();
              break;
        }
    }
  }
}