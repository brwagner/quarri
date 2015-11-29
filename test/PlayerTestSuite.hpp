#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Player.hpp"
#include "Constants.hpp"

class PlayerTestSuite : public CxxTest::TestSuite
{
    
    std::pair<double, double> * pos1;
    Player * player1;
    
public:
    void setUp()
    {
        pos1 = new std::pair<double, double>(1 * Constants::PLAYER_SIZE, 0.0);
        player1 = new Player(*pos1, true);
    }
    
    void tearDown()
    {
        
    }
 
    void test_Constructor()
    {
        TS_ASSERT(*pos1 == player1->relativePosition(0,0));
    }
    
    void test_isMovable()
    {
        TS_ASSERT(player1->isMovable());
    }
    
    void test_isPlayer()
    {
        TS_ASSERT(player1->isPlayer());
    }
    
    void test_move1()
    {
        
    }
    
    
};
