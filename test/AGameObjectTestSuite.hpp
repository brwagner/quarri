#include <cxxtest/TestSuite.h>
#include <iostream>
#include "AGameObject.hpp"
#include "Constants.hpp"
#include "Block.hpp"

class AGameObjectTestSuite : public CxxTest::TestSuite
{
public:
  AGameObject* goWall;
  AGameObject* goMoveable;
  
  // set up objects for testing
  void setUp(){
   goWall = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
   goMoveable = new Block(std::pair<double, double>(-2 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE), true, Constants::WALL_COLOR);
   
  }
  
  // delete objects used for testing
  void tearDown(){
    delete goWall;
    delete goMoveable;
  }

  void test_relativePosition()
  {
    std::pair<double,double> origin = std::pair<double,double>(0,0);
    TS_ASSERT(origin == goWall->relativePosition(0,0));
    TS_ASSERT_EQUALS(origin, goMoveable->relativePosition(-2,1));
  }
};

