/**************************************************************************************************/
// Test File for PP1
// Requires the Catch2 header file
// How to compile: g++ -std=c++17 -Wall -I$(CATCH_SINGLE_INCLUDE) (All cpp files)
// Example if Catch2 and source files are in this directory and at directory level: 
//    Example: g++ -std=c++17 -Wall *.cpp
// To see what tests were successful and failed, run your executable with the -s flag
//    Example: a.out -s
// A successful test should output: All tests passed (22 assertions in 1 test case)
/**************************************************************************************************/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>

#include "CalcList.hpp"
#include "CalcList.cpp"

TEST_CASE("PP1: Test Cases for CalcList") {
  CalcList calc;

  SECTION("Total should be initially zero") {
    REQUIRE(calc.total() == 0.0l);
  }

  SECTION("Operations should be removable") {
    calc.newOperation(SUBTRACTION, 10);
    REQUIRE(calc.total() == -10.0l);

    calc.removeLastOperation();
    REQUIRE(calc.total() == 0.0l);
  }

  SECTION("Zero multiplication operation should be removable") {
    calc.newOperation(ADDITION, 50);
    calc.newOperation(MULTIPLICATION, 0);

    calc.removeLastOperation();
    REQUIRE(calc.total() == 50.0l);
  }

  SECTION("Operations cannot divide by zero and should throw") {
    REQUIRE_THROWS(calc.newOperation(DIVISION, 0));

    REQUIRE_NOTHROW(calc.newOperation(SUBTRACTION, 10));
    REQUIRE_THROWS(calc.newOperation(DIVISION, 0));
  }



  SECTION("Removal of operations from an empty CalcList should throw") {
    REQUIRE_THROWS(calc.removeLastOperation());

    REQUIRE_NOTHROW(calc.newOperation(DIVISION, 10));
    REQUIRE_NOTHROW(calc.removeLastOperation());
    REQUIRE_THROWS(calc.removeLastOperation());
  }

  SECTION("toString functions should return string list of operations at precision") {
    calc.newOperation(ADDITION, 10);
    calc.newOperation(ADDITION, 20);
    calc.newOperation(SUBTRACTION, 20);
    calc.removeLastOperation();
    calc.newOperation(MULTIPLICATION, 1);

    std::string output = calc.toString(1);
    std::string outputShouldBe = 
    "3: 30.0*1.0=30.0\n2: 10.0+20.0=30.0\n1: 0.0+10.0=10.0\n";
    REQUIRE_THAT(output, Catch::Equals(outputShouldBe));

    output = calc.toString(3);
    outputShouldBe = 
    "3: 30.000*1.000=30.000\n2: 10.000+20.000=30.000\n1: 0.000+10.000=10.000\n";
    REQUIRE_THAT(output, Catch::Equals(outputShouldBe));
  }

  SECTION("Operations should change the total") {
    double testTotal1, testTotal2, testTotal3, testTotal4;
    double tnAdd = rand() % 100 + 1;
    double tnMul = rand() % 100 + 1;
    double tnSub = rand() % 100 + 1;
    double tnDiv = rand() % 100 + 1;

    testTotal1 = 0 + tnAdd;
    testTotal2 = testTotal1 * tnMul;
    testTotal3 = testTotal2 - tnSub;
    testTotal4 = testTotal3 / tnDiv;

    calc.newOperation(ADDITION, tnAdd);
    REQUIRE(calc.total() == testTotal1);

    calc.newOperation(MULTIPLICATION, tnMul);
    REQUIRE(calc.total() == testTotal2);
    
    calc.newOperation(SUBTRACTION, tnSub);
    REQUIRE(calc.total() == testTotal3);

    calc.newOperation(DIVISION, tnDiv);
    REQUIRE(calc.total() == testTotal4);

    calc.removeLastOperation();
    REQUIRE(calc.total() == testTotal3);

    calc.removeLastOperation();
    REQUIRE(calc.total() == testTotal2);

    calc.removeLastOperation();
    REQUIRE(calc.total() == testTotal1);

    calc.removeLastOperation();
    REQUIRE(calc.total() == 0);

    calc.newOperation(ADDITION, 10);
    REQUIRE(calc.total() == 10);
  }
}
