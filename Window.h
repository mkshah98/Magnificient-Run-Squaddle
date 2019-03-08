//
// Created by mfbut on 2/21/2019.
//

#ifndef CURSESWRAPPER_WINDOW_H
#define CURSESWRAPPER_WINDOW_H

#include <vector>
#include <string>
#include <ostream>
#include "RowReference.h"

namespace Curses {
class RowReference;
class CellReference;

class Window {
 public:
  //Window(int numRows, int numCols, int rowStart, int colStart);

  //move the cursor to row,col and then get the character that is there
  //the cursor remains at row,col after this operation
  virtual char getWindowChar(int row, int col) = 0;
  //get the character where the cursor is currently located
  //do not advance the cursor
  virtual char getWindowChar() = 0;

  //move the cursor to row,col and then get a character from the user
  //the cursor should remain at row,col
  virtual char getCharInput(int row, int col) = 0;
  //get a character from the user
  //do not advance the cursor
  virtual char getCharInput() = 0;

  //move the cursor to row,col and then get a string from them
  //the cursor should remain at row, col after the operation
  virtual std::string getStringInput(int row, int col) = 0;
  //get a string from the user.
  //do not advance the cursor
  virtual std::string getStringInput() = 0;

  //move the cursor to row,col and the print the character
  //if advancing the cursor is enabled, the cursor should
  //move to the next cell after row,col with wrapping
  //if advancing the cursor is disabled it should
  //remain at row,col
  virtual void addCharacter(int row, int col, char value) = 0;

  virtual ~Window() {}

  //print the character at the current location
  //if advancing the cursor is enabled, the cursor should
  //move to the next cell after row,col with wrapping
  //if advancing the cursor is disabled it should
  //remain at row,col
  virtual void addCharacter(char value) = 0;

  //move to row,col and then add string to the screen with wrapping.
  //if cursor advancement is on then the cursor should
  //end up one cell beyond the last cell written to.
  //if it is off it should end up at the last cell written to
  virtual void addString(int row, int col, const std::string& str) = 0;

  //add a string to the screen based on the current cursor position
  //with wrapping.
  //if cursor advancement is on then the cursor should
  //end up one cell beyond the last cell written to.
  //if it is off it should end up at the last cell written to
  virtual void addString(const std::string& str) = 0;

  //get the row that this window starts at
  virtual int getRowStart() const = 0;
  //get the column this window starts at
  virtual int getColStart() const = 0;

  //get the number of rows in this window
  virtual int getNumRows() const = 0;
  //get the number of columns in this window
  virtual int getNumCols() const = 0;

  //get the row the cursor is on
  virtual int getCurRow() const = 0;
  //get the column the cursor is on
  virtual int getCurCol() const = 0;

  //move the cursor to the desired location
  virtual void moveCursor(int row, int col) = 0;

  //move the cursor the desired amount stopping at the
  //edge if moving the amount would take you off the board
  //if no amount is given it should move 1
  virtual void moveCursorLeft(int amount = 1) = 0;
  virtual void moveCursorRight(int amount = 1) = 0;
  virtual void moveCursorUp(int amount = 1) = 0;
  virtual void moveCursorDown(int amount = 1) = 0;

  //turn cursor advancement on. (it is on by default)
  //if cursor advancement is on when a character
  //or string is written to the screen the cursor
  //will be advanced to the cell after the last one written to
  //wrapping happens if at the end of a row
  //(if the last character written to is at the end of a
  //a row the cursor moves to the first cell of the next row
  //but if we are on the last row then it stays in the
  //bottom right corner)
  virtual void setAdvanceCursorOn() = 0;

  //turn cursor advancement off. (it is on by default)
  //when cursor advancement is off the cursor ends on
  //the cell that contains the last cell written
  virtual void setAdvanceCursorOff() = 0;

  //these methods are going to allow s to do
  //window[i][j] = some character
  //see both RowReference and CellReference for more details
  virtual RowReference at(int row) = 0;
  virtual RowReference operator[](int row) = 0;

  //put the contents on the screen
  virtual void refresh() = 0;

  //write the contents of the screen to the stream
  virtual void log(std::ostream& out) = 0;
};
}
#endif //CURSESWRAPPER_WINDOW_H
