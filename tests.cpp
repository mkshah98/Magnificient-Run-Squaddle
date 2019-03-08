//
// Created by mfbut on 2/26/2019.
//

#include "tests.h"
#include <tuple>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include "gtest/gtest.h"
#include "CursesWrapperTest.h"
#include "WindowImplementation.h"

::testing::AssertionResult operator==(const Curses::Window& lhs, const Curses::Window& rhs) {

  if (lhs.getNumRows() != rhs.getNumRows()) {
    return ::testing::AssertionFailure() << "Windows do not have the same number of rows.\n" <<
                                         "Left hand side has " << lhs.getNumRows() << " but the right hand side has "
                                         << rhs.getNumRows();
  } else if (lhs.getNumCols() != rhs.getNumCols()) {
    return ::testing::AssertionFailure() << "Windows do not have the same number of columns.\n" <<
                                         "Left hand side has " << lhs.getNumCols() << " but the right hand side has "
                                         << rhs.getNumCols();
  } else if (lhs.getRowStart() != rhs.getRowStart()) {
    return ::testing::AssertionFailure() << "Windows do not start at the same row.\n" <<
                                         "Left hand side starts at " << lhs.getRowStart()
                                         << " but the right hand side starts at "
                                         << rhs.getRowStart();
  } else if (lhs.getColStart() != rhs.getColStart()) {
    return ::testing::AssertionFailure() << "Windows do not start at the same column.\n" <<
                                         "Left hand side starts at " << lhs.getColStart()
                                         << " but the right hand side starts at "
                                         << rhs.getColStart();
  } else if (lhs.getCurRow() != rhs.getCurRow()) {
    return ::testing::AssertionFailure() << "Cursors are not on the same row.\n" <<
                                         "Left hand side starts at " << lhs.getCurRow()
                                         << " but the right hand side starts at "
                                         << rhs.getCurRow();
  } else if (lhs.getCurCol() != rhs.getCurCol()) {
    return ::testing::AssertionFailure() << "Cursors are not on the same column.\n" <<
                                         "Left hand side starts at " << lhs.getCurCol()
                                         << " but the right hand side starts at "
                                         << rhs.getCurCol();
  } else {
    std::stringstream lhsContents, rhsContents;
    const_cast<Curses::Window&>(lhs).log(lhsContents);
    const_cast<Curses::Window&>(rhs).log(rhsContents);
    if (lhsContents.str() != rhsContents.str()) {
      return ::testing::AssertionFailure() << "Left hand side and right hand side have different contents.\n" <<
                                           "Left Hand Side:\n" << lhsContents.str() << "\n\nRight Hand Side\n"
                                           << rhsContents.str() << std::endl;
    }
  }

  return ::testing::AssertionSuccess();
}

void testCursorMoves(Curses::Window& win, int row, int col) {
  win.moveCursor(row, col);
  ASSERT_EQ(win.getCurRow(), row);
  ASSERT_EQ(win.getCurCol(), col);
}

void testCursorMovesLeft(Curses::Window& win, int amount, int newRow, int newCol) {
  win.moveCursorLeft(amount);
  ASSERT_EQ(win.getCurRow(), newRow);
  ASSERT_EQ(win.getCurCol(), newCol);
}

void testCursorMovesRight(Curses::Window& win, int amount, int newRow, int newCol) {
  win.moveCursorRight(amount);
  ASSERT_EQ(win.getCurRow(), newRow);
  ASSERT_EQ(win.getCurCol(), newCol);
}

void testCursorMovesUp(Curses::Window& win, int amount, int newRow, int newCol) {
  win.moveCursorUp(amount);
  ASSERT_EQ(win.getCurRow(), newRow);
  ASSERT_EQ(win.getCurCol(), newCol);
}

void testCursorMovesDown(Curses::Window& win, int amount, int newRow, int newCol) {
  win.moveCursorDown(amount);
  ASSERT_EQ(win.getCurRow(), newRow);
  ASSERT_EQ(win.getCurCol(), newCol);
}

TEST_F(CursesWrapperTest, DimensionsMatch) {
  std::vector<std::vector<int>> constructorArgs{
      {3, 4, 0, 0},
      {5, 9, 6, 2},
      {13, 27, 23, 62}
  };
  std::vector<std::unique_ptr<Curses::Window>> windows;
  for (const auto& args : constructorArgs) {
    windows.push_back(
        std::make_unique<Curses::WindowImplementation>(
            args.at(0), args.at(1), args.at(2), args.at(3)
        ));
  }

  auto argsItr = constructorArgs.cbegin();
  auto windowsItr = windows.cbegin();
  for (; argsItr != constructorArgs.end(); ++argsItr, ++windowsItr) {
    EXPECT_EQ(argsItr->at(0), (*windowsItr)->getNumRows());
    EXPECT_EQ(argsItr->at(1), (*windowsItr)->getNumCols());
  }

}

