#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Player.hpp"

class PlayerTestSuite : public CxxTest::TestSuite
{
public:

  void test_Nothing()
  {
    TS_ASSERT(true);
  }
};
