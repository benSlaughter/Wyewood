#ifndef Countdown_h
#define Countdown_h

#include "Output.h"

class Countdown {
  Output& _output;
  boolean _active;
  long _previousMillis;
  int _timeMinutes;
  int _timeSeconds;
  
public:
  Countdown(Output&);
  void begin();
  void update();
  void start();
  void stop();
  bool active();
  int  timeMinutes;
  int  timeSeconds;
  int  interval;
  boolean restart;
};

#endif
