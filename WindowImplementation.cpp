//
// Created by mfbut on 2/24/2019.
//
#include "WindowImplementation.h"

/*
 * I've already added the cut to initialize curses if it hasn't been called
 * and to create the window. You may still need to do more initialization if
 * you have other members
 */
Curses::WindowImplementation::WindowImplementation(int numRows, int numCols, int startRow, int startCol) :
    cursesWindow(nullptr, delwin) {
  if (!stdscr) {
    initscr();
  }
  cursesWindow = std::unique_ptr<WINDOW, decltype(delwin)*>(newwin(numRows, numCols, startRow, startCol), delwin);
}

Curses::WindowImplementation::WindowImplementation(int numRows, int numCols) : WindowImplementation(numRows,
                                                                                                    numCols,
                                                                                                    0,
                                                                                                    0) {

}

//the unique pointer will automatically delete itself
//but if you dynamically allocate any more space for this
//problem make sure to free it here.
Curses::WindowImplementation::~WindowImplementation() = default;

char Curses::WindowImplementation::getWindowChar(int row, int col) {
  return mvwgetch(cursesWindow.get(), row, col);
}

char Curses::WindowImplementation::getWindowChar() {
  return getWindowChar(getCurRow(), getCurCol());
}

char Curses::WindowImplementation::getCharInput(int row, int col) {
  return mvwgetch(cursesWindow.get(),row, col);
}

char Curses::WindowImplementation::getCharInput() {
  return getCharInput(getCurRow(),getCurCol());
}

std::string Curses::WindowImplementation::getStringInput(int row, int col) {
  std::string win_string;
  int i = col;

  while(getCharInput(row, i) != '\0' && getmaxx(cursesWindow.get()) != i + 1) {
    win_string += getCharInput(row, i);
    ++i;
  }
  win_string += '\0';
  return win_string;
}

std::string Curses::WindowImplementation::getStringInput() {
  return getStringInput(getCurRow(), getCurCol());
}

void Curses::WindowImplementation::addCharacter(int row, int col, char value) {
  int oriRow = getcury(cursesWindow.get());
  int oriCol = getcurx(cursesWindow.get());
  mvwaddch(cursesWindow.get(), row, col, value);
  wmove(cursesWindow.get(), oriRow, oriCol);
  change_cursor();
}

void Curses::WindowImplementation::addCharacter(char value) {
  addCharacter(getCurRow(), getCurCol(), value);
}

void Curses::WindowImplementation::addString(int row, int col, const std::string& str) {
    wmove(cursesWindow.get(), row, col);
    for(const auto& letter : str) {
        addCharacter(letter);
    }
}

void Curses::WindowImplementation::addString(const std::string& str) {
    addString(getcury(cursesWindow.get()), getcurx(cursesWindow.get()), str);
}

int Curses::WindowImplementation::getRowStart() const {
  return getbegy(cursesWindow.get());
}

int Curses::WindowImplementation::getColStart() const {
  return getbegx(cursesWindow.get());
}

int Curses::WindowImplementation::getNumRows() const {
  return getmaxy(cursesWindow.get());
}

int Curses::WindowImplementation::getNumCols() const {
  return getmaxx(cursesWindow.get());
}

int Curses::WindowImplementation::getCurRow() const {
  return getcury(cursesWindow.get());
}

int Curses::WindowImplementation::getCurCol() const {
  return getcurx(cursesWindow.get());
}

void Curses::WindowImplementation::moveCursor(int row, int col) {
  wmove(cursesWindow.get(), row, col);
}

void Curses::WindowImplementation::moveCursorLeft(int amount) {
  if (getcurx(cursesWindow.get()) < amount) {
    amount = getcurx(cursesWindow.get());
  }
  wmove(cursesWindow.get(), getcury(cursesWindow.get()), getcurx(cursesWindow.get())-amount);
}

void Curses::WindowImplementation::moveCursorRight(int amount) {
  int current = getcurx(cursesWindow.get());
  if (amount + getcurx(cursesWindow.get()) >= getmaxx(cursesWindow.get()) - 1) {
      amount = getmaxx(cursesWindow.get()) - 1;
      current = 0;
  }
  wmove(cursesWindow.get(), getcury(cursesWindow.get()), amount + current);
}

void Curses::WindowImplementation::moveCursorUp(int amount) {
  if (getcury(cursesWindow.get()) < amount) {
    amount = getcury(cursesWindow.get());
  }
  wmove(cursesWindow.get(), getcury(cursesWindow.get()) - amount, getcurx(cursesWindow.get()));
}

void Curses::WindowImplementation::moveCursorDown(int amount) {
  int current = getcury(cursesWindow.get());
  if (amount + getcury(cursesWindow.get()) >= getmaxy(cursesWindow.get()) - 1) {
    amount = getmaxy(cursesWindow.get()) - 1;
    current = 0;
  }
  wmove(cursesWindow.get(), current + amount, getcurx(cursesWindow.get()));
}

void Curses::WindowImplementation::setAdvanceCursorOn() {
  advancing_status = true;
}

void Curses::WindowImplementation::setAdvanceCursorOff() {
  advancing_status = false;
}

Curses::RowReference Curses::WindowImplementation::at(int row) {
  return Curses::RowReference(*this, row);
}

Curses::RowReference Curses::WindowImplementation::operator[](int row) {
  return RowReference(*this, row);
}

void Curses::WindowImplementation::refresh() {
  wrefresh(cursesWindow.get());
}

void Curses::WindowImplementation::log(std::ostream& out) {

 /* for (int i = 0; i < getNumRows(); i++) {
    for (int k = 0; k < getNumCols(); k++) {
      out << getWindowChar(i , k);
    }
    out << std::endl;
  }*/
}

void Curses::WindowImplementation::change_cursor() {
    // THIS is only for advancing cursor to right by one with wrapping

    int maxX = getmaxx(cursesWindow.get());
    int maxY = getmaxy(cursesWindow.get());
    int curX = getcurx(cursesWindow.get());
    int curY = getcury(cursesWindow.get());

    if (advancing_status) {
        if (maxX == curX + 1 && maxY == curY + 1) {   // bottom right corner
        }
        else if (maxX == curX + 1 && maxY != curY + 1) {   // end of a row
          wmove(cursesWindow.get(), curY + 1, 0); }
        else { wmove(cursesWindow.get(), curY, curX + 1); } // within window borders
    }

}
