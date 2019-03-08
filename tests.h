//
// Created by mfbut on 2/26/2019.
//

#ifndef CURSESWRAPPERTESTER_TESTS_H
#define CURSESWRAPPERTESTER_TESTS_H

#include "gtest/gtest.h"
#include "Window.h"

::testing::AssertionResult operator==(const Curses::Window& lhs, const Curses::Window& rhs);
void testCursorMoves(Curses::Window& win, int row, int col);
void testCursorMovesLeft(Curses::Window& win, int amount, int newRow, int newCol);
void testCursorMovesRight(Curses::Window& win, int amount, int newRow, int newCol);
void testCursorMovesUp(Curses::Window& win, int amount, int newRow, int newCol);
void testCursorMovesDown(Curses::Window& win, int amount, int newRow, int newCol);

#endif //CURSESWRAPPERTESTER_TESTS_H