TEST_F(CursesWrapperTest, StartLocationsMatch) {
  std::vector<std::vector<int>> constructorArgs{
      {3, 4, 0, 0},
      {5, 9, 6, 2},
      {13, 27, 23, 62}
  };
  std::vector<std::unique_ptr<Curses::Window>> windows;
  for (const auto& args : constructorArgs) {
    windows.push_back(
        std::make_unique<Curses::WindowImplementation>(
            args.at(0), args.at(1), args.at(2), args.at(3)
        ));
  }

  auto argsItr = constructorArgs.cbegin();
  auto windowsItr = windows.cbegin();
  for (; argsItr != constructorArgs.end(); ++argsItr, ++windowsItr) {
    EXPECT_EQ(argsItr->at(2), (*windowsItr)->getRowStart());
    EXPECT_EQ(argsItr->at(3), (*windowsItr)->getColStart());
  }
}

TEST_F(CursesWrapperTest, CursorMoveWorks) {
  Curses::WindowImplementation win(15, 32, 23, 8);
  testCursorMoves(win, 3, 9);
  testCursorMoves(win, 4, 20);
  testCursorMoves(win, 0, 0);
  testCursorMoves(win, 14, 31);
}

TEST_F(CursesWrapperTest, CursorMoveLeftWorks) {
  Curses::WindowImplementation win(15, 32, 23, 8);
  testCursorMoves(win, 3, 9);
  testCursorMovesLeft(win, 2, 3, 7);
  testCursorMovesLeft(win, 3, 3, 4);
  testCursorMovesLeft(win, 1, 3, 3);
  testCursorMovesLeft(win, 5, 3, 0); // stops at boundary
  testCursorMovesLeft(win, 1, 3, 0); // stops at boundary

  testCursorMoves(win, 4, 20);
  testCursorMovesLeft(win, 10, 4, 10);
  testCursorMovesLeft(win, 15, 4, 0); //stops at boundary
  testCursorMovesLeft(win, 1, 4, 0); //stops at boundary
}

TEST_F(CursesWrapperTest, CursorMoveRightWorks) {
  Curses::WindowImplementation win(15, 32, 23, 8);
  testCursorMoves(win, 3, 9);
  testCursorMovesRight(win, 2, 3, 11);
  testCursorMovesRight(win, 3, 3, 14);
  testCursorMovesRight(win, 1, 3, 15);
  testCursorMovesRight(win, 20, 3, 31); //stops at boundary
  testCursorMovesRight(win, 1, 3, 31); //stops at boundary

  testCursorMoves(win, 4, 10);
  testCursorMovesRight(win, 2, 4, 12);
  testCursorMovesRight(win, 3, 4, 15);  //stops at boundary
  testCursorMovesRight(win, 16, 4, 31); //stops at boundary
}

TEST_F(CursesWrapperTest, CursorMoveUpWorks) {
  Curses::WindowImplementation win(15, 32, 23, 8);
  testCursorMoves(win, 10, 9);
  testCursorMovesUp(win, 2, 8, 9);
  testCursorMovesUp(win, 3, 5, 9);
  testCursorMovesUp(win, 1, 4, 9);
  testCursorMovesUp(win, 20, 0, 9); //stops at boundary
  testCursorMovesUp(win, 1, 0, 9); //stops at boundary

  testCursorMoves(win, 4, 10);
  testCursorMovesUp(win, 2, 2, 10);
  testCursorMovesUp(win, 3, 0, 10);  //stops at boundary
  testCursorMovesUp(win, 1, 0, 10); //stops at boundary
}

TEST_F(CursesWrapperTest, CursorMoveDownWorks) {
  Curses::WindowImplementation win(15, 32, 23, 8);
  testCursorMoves(win, 5, 9);
  testCursorMovesDown(win, 2, 7, 9);
  testCursorMovesDown(win, 3, 10, 9);
  testCursorMovesDown(win, 1, 11, 9);
  testCursorMovesDown(win, 20, 14, 9); //stops at boundary
  testCursorMovesDown(win, 1, 14, 9); //stops at boundary

  testCursorMoves(win, 4, 10);
  testCursorMovesDown(win, 2, 6, 10);
  testCursorMovesDown(win, 9, 14, 10);  //stops at boundary
  testCursorMovesDown(win, 1, 14, 10); //stops at boundary
}

