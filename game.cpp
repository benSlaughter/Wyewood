// Library header
#include "Game.h"

Game::Game(Input& input, Output& output, Countdown& countdown) : _input(input), _output(output), _countdown(countdown) {
  _active = false;
}

void Game::begin() {
  _code[0] = '3';
  _code[1] = '3';
  _code[2] = '4';
  _code[3] = '5';

  _reset();
}

void Game::update() {
  if (digitalRead(GREEN_SW_PIN) == LOW || digitalRead(RED_SW_PIN) == LOW) {
    _codeEntry();
  }
}

void Game::_codeEntry() {
  char key = _input.keypad.getKey();
  if (key && _isNum(key))
  {
    _output.beep();
    *_entry_char = key;
    _entry_char++;
    _entry_int++;

    _codeDiaplay();

    if (_entry_int > 3) {
      delay(200);
      if (_check()) {
        if (digitalRead(GREEN_SW_PIN) == LOW) {
          _countdown.start();
          _output.setArmed();
        } else {
          _countdown.stop();
          _output.setIdle();
        }

        _output.pass();
      } else {
        _output.fail();
      }
      _reset();
    }
  }
}

void Game::_codeDiaplay() {
  String inst = "Enter Code: ";
  char final[20];

  inst += _entry;
  inst.toCharArray(final, 20);
  _output.setInstruction(final);
}

bool Game::_isNum(char c) {
  char numbers[10] = {'1','2','3','4','5','6','7','8','9','0'};
  for(int y=0; y<10; y++) {
    if(c == numbers[y]) {
      return true;
    }
  }
  return false;
}

bool Game::_check() {
  for(int i=0; i<4; i++) {
    if (_code[i] != _entry[i]) {
      return false;
    }
  }
  return true;
}

void Game::_reset() {
  _entry_char = &_entry[0];
  _entry_int = 0;
  _entry[0] = '-';
  _entry[1] = '-';
  _entry[2] = '-';
  _entry[3] = '-';
  _output.setInstruction("Enter Code:     ");
}