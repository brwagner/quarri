#include <cxxtest/TestSuite.h>
#include "WinCond.hpp"
#include "Constants.hpp"
#include "LevelState.hpp"
#include "Player.hpp"
#include <vector>

class WinCondTestSuite : public CxxTest::TestSuite
{
  
public:
  Display* disp;
  LevelState* state;
  WinCond* wc;
  Player* p;

  // make a level where the wincond is two spaces to the left of the player
  void setUp(){
    disp = new Display("Quarri", 800, 600);
    
    Block* wall1 = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
    Block* wall2 = new Block(std::pair<double, double>(-2 * Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
    Block* wall3 = new Block(std::pair<double, double>(-Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
    
    wc = new WinCond(std::pair<double,double>(-2 * Constants::PLAYER_SIZE, Constants::PLAYER_SIZE));
    
    p = new Player(std::pair<double,double>(0, Constants::PLAYER_SIZE), true);
    
    std::vector<AGameObject*> gameobjects;
    gameobjects.push_back(wall1);
    gameobjects.push_back(wall2);
    gameobjects.push_back(wall3);
    gameobjects.push_back(wc);
    gameobjects.push_back(p);
    
    state = new LevelState(gameobjects, 1, disp); 
   
  }
  void tearDown(){
    delete disp;
    delete state;
  }
  
  void test_update(){
    // when the player is not touching the win zone
    wc->update();
    TS_ASSERT_EQUALS(1, state->getCurrentLevel());
  
    p->move(p->left());
    
    
    // when the player has touched the win zone
    wc->update();
    TS_ASSERT_EQUALS(2, state->getCurrentLevel());
  }
};