TEST_F(CursesWrapperTest, AddSingleCharacter) {
  const int numRows = 15;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  win.addCharacter(1, 3, 'k');
  ansWin.addCharacter(1, 3, 'k');
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, AddSingleCharacterInBottomRightCorner) {
  const int numRows = 15;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  win.addCharacter(14, 9, 'k');
  ansWin.addCharacter(14, 9, 'k');
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, AddSingleCharacterAtEndOfRow) {
  const int numRows = 15;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  win.addCharacter(10, 9, 'k');
  ansWin.addCharacter(10, 9, 'k');
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, AddSingleCharacterWithAdvancementOff) {
  const int numRows = 15;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  win.addCharacter(1, 3, 'k');
  ansWin.addCharacter(1, 3, 'k');
  ansWin.moveCursor(1, 3);
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, AddSingleCharacterAtEndOfRowWithAdvancementOff) {
  const int numRows = 15;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  win.addCharacter(10, 9, 'k');
  ansWin.addCharacter(10, 9, 'k');
  ansWin.moveCursor(10, 9);
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, AddMultipleCharacters) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  std::vector<std::tuple<int, int, char>> args{{1, 3, 'k'},
                                               {2, 9, 'k'},
                                               {6, 4, 'p'},
                                               {2, 3, '{'},
                                               {0, 0, '@'},
                                               {3, numCols - 1, '+'},
                                               {2, 3, '6'},
                                               {numRows - 1, numCols - 1, '!'}
  };

  for (const auto& arg : args) {
    win.addCharacter(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg));
    ansWin.addCharacter(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg));

    ASSERT_TRUE(win == ansWin);
  }
}

TEST_F(CursesWrapperTest, AddMultipleCharactersWithAdvancementOff) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  std::vector<std::tuple<int, int, char>> args{{1, 3, 'k'},
                                               {2, 9, 'k'},
                                               {6, 4, 'p'},
                                               {2, 3, '{'},
                                               {0, 0, '@'},
                                               {3, numCols - 1, '+'},
                                               {2, 3, '6'},
                                               {numRows - 1, numCols - 1, '!'}
  };

  for (const auto& arg : args) {
    win.addCharacter(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg));
    ansWin.addCharacter(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg));
    ansWin.moveCursor(std::get<0>(arg), std::get<1>(arg));
    ASSERT_TRUE(win == ansWin);
  }
}

TEST_F(CursesWrapperTest, AddMultipleCharactersNoLocationSpecifiedWithAdvancement) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 7;
  const int colStart = 5;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  std::string letters2Add("Hello World And Have a nice day!!");

  win.moveCursor(rowStart, colStart);
  ansWin.moveCursor(rowStart, colStart);

  for (const auto& letter: letters2Add) {
    win.addCharacter(letter);
    ansWin.addCharacter(letter);
    ASSERT_TRUE(win == ansWin);
  }
}

TEST_F(CursesWrapperTest, AddMultipleCharactersNoLocationSpecifiedWithAdvancementOff) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 7;
  const int colStart = 5;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  std::string letters2Add("Hello World And Have a nice day!!");

  win.moveCursor(rowStart, colStart);
  ansWin.moveCursor(rowStart, colStart);

  for (const auto& letter: letters2Add) {
    win.addCharacter(letter);
    const int curRow = ansWin.getCurRow(), curCol = ansWin.getCurCol();
    ansWin.addCharacter(letter);
    ansWin.moveCursor(curRow, curCol);
    ASSERT_TRUE(win == ansWin);
  }
}

TEST_F(CursesWrapperTest, AddAStringWithAdvancementOn) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 7;
  const int colStart = 5;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  std::string letters2Add("Hello World And Have a nice day!!");

  win.addString(rowStart, colStart, letters2Add);
  ansWin.addString(rowStart, colStart, letters2Add);
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, AddAStringWithAdvancementOff) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 5;
  const int colStart = 5;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  std::string letters2Add("Hello World And Have a nice day!!");

  win.addString(0, 0, letters2Add);
  ansWin.addString(0, 0, letters2Add);
  ansWin.moveCursor(3, 2);
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, WriteUsingBracket) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 5;
  const int colStart = 5;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  win[3][2] = 'k';
  ansWin.addCharacter(3, 2, 'k');
  ansWin.moveCursor(3, 2);
  ASSERT_TRUE(win == ansWin);
}

TEST_F(CursesWrapperTest, ReadUsingBracket) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 5;
  const int colStart = 5;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOn();

  win[3][2] = 'k';
  ansWin.addCharacter(3, 2, 'k');
  ansWin.moveCursor(3, 2);
  ASSERT_TRUE(win == ansWin);

  win.moveCursor(5, 7);
  ASSERT_EQ(win[3][2], 'k');
}

