//
// Created by mfbut on 2/26/2019.
//

#include "CursesWrapperTest.h"

CursesWrapperTest::CursesWrapperTest() : numWindowsCreated(0) {}

void CursesWrapperTest::SetUp() {
  Test::SetUp();
  initscr();
  numWindowsCreated++;
}

void CursesWrapperTest::TearDown() {
  Test::TearDown();
  const unsigned int numWindowsRemaining = FakeCursesWindow::activeWindows.size();
  FakeCursesWindow::activeWindows.clear(); //delete all active windows

  if (FakeCursesWindow::activeWindows.size() > 1) {
    FAIL() << numWindowsCreated <<
           " windows (including stdscr) were created for this test but there are"
           " still " << numWindowsRemaining << " windows left (including stdscr)."
                                               " Double check you called delwin in your destructor.";
  } else if (numWindowsRemaining == 0) {
    FAIL() << "Some how you ended up deleting stdscr. You shouldn't have done that";
  }
}

