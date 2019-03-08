//
// Created by mfbut on 2/26/2019.
//

#ifndef CURSESWRAPPERTESTER_CURSESWRAPPERTEST_H
#define CURSESWRAPPERTESTER_CURSESWRAPPERTEST_H
#include "gtest/gtest.h"
#include "FakeCurses.h"
#include "WindowImplementation.h"
class CursesWrapperTest : public ::testing::Test {
 protected:
 public:
  CursesWrapperTest();
 protected:
  virtual void SetUp() override;
  virtual void TearDown() override;
  int numWindowsCreated;
};

#endif //CURSESWRAPPERTESTER_CURSESWRAPPERTEST_H
