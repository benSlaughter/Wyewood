#ifndef Output_h
#define Output_h

#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include "input.h"

#define DET_PIN_ONE    9
#define DET_PIN_TWO    8

#define GREEN_LED_PIN  7
#define YELLOW_LED_PIN 6
#define RED_LED_PIN    5
#define SPEAKER_PIN    4
#define GREEN_SWL_PIN  3
#define RED_SWL_PIN    2


#define LCD_RS_PIN     22
#define LCD_EN_PIN     24
#define LCD_DATA4_PIN  26
#define LCD_DATA5_PIN  28
#define LCD_DATA6_PIN  30
#define LCD_DATA7_PIN  32

class Output {
  LiquidCrystal _lcd;
  Adafruit_7segment _matrix;
  byte _redPin;
  byte _yellowPin;
  byte _greenPin;
  byte _speakerPin;
  void _clearStatus();
public:
  Output();
  void begin();
  void update();
  void beep();
  void fail();
  void pass();
  void flatLine();
  void setStatus(char *str);
  void setInstruction(char *str);
  void setReady();
  void setIdle();
  void setArmed();
  void setDet();
  void printTime(int large, int small);
  void clearTime();
};

#endif
