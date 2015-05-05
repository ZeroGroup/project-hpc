// #include <gmock/gtest.h>

// TEST(SensorsTestcase1, empty) {
//   EXPECT_EQ(1, 1);
// }

#include "ut/mocks/TurtleMock.hpp"

#include <gtest/gtest.h>

using ::testing::AtLeast;

TEST(TurtleMockTest, CanBeIntantiated) {
    TurtleMock turtle;
    EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

    turtle.PenDown();
    turtle.PenDown();
}

class TestedClass {
public:
    TestedClass(SensorNetwork * net) : _net(net) {}

    void testedMethod(){
        _net->push();
    }

private:
    SensorNetwork * _net;
};

TEST(SensorNetworkTestcase1, empty_CanbeInstantiated){
    SensorNetworkMock mock;

    TestedClass uut(&mock);

    EXPECT_CALL(mock, push()).Times(AtLeast(1));

    uut.testedMethod();
}

// int main(int argc, char** argv) {
//   // The following line must be executed to initialize Google Mock
//   // (and Google Test) before running the tests.
//   ::testing::InitGoogleMock(&argc, argv);
//   return RUN_ALL_TESTS();
// }
