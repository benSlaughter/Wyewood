// Library header
#include "Countdown.h"

Countdown::Countdown(Output& output) : _output(output) {
  _active     = false;
  timeMinutes = 5;
  timeSeconds = 0;
  interval    = 100;
  restart     = false;
}

bool Countdown::active() {
  return _active;
}

void Countdown::begin() {
  Serial.println("Starting Countdown config");
  _timeMinutes = timeMinutes;
  _timeSeconds = timeSeconds;
  Serial.println("Completed Countdown config");
}

void Countdown::start() {
  _active = true;
  _previousMillis = millis()/10;
  _output.setArmed();
  
  if(restart) {
    _timeMinutes = timeMinutes;
    _timeSeconds = timeSeconds;
  }
}

void Countdown::stop() {
  _active = false;
}

void Countdown::update() {
  long currentMillis = millis()/10;
  
  if(currentMillis - _previousMillis > interval && _active) {
    _output.printTime(_timeMinutes, _timeSeconds);
    _output.beep();
    _previousMillis = currentMillis;

    Serial.print(_timeMinutes);
    Serial.print(":");
    Serial.println(_timeSeconds);

    if(_timeSeconds > 0) {
      _timeSeconds--;
    } else {
      if(_timeMinutes > 0) {
        _timeSeconds = 59;
        _timeMinutes--;
      } else {
        _active = false;
        _output.setDet();
        _output.flatLine();
      }
    }
  }
}
