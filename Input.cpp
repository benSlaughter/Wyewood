// Library header
#include "Input.h"

byte rowPins[ROW_NUM] = ROW_PINS;
byte colPins[COL_NUM] = COL_PINS;
char hexaKeys[ROW_NUM][COL_NUM] = KEYBOARD;

Input::Input() : keypad(makeKeymap(hexaKeys), rowPins, colPins, ROW_NUM, COL_NUM) {
  keypad.setDebounceTime(50);
  _accel = Adafruit_ADXL345_Unified(12345);

  pinMode(GREEN_SW_PIN, INPUT_PULLUP);
  pinMode(RED_SW_PIN, INPUT_PULLUP);
  pinMode(KEY_PIN, INPUT_PULLUP);
}

void Input::begin() {
  Serial.println("Starting Input config");
  _accel.begin();
  _accel.setRange(ADXL345_RANGE_16_G);
  displaySensorDetails();

  _threashold = 100;
  triggered = false;
  Serial.println("Completed Input config");
}

void Input::displaySensorDetails() {
  sensor_t sensor;
  _accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
}

void Input::update() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  _accel.getEvent(&event);
  
  if(!triggered && (event.acceleration.z > _threashold || event.acceleration.z < -_threashold)) {
    triggered = true;
    Serial.println("TRIGGERED!");
  }
}
