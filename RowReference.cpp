//
// Created by mfbut on 2/22/2019.
//

#include "RowReference.h"

Curses::RowReference::RowReference(Curses::Window& win, const int row): win(win), row(row){}

Curses::CellReference Curses::RowReference::at(int col) {
    return Curses::CellReference(win, row, col);
}

Curses::CellReference Curses::RowReference::operator[](int col) {
    return Curses::CellReference(win,row,col);
}
