#include "Output.h"

Output::Output() : _lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_DATA4_PIN, LCD_DATA5_PIN, LCD_DATA6_PIN, LCD_DATA7_PIN) { 
  
  _redPin      = RED_LED_PIN;
  _yellowPin   = YELLOW_LED_PIN;
  _greenPin    = GREEN_LED_PIN;
  _speakerPin  = SPEAKER_PIN;
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(GREEN_SWL_PIN, OUTPUT);
  pinMode(RED_SWL_PIN, OUTPUT);

  pinMode(DET_PIN_ONE, OUTPUT);
  pinMode(DET_PIN_TWO, OUTPUT);

  digitalWrite(GREEN_SWL_PIN, LOW);
  digitalWrite(RED_SWL_PIN, LOW);

  digitalWrite(DET_PIN_ONE, LOW);
  digitalWrite(DET_PIN_TWO, LOW);
}

void Output::begin() {
  Serial.println("Starting Output config");
  _matrix = Adafruit_7segment();
  _lcd.begin(20,4);
  _matrix.begin(0x70);
  
  Serial.print("DEBUG:redPin:");Serial.println(_redPin);
  Serial.print("DEBUG:yellowPin:");Serial.println(_yellowPin);
  Serial.print("DEBUG:greenPin:");Serial.println(_greenPin);
  Serial.print("DEBUG:speakerPin:");Serial.println(_speakerPin);
  
  setReady();
  clearTime();
  Serial.println("Completed Output config");
  noTone(_speakerPin);
}

void Output::update() {
  digitalRead(GREEN_SW_PIN) == LOW ? digitalWrite(GREEN_SWL_PIN, HIGH) : digitalWrite(GREEN_SWL_PIN, LOW);
  digitalRead(RED_SW_PIN) == LOW ? digitalWrite(RED_SWL_PIN, HIGH) : digitalWrite(RED_SWL_PIN, LOW);
}

void Output::beep() {
  tone(_speakerPin, 587, 100);
}

void Output::fail() {
  tone(_speakerPin, 262, 300);
}

void Output::pass() {
  tone(_speakerPin, 2093, 300);
}

void Output::flatLine() {
  tone(_speakerPin, 880);
  delay(2000);
  noTone(_speakerPin);

  digitalWrite(DET_PIN_ONE, HIGH);
  digitalWrite(DET_PIN_TWO, HIGH);
}

void Output::setStatus(char *str) {
  _clearStatus();
  _lcd.setCursor(0, 0);
  _lcd.print("**");_lcd.print(str);_lcd.print("**");
}

void Output::setInstruction(char *str) {
  _lcd.setCursor(0, 1);
  _lcd.print(str);
}

void Output::setReady() {
  digitalWrite(_redPin, LOW);
  digitalWrite(_yellowPin, LOW);
  digitalWrite(_greenPin, HIGH);
  setStatus("READY");
}

void Output::setIdle() {
  digitalWrite(_redPin, LOW);
  digitalWrite(_yellowPin, HIGH);
  digitalWrite(_greenPin, LOW);
  setStatus("IDLE");
}

void Output::setArmed() {
  digitalWrite(_redPin, HIGH);
  digitalWrite(_yellowPin, LOW);
  digitalWrite(_greenPin, LOW);
  setStatus("ARMED");
}

void Output::setDet() {
  digitalWrite(_redPin, HIGH);
  digitalWrite(_yellowPin, HIGH);
  digitalWrite(_greenPin, HIGH);
  setStatus("DETONATE");
}

void Output::printTime(int large, int small) {
  _matrix.writeDigitNum(0, large / 10);
  _matrix.writeDigitNum(1, large % 10);
  _matrix.drawColon(true);
  _matrix.writeDigitNum(3, small / 10);
  _matrix.writeDigitNum(4, small % 10);
  _matrix.writeDisplay();
}

void Output::clearTime() {
  _matrix.writeDigitNum(0, 0);
  _matrix.writeDigitNum(1, 0);
  _matrix.drawColon(true);
  _matrix.writeDigitNum(3, 0);
  _matrix.writeDigitNum(4, 0);
  _matrix.writeDisplay();
}

void Output::_clearStatus() {
  _lcd.setCursor(0, 0);
  _lcd.print("                    ");
} 

