#include <LiquidCrystal.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_ADXL345_U.h>
#include <Keypad.h>

#include "Input.h"
#include "Output.h"
#include "Countdown.h"
#include "Game.h"

Input     bomb_input;
Output    bomb_output;
Countdown countdown(bomb_output);
Game      game(bomb_input, bomb_output, countdown);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Setup");
  
  bomb_output.begin();
  bomb_input.begin();
  countdown.begin();
  game.begin();
  
  Serial.println("Completed Setup");
}

void loop() {
  bomb_output.update();
  countdown.update();
  game.update();
}
