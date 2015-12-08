#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Constants.hpp"
#include "Block.hpp"
#include "LevelState.hpp"
#include <vector>

class BlockTestSuite : public CxxTest::TestSuite
{
public:
  Block* b;
  
  void setUp(){
   b = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
  }
  
  void tearDown(){
    delete b;
  }
  
  void test_getColor(){
    TS_ASSERT_EQUALS(Constants::WALL_COLOR, b->getColor());
  }
  
  // not much to test here besides what's already tested by game object
};