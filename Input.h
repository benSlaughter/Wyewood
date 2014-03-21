#ifndef Input_h
#define Input_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Keypad.h>

#define ROW_NUM 4
#define COL_NUM 4
#define ROW_PINS {34, 36, 38, 40}
#define COL_PINS {42, 44, 46, 48}
#define KEYBOARD {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'Y','0','N','D'}}

class Input {
  Adafruit_ADXL345_Unified _accel;
  int _threashold;
public:
  Input();
  Keypad keypad;
  void begin();
  void update();
  void displaySensorDetails();
  boolean triggered;
};

#endif
