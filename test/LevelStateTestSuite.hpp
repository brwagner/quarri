#include <cxxtest/TestSuite.h>
#include <iostream>
#include "AGameObject.hpp"
#include "Block.hpp"
#include "Constants.hpp"
#include "Display.hpp"
#include "LevelState.hpp"

class LevelStateTestSuite : public CxxTest::TestSuite
{
    Display * display1;
    Display * display2;
    
    LevelState * levelState1;
    LevelState * levelState2;
   
public:
    void setUp()
    {
        display1 = new Display("Quarri", 800, 600);
        levelState1 = new LevelState("res/level/", 1, display1);
        
        display2 = new Display("Quarri", 800, 600);
        levelState2 = new LevelState("res/level/", 2, display2);
    }
    
    void tearDown()
    {
        delete display1;
        delete levelState1;
        delete display2;
        delete levelState2;
    }
    
    void test_Constructor()
    {
        //Is there a way to test this besides testing everything else?
        
        TS_ASSERT(true);
    }
    
    void test_getAtPositionWall()
    {

        const std::pair<double,double> pos = std::pair<double,double>(0, 0);
        AGameObject* objectFound = levelState1->getAtPosition(pos);

        TS_ASSERT_EQUALS(objectFound->getPos(), pos); // Verifies the object you got is actually at that position and that it is a wall, as it should be
        TS_ASSERT(!objectFound->isPlayer());
        TS_ASSERT(!objectFound->isMovable());
        
    }
    
    void test_getAtPositionPlayer()
    {
        const std::pair<double,double> pos = std::pair<double,double>(8 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        AGameObject* objectFound = levelState1->getAtPosition(pos);
        TS_ASSERT_EQUALS(objectFound->getPos(), pos); // Verifies the object you got is actually at that position and that it is a player, as it should be
        TS_ASSERT(objectFound->isPlayer());
        
    }
    
    void test_getAtPositionMovable()
    {
        const std::pair<double,double> pos = std::pair<double,double>(5 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        AGameObject* objectFound = levelState1->getAtPosition(pos);
        TS_ASSERT_EQUALS(objectFound->getPos(), pos); // Verifies the object you got is actually at that position and that it is a moveable block, as it should be
        TS_ASSERT(!objectFound->isPlayer());
        TS_ASSERT(objectFound->isMovable());
    }
    
    void test_getAtPositionWinCond()
    {
        const std::pair<double,double> pos = std::pair<double,double>(1 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        AGameObject* objectFound = levelState1->getAtPosition(pos);
        TS_ASSERT_EQUALS(objectFound->getPos(), pos); // Verifies the object you got is actually at that position and that it is a nonmoveable block (which is what wincond inherits from)
        TS_ASSERT(!objectFound->isPlayer());
        TS_ASSERT(!objectFound->isMovable());
        
    }
    
    void test_move1()
    {
        const std::pair<double,double> from = std::pair<double,double>(8 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
         const std::pair<double,double> to = std::pair<double,double>(7 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        
        levelState1->move(from, to);
        AGameObject* newPlace = levelState1->getAtPosition(to);
        AGameObject* oldPlace = levelState1->getAtPosition(from);
        TS_ASSERT(newPlace->isPlayer()); // Player moves to the given position
        TS_ASSERT(oldPlace == NULL);
    }
    
    void test_move2()
    {
        const std::pair<double,double> from = std::pair<double,double>(8 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        const std::pair<double,double> to = std::pair<double,double>(5 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);
        
        levelState1->move(from, to);
        AGameObject* objectFound = levelState1->getAtPosition(from);
        TS_ASSERT(objectFound->isPlayer()); // Player doesn't move since it can't move there
    }
    
    void test_isAtPosition1()
    {
        const std::pair<double,double> pos = std::pair<double,double>(8 * Constants::PLAYER_SIZE, 1* Constants::PLAYER_SIZE);

        TS_ASSERT(levelState1->isAtPosition(pos));
    }
    
    void test_isAtPosition2()
    {
        const std::pair<double,double> pos = std::pair<double,double>(8 * Constants::PLAYER_SIZE, 2* Constants::PLAYER_SIZE);
        
        TS_ASSERT(!levelState1->isAtPosition(pos));
    }
    
    void test_isAtPosition3()
    {
        const std::pair<double,double> pos = std::pair<double,double>(0 * Constants::PLAYER_SIZE, 2* Constants::PLAYER_SIZE);
        
        TS_ASSERT(levelState1->isAtPosition(pos));
    }
    
    // Update just calls update on items in the vector so won't be tested, same for some other methods...
    
    void test_registerWin()
    {
        TS_ASSERT_EQUALS(1, levelState1->getCurrentLevel());
        levelState1->registerWin();
        TS_ASSERT_EQUALS(2, levelState1->getCurrentLevel());
        // TODO Cover case where you beat the last level
    }
    

};
