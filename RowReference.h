//
// Created by mfbut on 2/22/2019.
//

#ifndef CURSESWRAPPER_ROWREFERENCE_H
#define CURSESWRAPPER_ROWREFERENCE_H
#include "Window.h"
#include "CellReference.h"




namespace Curses {

//forward declarations
class Window;
class CellReference;

/* A row reference keeps track of what row it is
 * on inside of a particular window. It will be used
 * to help implement window[i][j] = some character.
 * Because there is no operator[][] just an operator[]
 * we are going to have to return create some temporary classes
 * to help us keep track of where we are at. If we break down
 * the statement window[i][j] =some character
 * into its corresponding operators instead we have
 * window.operator[](i).operator[](j) = some character
 * window.operator[](i) returns a row reference, which is once again
 * keeping track of what window it is over and what row it is on.
 *
 * So now we have
 * RowReference(window, i).operator[](j) = some character
 * RowReference's operator [] returns a cellReference that
 * keeps track of what row,col it is at in a window.
 *
 * We then overload the Cell Reference's assignment operator to allow us
 * to go update the window. This works because the cell reference
 * has a reference to the window and the row and column and so
 * can just call the windows addCharacter method.
 *
 */
class RowReference {
 public:
  RowReference(Window& win, const int row);

  //return a cell reference tracking
  //your window, your row, and your column
  CellReference at(int col);
  //same as at
  CellReference operator[](int col);

 protected:
  Window& win;
  const int row;
};
}

#endif //CURSESWRAPPER_ROWREFERENCE_H
