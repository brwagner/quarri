#include <cxxtest/TestSuite.h>
#include <iostream>
#include "AGameObject.hpp"

class AGameObjectTestSuite : public CxxTest::TestSuite
{
public:

  void test_Nothing()
  {
    TS_ASSERT(true);
  }
};

