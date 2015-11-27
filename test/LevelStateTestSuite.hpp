#include <cxxtest/TestSuite.h>
#include <iostream>
#include "AGameObject.hpp"
#include "Block.hpp"
#include "Constants.hpp"
#include "Display.hpp"
#include "LevelState.hpp"

class LevelStateTestSuite : public CxxTest::TestSuite
{
    // NEED DEFAULT CONSTRUCTORS FOR LEVELSTATE AND DISPLAY
public:
    void setUp()
    {

    }
    
    void tearDown()
    {

    }
    
    void test_Constructor()
    {
        //levelState1;
        
        TS_ASSERT(true);
        
    
        
    }
    
    void test_getAtPosition1()
    {
        Display display = Display("Quarri", 800, 600);
        LevelState levelState1 = LevelState("res/level/", 2, &display);
        
        const std::pair<double,double> pos = std::pair<double,double>(0, 0);
        AGameObject* objectFound = levelState1.getAtPosition(pos);

        TS_ASSERT_EQUALS(objectFound->getPos(), pos); // Verifies the object you got is actually at that position and that it is a wall, as it should be
        TS_ASSERT(!objectFound->isPlayer());
        TS_ASSERT(!objectFound->isMovable());
        
    }
    
    void test_getAtPosition2()
    {
        Display display = Display("Quarri", 800, 600);
        LevelState levelState1 = LevelState("res/level/", 1, &display);
        
        const std::pair<double,double> pos = std::pair<double,double>(8 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        AGameObject* objectFound = levelState1.getAtPosition(pos);
        TS_ASSERT_EQUALS(objectFound->getPos(), pos); // Verifies the object you got is actually at that position and that it is a wall, as it should be
        TS_ASSERT(objectFound->isPlayer());
        
    }
    

    

};
