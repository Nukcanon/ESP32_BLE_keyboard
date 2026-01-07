#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27}; 
byte colPins[COLS] = {26, 25, 33, 32}; 
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
void setup() {
  Serial.begin(115200);
  Serial.println("키패드 입력을 시작합니다...");
}void loop() {
  char key = myKeypad.getKey();
  if (key) {
    Serial.print("입력된 키: ");
    Serial.println(key);
  }
}
