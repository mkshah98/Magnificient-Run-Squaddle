//
// Created by mfbut on 2/24/2019.
//

#ifndef CURSESWRAPPER_CELLREFERENCE_H
#define CURSESWRAPPER_CELLREFERENCE_H

#include "Window.h"
namespace Curses {

class Window;

class CellReference {

 public:
  CellReference(Window& win, const int row, const int col);

  //update the window at your row,col to be letter
  CellReference& operator=(const char letter);
  //return the character at row,col in the window
  operator char() const;

 protected:
  Window& win;
  const int row;
  const int col;
};
}

#endif //CURSESWRAPPER_CELLREFERENCE_H
