#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Display.hpp"

class DisplayTestSuite : public CxxTest::TestSuite
{
public:
  Display* d;
  
  void setUp(){
    d = new Display("Quarri", 800, 600);
  }
  void tearDown(){
    delete d;
  }
  
  void test_Constructor(){
    TS_ASSERT_EQUALS(d->getWidth(), 800);
    TS_ASSERT_EQUALS(d->getHeight(), 600);
    TS_ASSERT_EQUALS(d->getCameraOffset(), 0);
  }
  
  void test_MoveCamera(){
    d->moveCamera(3);
    TS_ASSERT_EQUALS(d->getCameraOffset(), 3);
    d->moveCamera(5);
    TS_ASSERT_EQUALS(d->getCameraOffset(), 8);
    d->moveCamera(-20);
    TS_ASSERT_EQUALS(d->getCameraOffset(), -12);
  }
  
  void test_resetCamera(){
    d->moveCamera(3000);
    d->resetCamera();
    TS_ASSERT_EQUALS(d->getCameraOffset(), 0);
    d->resetCamera();
    TS_ASSERT_EQUALS(d->getCameraOffset(), 0);
    d->moveCamera(-4444444);
    d->resetCamera();
    TS_ASSERT_EQUALS(d->getCameraOffset(), 0);
  }
};