#include <cxxtest/TestSuite.h>
#include <iostream>
#include "AGameObject.hpp"
#include "Constants.hpp"
#include "Block.hpp"
#include "LevelState.hpp"
#include <vector>

class AGameObjectTestSuite : public CxxTest::TestSuite
{
public:
  AGameObject* goWall;
  AGameObject* goMovable;
  Display* display;
  // go movable is two spaces above go wall in this level
  LevelState* state;
  
  // set up objects for testing
  void setUp(){
   goWall = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
   goMovable = new Block(std::pair<double, double>(0 * Constants::PLAYER_SIZE, 2 * Constants::PLAYER_SIZE), true, Constants::WALL_COLOR);
   
   std::vector<AGameObject*> gameObjects;
   
   gameObjects.push_back(goWall);
   gameObjects.push_back(goMovable);
   
   display = new Display("Quarri", 800, 600);
   
   state = new LevelState(gameObjects, 0, display);
   
  }
  
  // delete objects used for testing
  void tearDown(){
    delete display;
    delete state;
  }
  
  void test_getPos(){
    std::pair<double,double> pos1 = std::pair<double,double>(0,0);
    TS_ASSERT(pos1 == goWall->getPos());
    std::pair<double,double> pos2 = std::pair<double,double>(0,2*Constants::PLAYER_SIZE);
    TS_ASSERT(pos2 == goMovable->getPos());
  }
  
  void test_move(){
    goMovable->move(goMovable->up()); // moves up one space, then falls back down 2 spaces
    std::pair<double,double> newPos = std::pair<double,double>(0, Constants::PLAYER_SIZE);
    TS_ASSERT(newPos == goMovable->getPos());
  }

  void test_isMovable(){
    // movable is movable
    TS_ASSERT(goMovable->isMovable());
    // goWall is not movable
    TS_ASSERT(!goWall->isMovable());
  }
  
  void test_isPlayer(){
    TS_ASSERT(!goWall->isPlayer());
    TS_ASSERT(!goMovable->isPlayer());
  }
  
  void test_relativePosition()
  {
    std::pair<double,double> origin = std::pair<double,double>(0,0);
    // returns object's position when given 0,0
    TS_ASSERT(origin == goWall->relativePosition(0,0));
    // returns object's position + player_size*pos
    TS_ASSERT_EQUALS(origin, goMovable->relativePosition(0,-2));
  }
  
  void test_down(){
    std::pair<double,double> dpos = std::pair<double,double>(0, -Constants::PLAYER_SIZE);
    TS_ASSERT(dpos == goWall->down());
  }
  
  void test_up(){
    std::pair<double,double> dpos = std::pair<double,double>(0, Constants::PLAYER_SIZE);
    TS_ASSERT(dpos == goWall->up());
  }
  
  void test_left(){
    std::pair<double,double> dpos = std::pair<double,double>(-Constants::PLAYER_SIZE, 0);
    TS_ASSERT(dpos == goWall->left());
  }
  
  void test_right(){
    std::pair<double,double> dpos = std::pair<double,double>(Constants::PLAYER_SIZE, 0);
    TS_ASSERT(dpos == goWall->right());
  }
  
};

