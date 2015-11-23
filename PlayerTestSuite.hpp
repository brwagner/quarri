#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Player.hpp"

class PlayerTestSuite : public CxxTest::TestSuite
{
public:
 
  void test_Constructor()
  {
    std::pair<double,double> pos = std::pair<double, double>(1.0, -1.0);
    Player p = Player(pos, true);
    //TS_ASSERT(pos == p.relativePosition(0,0));
  }
};
