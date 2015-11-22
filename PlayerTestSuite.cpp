/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_PlayerTestSuite_init = false;
#include "PlayerTestSuite.hpp"

static PlayerTestSuite suite_PlayerTestSuite;

static CxxTest::List Tests_PlayerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PlayerTestSuite( "PlayerTestSuite.hpp", 5, "PlayerTestSuite", suite_PlayerTestSuite, Tests_PlayerTestSuite );

static class TestDescription_suite_PlayerTestSuite_test_Nothing : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PlayerTestSuite_test_Nothing() : CxxTest::RealTestDescription( Tests_PlayerTestSuite, suiteDescription_PlayerTestSuite, 9, "test_Nothing" ) {}
 void runTest() { suite_PlayerTestSuite.test_Nothing(); }
} testDescription_suite_PlayerTestSuite_test_Nothing;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
