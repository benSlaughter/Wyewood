#ifndef Game_h
#define Game_h

#include "Input.h"
#include "Output.h"
#include "Countdown.h"

class Game {
  Output& _output;
  Input& _input;
  Countdown& _countdown;
  char _code[5];
  char _entry[5];
  bool _active;
  char * _entry_char;
  int _entry_int;
  void _codeEntry();
  void _codeDiaplay();
  bool _isNum(char c);
  bool _check();
  void _reset();
public:
  Game(Input&, Output&, Countdown&);
  void begin();
  void update();
};

#endif
