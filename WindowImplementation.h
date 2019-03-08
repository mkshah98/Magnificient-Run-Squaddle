//
// Created by mfbut on 2/24/2019.
//

#ifndef CURSESWRAPPER_WINDOWIMPLEMENTATION_H
#define CURSESWRAPPER_WINDOWIMPLEMENTATION_H
#include <memory>
#include "ncurses.h"
#include "Window.h"

namespace Curses {
class WindowImplementation : public Window {
 public:
  WindowImplementation(int numRows, int numCols, int startRow, int startCol);
  WindowImplementation(int numRows, int numCols);
  virtual ~WindowImplementation();

  virtual char getWindowChar(int row, int col) override;
  virtual char getWindowChar() override;
  virtual char getCharInput(int row, int col) override;
  virtual char getCharInput() override;
  virtual std::string getStringInput(int row, int col) override;
  virtual std::string getStringInput() override;
  virtual void addCharacter(int row, int col, char value) override;
  virtual void addCharacter(char value) override;
  virtual void addString(int row, int col, const std::string& str) override;
  virtual void addString(const std::string& str) override;
  virtual int getRowStart() const override;
  virtual int getColStart() const override;
  virtual int getNumRows() const override;
  virtual int getNumCols() const override;
  virtual int getCurRow() const override;
  virtual int getCurCol() const override;
  virtual void moveCursor(int row, int col) override;
  virtual void moveCursorLeft(int amount) override;
  virtual void moveCursorRight(int amount) override;
  virtual void moveCursorUp(int amount) override;
  virtual void moveCursorDown(int amount) override;
  virtual void setAdvanceCursorOn() override;
  virtual void setAdvanceCursorOff() override;
  virtual RowReference at(int row) override;
  virtual RowReference operator[](int row) override;
  virtual void refresh() override;
  virtual void log(std::ostream& out) override;

  void change_cursor();
 protected:
  //a unique pointer to a window that will call
  //delwin to destroy the window
  //the optional second argument to unique_ptr
  //is a function that will be called to delete the object
  //by default it is just delete but we are going to want to
  //call delwin in this situation
  //decltype(expression) tells you the type of expression
  std::unique_ptr<WINDOW, decltype(delwin)*> cursesWindow;

private:
    bool advancing_status;
};
}
#endif //CURSESWRAPPER_WINDOWIMPLEMENTATION_H
