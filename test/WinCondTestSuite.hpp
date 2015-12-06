#include <cxxtest/TestSuite.h>
#include "WinCond.hpp"
#include "Constants.hpp"


class WinCondTestSuite : public CxxTest::TestSuite
{
public:
  void test_Nothing(){
    TS_ASSERT(true);
  }
};