TEST_F(CursesWrapperTest, ReadAndWriteMultipleCharactersWithBrackets) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  std::vector<std::tuple<int, int, char>> args{{1, 3, 'k'},
                                               {2, 9, 'k'},
                                               {6, 4, 'p'},
                                               {2, 3, '{'},
                                               {0, 0, '@'},
                                               {3, numCols - 1, '+'},
                                               {2, 5, '6'},
                                               {numRows - 1, numCols - 1, '!'}
  };

  for (const auto& arg : args) {
    win[std::get<0>(arg)][std::get<1>(arg)] = std::get<2>(arg);
    ansWin.addCharacter(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg));
    ansWin.moveCursor(std::get<0>(arg), std::get<1>(arg));
    ASSERT_TRUE(win == ansWin);
  }

  for (const auto& arg : args) {
    ASSERT_EQ(win[std::get<0>(arg)][std::get<1>(arg)], std::get<2>(arg));
  }

}

TEST_F(CursesWrapperTest, MoveAndReadChar) {
  std::stringstream windowIn("Hello World!");
  std::stringstream windowOut;
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);

  FakeCursesWindow::activeWindows.back()->setIn(&windowIn);
  FakeCursesWindow::activeWindows.back()->setOut(&windowOut);

  ASSERT_EQ(win.getCharInput(3, 4), 'H');
  ASSERT_EQ(win.getCurRow(), 3);
  ASSERT_EQ(win.getCurCol(), 4);
}

TEST_F(CursesWrapperTest, ReadCharFromCurrentLocation) {
  std::string str("Hello World!");
  std::stringstream windowIn(str);
  std::stringstream windowOut;
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  FakeCursesWindow::activeWindows.back()->setIn(&windowIn);
  FakeCursesWindow::activeWindows.back()->setOut(&windowOut);
  win.moveCursor(5, 7);

  for (const auto& let : str) {
    ASSERT_EQ(win.getCharInput(), let);
    ASSERT_EQ(win.getCurRow(), 5);
    ASSERT_EQ(win.getCurCol(), 7);
  }
}

TEST_F(CursesWrapperTest, MoveAndReadString) {
  std::string str("Hello World!\nGoodbye World!");
  std::stringstream windowIn(str);
  std::stringstream windowOut;
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  FakeCursesWindow::activeWindows.back()->setIn(&windowIn);
  FakeCursesWindow::activeWindows.back()->setOut(&windowOut);
  ASSERT_EQ(win.getStringInput(3, 6), "Hello World!");
  ASSERT_EQ(win.getCurRow(), 3);
  ASSERT_EQ(win.getCurCol(), 6);
}

TEST_F(CursesWrapperTest, ReadMultipleStrings) {
  std::string str("Hello World!\nGoodbye World!\nA whole new world\n");
  std::stringstream windowIn(str);
  std::stringstream windowOut;
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);

  win.setAdvanceCursorOff();

  FakeCursesWindow::activeWindows.back()->setIn(&windowIn);
  FakeCursesWindow::activeWindows.back()->setOut(&windowOut);
  win.moveCursor(9, 8);
  ASSERT_EQ(win.getStringInput(), "Hello World!");
  ASSERT_EQ(win.getCurRow(), 9);
  ASSERT_EQ(win.getCurCol(), 8);

  ASSERT_EQ(win.getStringInput(), "Goodbye World!");
  ASSERT_EQ(win.getCurRow(), 9);
  ASSERT_EQ(win.getCurCol(), 8);

  ASSERT_EQ(win.getStringInput(), "A whole new world");
  ASSERT_EQ(win.getCurRow(), 9);
  ASSERT_EQ(win.getCurCol(), 8);
}

TEST_F(CursesWrapperTest, Refresh) {
  const int numRows = 10;
  const int numCols = 10;
  const int rowStart = 3;
  const int colStart = 7;
  Curses::WindowImplementation win(numRows, numCols, rowStart, colStart);
  FakeCursesWindow ansWin(numRows, numCols, rowStart, colStart);
  FakeCursesWindow fakeStdscr(ROWS, COLS, 0, 0);
  ansWin.setStdscr(&fakeStdscr);

  win.setAdvanceCursorOff();

  std::vector<std::tuple<int, int, char>> args{{1, 3, 'k'},
                                               {2, 9, 'k'},
                                               {6, 4, 'p'},
                                               {2, 3, '{'},
                                               {0, 0, '@'},
                                               {3, numCols - 1, '+'},
                                               {2, 5, '6'},
                                               {numRows - 1, numCols - 1, '!'}
  };

  for (const auto& arg : args) {
    win[std::get<0>(arg)][std::get<1>(arg)] = std::get<2>(arg);
    ansWin.addCharacter(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg));
    ansWin.moveCursor(std::get<0>(arg), std::get<1>(arg));
    ASSERT_TRUE(win == ansWin);

    win.refresh();
    ansWin.refresh();

    ASSERT_TRUE(*stdscr == fakeStdscr);
  }

}
